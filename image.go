package main

import (
	"image/jpeg"
	"image/png"
	"log"
	"net/http"
	"os"
	"regexp"
)

func JPEGHandler(f *os.File, res *http.Response) {
	myImage, err := jpeg.Decode(res.Body)
	if err != nil {
		log.Fatalln(err)
	}

	defer f.Close()
	if err = jpeg.Encode(f, myImage, nil); err != nil {
		log.Printf("failed to encode: %v", err)
	}
}

func PNGHandler(f *os.File, res *http.Response) {

	myImage, err := png.Decode(res.Body)

	if err != nil {
		log.Fatalln(err)
	}

	defer f.Close()

	if err = png.Encode(f, myImage); err != nil {
		log.Printf("failed to encode: %v", err)
	}
}

func DownloadImage(url string, id string, subreddit string) {
	 if url == "" {
        return
    }

    res, err := http.Get(url)
	if err != nil {
		log.Println(err)
	}

	if res.StatusCode != 200 {
		log.Printf("Status code error: %d %s", res.StatusCode, res.Status)
	}

	defer res.Body.Close()

	jpegRegex := regexp.MustCompile(`(?i)\.jpe?g$`)
	pngRegex := regexp.MustCompile(`(?i)\.png$`)

	isJPEG := jpegRegex.MatchString(url)
	isPNG := pngRegex.MatchString(url)

	if isJPEG {

		name := "./" + subreddit + "/" + id + ".jpeg"
		f, err := os.Create(name)

		if err != nil {
			log.Fatalln(err)
		}
		JPEGHandler(f, res)
	}

	if isPNG {
		name := "./" + subreddit + "/" + id + ".png"
		f, err := os.Create(name)

		if err != nil {
			log.Fatalln(err)
		}
		PNGHandler(f, res)
	}

}
