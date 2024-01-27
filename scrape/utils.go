package scrape

import (
	"encoding/json"
	"fmt"
	"log"
	"math/rand"
	"os"
	"time"
)

func CreateDir(name string) {
	if err := os.Mkdir(name, os.ModePerm); err != nil {
		log.Println(err)
	}
}

func WritetoJSON(data []Data, file_name string) error {
	log.Println("Writing to JSON...")

	file, err := os.Create(file_name)
	if err != nil {
		return fmt.Errorf("error creating file: %w", err)

	}
	defer file.Close()

	encoder := json.NewEncoder(file)
	if err := encoder.Encode(data); err != nil {
		return fmt.Errorf("error encoding JSON: %w", err)
	}
	return nil
}

func ParseDate(date string) (string, error) {
	parsedTime, err := time.Parse(time.RFC3339Nano, date)
	if err != nil {
		return "", fmt.Errorf("error parsing date: %w", err)
	}

	formattedString := parsedTime.Format("January 2, 2006 at 15:04:05 MST")
	return formattedString, nil
}

func RandomUserAgent() string {
	r := rand.Intn(len(UserAgents))
	return UserAgents[r]
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
