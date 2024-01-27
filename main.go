package main

import (
	"flag"
	"log"
	"time"

	"github.com/nyx6965/grawddit/scrape"
)

func main() {
	startTime := time.Now()

	var subreddit string
	var limit int
	var category string

	flag.StringVar(&subreddit, "subreddit", "TwoSentenceHorror", "Subreddit")
	flag.IntVar(&limit, "limit", 10, "Number of posts to scrape")
	flag.StringVar(&category, "sort", "top", "Type of sort E.g [new,top,hot]")

	flag.Parse()

	baseDataDir := "./data"
	data, err := scrape.Start(subreddit, limit, category)
	if err != nil {
		log.Println(err)
	}
	if err := scrape.WritetoJSON(data, baseDataDir + "/" + subreddit + ".json" ); err != nil {
		log.Println(err)
	}

	endTime := time.Now()
	elapsedTime := endTime.Sub(startTime)

	log.Println("Done!")
	log.Println("Elapsed Time:", elapsedTime)
}
