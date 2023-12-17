package main

import "fmt"


var base_url string = "https://reddit.com"

func main() {

	var data []Data

	url := base_url + "/r/TwoSentenceHorror/top/?t=day"

	html := SendRequests(url)
	links := Unique(LinkGrabber(html))

	for _, v := range links {
		content := Scroller(base_url + v)
        fmt.Println(v)
        id := GetText(content,"id")
		var d = Data{
            ID : id,
			Title: GetText(content,"post-title"),
            Score: GetText(content,"score"),
            UserName: GetText(content,"author"),
		}

         GetPost(content,id)
        data = append(data, d)
	}
}
