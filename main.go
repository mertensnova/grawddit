package main

import (
	"flag"
	"fmt"
	"time"
)

var base string = "https://reddit.com"

func main() {

	startTime := time.Now()

	var subreddit string
	var limit int
	var category string

	flag.StringVar(&subreddit, "subreddit", "TwoSentenceHorror", "Subreddit")
	flag.IntVar(&limit, "limit", 10, "Number of posts to scrape")
	flag.StringVar(&category, "sort", "top", "Type of sort E.g [new,top,hot]")

	flag.Parse()

	Start(subreddit, limit, category)

	endTime := time.Now()
	elapsedTime := endTime.Sub(startTime)

	fmt.Println("Done!")
	fmt.Println("Elapsed Time:", elapsedTime)
}

func Start(subreddit string, limit int, category string) {
	var data []Data
	var suffix string

	if category == "top" {
		suffix = "/r/" + subreddit + "/top/?t=day"
	} else {
		suffix = "/r/" + subreddit + "/" + category
	}

	url := base + suffix

	fmt.Println("Fetching the page...")
	html := Scroller(url)

	links := Unique(LinkGrabber(html, subreddit))

	CreateDir(subreddit)

	for k, v := range links {

		if k == limit {
			break
		}
		fmt.Println(k, "Scrapping -> "+v)
		content := SendRequests(base + v)
		id := GetSubRedditData(content, "id")
		imageurl := GetSubRedditData(content, "content-href")
		if imageurl != "" {
			DownloadImage(imageurl, id, subreddit)
		}

		var d = Data{
			ID:           id,
			Title:        GetSubRedditData(content, "post-title"),
			Upvotes:      GetSubRedditData(content, "score"),
			Author:       GetSubRedditData(content, "author"),
			Post:         GetSubRedditPost(content, id),
			CommentCount: GetSubRedditData(content, "comment-count"),
			Image:        imageurl,
			PostType:     GetSubRedditData(content, "post-type"),
			CreatedAt:    GetSubRedditData(content, "created-timestamp"),
		}
		data = append(data, d)
	}

	WritetoJSON(data, subreddit)
}
