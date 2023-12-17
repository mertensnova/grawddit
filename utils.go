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

	"github.com/tebeka/selenium"
	"golang.org/x/net/html"
)

func Scroller(target string) string {

    fmt.Println("PR inS")
	caps := selenium.Capabilities{"browserName": "chrome"}
	wd, err := selenium.NewRemote(caps, "http://192.168.1.112:4444/wd/hub")
	if err != nil {
		log.Fatal(err)
	}
	defer wd.Quit()

	err = wd.Get(target)
	if err != nil {
		log.Fatal(err)
	}

	for i := 0; i < 3; i++ {
		time.Sleep(2 * time.Second) 
		_, err := wd.ExecuteScript("window.scrollTo(0, document.body.scrollHeight);", nil)
		if err != nil {
			log.Fatal(err)
		}
	}

	content, err := wd.PageSource()
	if err != nil {
		log.Fatal(err)
	}

    fmt.Println(content)
    return content
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




