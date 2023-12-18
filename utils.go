package main

import (
	"bufio"
	"context"
	"fmt"
	"io/ioutil"
	"log"
	"math/rand"
	"net/http"
	"os"
	"strings"
	"time"

	"github.com/chromedp/chromedp"

	"golang.org/x/net/html"
)

func Scroller(target string) string {
	// Create a new context
	ctx, cancel := chromedp.NewContext(context.Background())
	defer cancel()

	// Navigate to the target website
	if err := chromedp.Run(ctx, chromedp.Navigate("https://example.com")); err != nil {
		log.Fatal(err)
	}

	// Wait for dynamic content to load (you may need to adjust the timeout)
	time.Sleep(5 * time.Second)

	// Scroll down to trigger the loading of more content
    if err := chromedp.Run(ctx, chromedp.ActionFunc(func(ctx context.Context) error {
		// Scroll down by executing JavaScript
		err := chromedp.Evaluate(ctx, "window.scrollTo(0, document.body.scrollHeight);", nil)
		return err
	})); err != nil {
		log.Fatal(err)
	}

	// Wait for the additional content to load (you may need to adjust the timeout)
	time.Sleep(5 * time.Second)

	// Extract the HTML content of the entire page
	var htmlContent string
	if err := chromedp.Run(ctx, chromedp.OuterHTML("html", &htmlContent)); err != nil {
		log.Fatal(err)
	}

	// Print or use the HTML content
	fmt.Println(htmlContent)
	return htmlContent
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

func Unique(intSlice []string) []string {
	keys := make(map[string]bool)
	list := []string{}
	for _, entry := range intSlice {
		if _, value := keys[entry]; !value {
			keys[entry] = true
			list = append(list, entry)
		}
	}
	return list
}
