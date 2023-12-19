package main

import (
	"fmt"
	"time"
    "flag"
)

var base string = "https://reddit.com"

func main() {


	startTime := time.Now()

	var subreddit string
	flag.StringVar(&subreddit, "subreddit", "TwoSentenceHorror", "Subreddit")

	flag.Parse()

	var data []Data

	suffix := "/r/" + subreddit + "/top/?t=day"
	url := base + suffix

    fmt.Println("Fetching the page...")
	html := Scroller(url)

	links := Unique(LinkGrabber(html, subreddit))

	for k, v := range links {
		fmt.Println(k, "Scrapping -> "+v)
		content := SendRequests(base + v)
		id := GetSubRedditData(content, "id")
		var d = Data{
			ID:        id,
			Title:     GetSubRedditData(content, "post-title"),
			Upvotes:   GetSubRedditData(content, "score"),
			Author:    GetSubRedditData(content, "author"),
			Post:      GetSubRedditPost(content, id),
			CreatedAt: GetSubRedditData(content, "created-timestamp"),
		}
		data = append(data, d)
	}
	WritetoJSON(data, subreddit)
	endTime := time.Now()
	elapsedTime := endTime.Sub(startTime)


	fmt.Println("Done!")
	fmt.Println("Elapsed Time:", elapsedTime)

}
