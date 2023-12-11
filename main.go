package main

var base_url string = "https://www.reddit.com"

func main() {
	url := base_url + "/r/TwoSentenceHorror/top/?t=day"
	html := SendRequests(url)
	links := LinkGrabber(html)

	for _, v := range links {
       html := SendRequests(v)
       GetTitle(html)
	}
}
