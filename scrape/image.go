package scrape

import (
	"fmt"
	"image/jpeg"
	"image/png"
	"net/http"
	"os"
	"regexp"
)

func JPEGHandler(f *os.File, res *http.Response) error {
	myImage, err := jpeg.Decode(res.Body)
	if err != nil {
		return err
	}

	defer f.Close()
	if err = jpeg.Encode(f, myImage, nil); err != nil {
		return fmt.Errorf("failed to encode: %w", err)
	}
	return nil
}

func PNGHandler(f *os.File, res *http.Response) error {
	myImage, err := png.Decode(res.Body)
	if err != nil {
		return err
	}

	defer f.Close()

	if err = png.Encode(f, myImage); err != nil {
		return fmt.Errorf("failed to encode: %w", err)
	}
	return nil
}

func DownloadImage(url string, id string, subreddit string) error {
	if url == "" {
		return nil
	}

	res, err := http.Get(url)
	if err != nil {
		return err
	}

	if res.StatusCode != 200 {
		return fmt.Errorf("status code error: %d %s", res.StatusCode, res.Status)
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
			return err
		}
		return JPEGHandler(f, res)
	}

	if isPNG {
		name := "./" + subreddit + "/" + id + ".png"
		f, err := os.Create(name)
		if err != nil {
			return err
		}
		return PNGHandler(f, res)
	}
	return nil
}
