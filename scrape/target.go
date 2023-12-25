package main

import (
	"context"
	"fmt"
	"io/ioutil"
	"log"
	"net/http"
	"time"

	"github.com/chromedp/cdproto/dom"
	"github.com/chromedp/chromedp"
)

func Scroller(target string) string {

	fmt.Println("Scrolling the page...")

	ctx, cancel := chromedp.NewContext(
		context.Background(),
	)
	defer cancel()

	var html string
	err := chromedp.Run(ctx,
		chromedp.Navigate(target),
		chromedp.Evaluate(ReadScripts("./script.js"), nil),
		chromedp.Sleep(3000 * time.Millisecond),
		chromedp.ActionFunc(func(ctx context.Context) error {
			rootNode, err := dom.GetDocument().Do(ctx)
			if err != nil {
				return err
			}
			html, err = dom.GetOuterHTML().WithNodeID(rootNode.NodeID).Do(ctx)
			return err
		}),
	)

	if err != nil {
		log.Fatal("Error while performing the automation logic:", err)
	}
	return html
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
	}

	return string(body)
}
