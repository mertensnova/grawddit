package main

import (
	"bufio"
	"fmt"
	"io/ioutil"
	"log"
	"math/rand"
	"net/http"
	"os"
	"strings"
	"time"

	"golang.org/x/net/html"
)

type Data struct {
    ID string
	Title    string
	Post     string
	Score    string
	UserName string
}

func GetPost(content string,id string)  {
	reader := strings.NewReader(content)
	doc, err := html.Parse(reader)

	if err != nil {
		log.Fatalln("Error parsing HTML:", err)
	}

	var traverse func(*html.Node)
	traverse = func(node *html.Node) {
		if node.Type == html.ElementNode && node.Data == "p" {
            fmt.Println(node.FirstChild.Data)
			/*for _, post := range node.Attr {
				if post.Key == id {
                    text = post.Val
					break
				}
			}*/
		}

		for c := node.FirstChild; c != nil; c = c.NextSibling {
			traverse(c)
		}

	}

	traverse(doc)

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

func RandomUserAgents() string {

	file, err := os.Open("user-agent.txt")

	if err != nil {
		fmt.Println("Error opening file:", err)
	}

	defer file.Close()

	scanner := bufio.NewScanner(file)
	var lines []string
	for scanner.Scan() {
		lines = append(lines, scanner.Text())
	}

	if len(lines) == 0 {
		fmt.Println("File is empty")
	}

	r := rand.Intn(len(lines))

	return lines[r]
}

func SendRequests(value string) string {

	client := &http.Client{
		Timeout: 30 * time.Second,
	}

	request, err := http.NewRequest("GET", value, nil)
	request.Header.Set("User-Agent", RandomUserAgents())

	if err != nil {
		log.Fatalln(err)
	}

	response, err := client.Do(request)

	if err != nil {
		log.Fatalln(err)
	}

	body, err := ioutil.ReadAll(response.Body)

	if err != nil {
		fmt.Println("Error reading response body:", err)
		return ""
	}

	return string(body)
}
