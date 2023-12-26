package scrape

import (
	"context"
	"fmt"
	"io"
	"log"
	"net/http"
	"time"

	"github.com/chromedp/cdproto/dom"
	"github.com/chromedp/chromedp"
)

var script = `const scrollInterval = setInterval(() => {
    window.scrollTo(0, document.body.scrollHeight)
}, 500)
`

func Scroller(target string) (string, error) {
	log.Println("Scrolling the page...")

	ctx, cancel := chromedp.NewContext(
		context.Background(),
	)
	defer cancel()
	var html string
	err := chromedp.Run(ctx,
		chromedp.Navigate(target),
		chromedp.Evaluate(script, nil),
		chromedp.Sleep(3000*time.Millisecond),
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
		return "", fmt.Errorf("error while performing the automation logic: %w", err)

	}
	return html, nil
}

func SendRequests(value string) (string, error) {
	client := &http.Client{
		Timeout: 30 * time.Second,
	}

	request, err := http.NewRequest("GET", value, nil)
	if err != nil {
		return "", fmt.Errorf("error creating request: %w", err)
	}

	request.Header.Set("User-Agent", RandomUserAgent())
	response, err := client.Do(request)
	if err != nil {
		return "", fmt.Errorf("error sending request: %w", err)
	}
	defer response.Body.Close()

	body, err := io.ReadAll(response.Body)
	if err != nil {
		return "", fmt.Errorf("error reading response body: %w", err)
	}

	return string(body), nil
}
