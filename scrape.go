package main

import (
	"fmt"
	"log"
	"strings"

	"golang.org/x/net/html"
)

type Data struct {
	ID       string
	Title    string
	Post     string
	Score    string
	UserName string
}

func GetPost(content string, id string) string {
	reader := strings.NewReader(content)
	doc, err := html.Parse(reader)

	if err != nil {
		log.Fatalln("Error parsing HTML:", err)
	}

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
							for c := isP.FirstChild; c != nil; c = c.NextSibling {
								if (c.Data == "em" || c.Data == "i" || c.Data == "b") && c != nil {
									post += c.FirstChild.Data
								} else {
									post += c.Data
								}
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
    fmt.Println(post)
	return post
}

func GetText(content string, attr string) string {

	var text string
	reader := strings.NewReader(content)
	doc, err := html.Parse(reader)

	if err != nil {
		log.Fatalln("Error parsing HTML:", err)
	}

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

func LinkGrabber(value string) []string {

	var links []string
	doc, err := html.Parse(strings.NewReader(value))

	if err != nil {
		log.Fatal(err)
	}

	var f func(*html.Node)
	f = func(n *html.Node) {
		if n.Type == html.ElementNode && n.Data == "a" {
			for _, a := range n.Attr {
				if a.Key == "href" {
					if strings.Contains(a.Val, "r/TwoSentenceHorror/comments") {
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
	return links
}
