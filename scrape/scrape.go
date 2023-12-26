package scrape

import (
	"log"
	"strings"

	"golang.org/x/net/html"
)

const base = "https://reddit.com"

func StartWithoutImages(subreddit string, limit int, category string) (data []Data, err error) {
	return start(subreddit, limit, category, false)
}

func Start(subreddit string, limit int, category string) (data []Data, err error) {
	return start(subreddit, limit, category, true)
}

func start(subreddit string, limit int, category string, images bool) (data []Data, err error) {
	var suffix string

	if category == "top" {
		suffix = "/r/" + subreddit + "/top/?t=day"
	} else {
		suffix = "/r/" + subreddit + "/" + category
	}

	url := base + suffix

	log.Println("Fetching the page...")
	page, err := Scroller(url)
	if err != nil {
		return nil, err
	}

	grabber, err := LinkGrabber(page, subreddit)
	if err != nil {
		return nil, err
	}
	links := Unique(grabber)

	for k, v := range links {
		if k == limit {
			break
		}
		log.Printf("Scrapping %d -> %q", k, v)
		content, err := SendRequests(base + v)
		if err != nil {
			log.Printf("%q: %v (skipping)", v, err)
			continue
		}

		reader := strings.NewReader(content)
		doc, err := html.Parse(reader)
		if err != nil {
			log.Printf("error parsing %q: %v (skipping)", v, err)
		}

		id := GetSubRedditData(doc, "id")
		var d = Data{
			ID:           id,
			Title:        GetSubRedditData(doc, "post-title"),
			Upvotes:      GetSubRedditData(doc, "score"),
			Author:       GetSubRedditData(doc, "author"),
			Post:         GetSubRedditPost(doc, id),
			CommentCount: GetSubRedditData(doc, "comment-count"),

			PostType:  GetSubRedditData(doc, "post-type"),
			CreatedAt: GetSubRedditData(doc, "created-timestamp"),
		}
		if images {
			imageurl := GetSubRedditData(doc, "content-href")
			if imageurl != "" {
				if err := DownloadImage(imageurl, id, subreddit); err != nil {
					log.Printf("error downloading image %q from %q: %v", imageurl, id, err)
				}
			}
			d.Image = imageurl
		}
		data = append(data, d)
	}
	return data, nil
}

type Data struct {
	ID           string `json:"id"`
	Title        string `json:"title"`
	Post         string `json:"post"`
	Upvotes      string `json:"upvotes"`
	Author       string `json:"author"`
	Image        string `json:"image"`
	PostType     string `json:"post_type"`
	Flair        string `json:"flair"`
	NSFW         bool   `json:"nsfw"`
	CommentCount string `json:"commentscount"`
	CreatedAt    string `json:"created_at"`
}

func GetSubRedditPost(doc *html.Node, id string) string {
	var post string

	id = id + "-post-rtjson-content"

	var f func(*html.Node)
	f = func(node *html.Node) {
		if node.Type == html.ElementNode && node.Data == "div" {
			for _, v := range node.Attr {
				if v.Key == "id" {
					if v.Val == id {
						isP := node.FirstChild.NextSibling
						if isP.Type == html.ElementNode && isP.Data == "p" {
							post += isP.FirstChild.Data
							if (isP.Data == "em" || isP.Data == "i" || isP.Data == "b") && isP != nil {
								post += isP.FirstChild.Data
							} else {
								post += isP.Data
							}
						}

					}
				}
			}
		}

		for c := node.FirstChild; c != nil; c = c.NextSibling {
			f(c)
		}
	}

	f(doc)
	return post
}

func GetSubRedditData(doc *html.Node, attr string) string {
	var text string

	var traverse func(*html.Node)
	traverse = func(node *html.Node) {
		if node.Type == html.ElementNode && node.Data == "shreddit-post" {
			for _, post := range node.Attr {
				if post.Key == attr {
					text = post.Val
					break
				}
			}
		}

		for c := node.FirstChild; c != nil; c = c.NextSibling {
			traverse(c)
		}
	}

	traverse(doc)
	return text
}

func LinkGrabber(value string, subreddit string) ([]string, error) {
	suffix := "r/" + subreddit + "/comments"
	var links []string

	doc, err := html.Parse(strings.NewReader(value))
	if err != nil {
		return nil, err
	}

	var f func(*html.Node)
	f = func(n *html.Node) {
		if n.Type == html.ElementNode && n.Data == "a" {
			for _, a := range n.Attr {
				if a.Key == "href" {
					if strings.Contains(a.Val, suffix) {
						links = append(links, a.Val)
					}
					break
				}
			}
		}
		for c := n.FirstChild; c != nil; c = c.NextSibling {
			f(c)
		}
	}

	f(doc)
	return links, nil
}
