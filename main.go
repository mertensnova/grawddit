package main


var base_url string = "https://reddit.com"

func unique(intSlice []string) []string {
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
func main() {

	var data []Data

	url := base_url + "/r/TwoSentenceHorror/top/?t=day"

	html := SendRequests(url)
	links := unique(LinkGrabber(html))

	for _, v := range links {
		content := SendRequests(base_url + v)

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
