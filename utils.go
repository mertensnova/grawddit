package main

import (
	"bufio"
	"encoding/json"
	"fmt"
	"io/ioutil"
	"log"
	"math/rand"
	"os"
	"time"
)

func WritetoJSON(data []Data, subreddit string) {

    fmt.Println("\n\nWriting to JSON...")
	file_name := subreddit + ".json"
	file, err := os.Create(file_name)

	if err != nil {
		fmt.Println("Error creating file:", err)
		return
	}

	defer file.Close()

	encoder := json.NewEncoder(file)

	if err := encoder.Encode(data); err != nil {
		log.Fatalln("Error encoding JSON:", err)
		return
	}

	return
}

func ParseDate(date string) string {
	parsedTime, err := time.Parse(time.RFC3339Nano, date)
	if err != nil {
		fmt.Println("Error:", err)
	}

	formattedString := parsedTime.Format("January 2, 2006 at 15:04:05 MST")
	return formattedString
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

func ReadScripts(srcipt string) string {
	content, err := ioutil.ReadFile(srcipt)
	if err != nil {
		log.Fatal(err)
	}
	return string(content)
}
