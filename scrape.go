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

func GetPost(content string, id string) {
	reader := strings.NewReader(content)
	doc, err := html.Parse(reader)
	if err != nil {
		log.Fatalln("Error parsing HTML:", err)
	}

	id = id + "-post-rtjson-content"
	var f func(*html.Node)
	f = func(node *html.Node) {

		if node.Type == html.ElementNode && node.Data == "div" {
			for c := node.FirstChild; c != nil; c = c.NextSibling {
				if c.Data == "p" && c != nil {
					fmt.Println(c.FirstChild.Data)
				}
			}
		}

		for c := node.FirstChild; c != nil; c = c.NextSibling {
			f(c)
		}
	}

	f(doc)
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


