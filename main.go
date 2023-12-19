package main

var base_url string = "https://reddit.com"

func main() {

	var data []Data

	url := base_url + "/r/TwoSentenceHorror/top/?t=day"

	html := Scroller(url)
	links := Unique(LinkGrabber(html))

	for _, v := range links {
		content := SendRequests(base_url + v)
		id := GetText(content, "id")
		var d = Data{
			ID:       id,
			Title:    GetText(content, "post-title"),
			Score:    GetText(content, "score"),
			UserName: GetText(content, "author"),
            Post: GetPost(content, id),
		}
		data = append(data, d)
	}
}
