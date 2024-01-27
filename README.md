# Grawddit - Reddit Top Posts Scraper

Grawddit is a lightweight tool that fetches the top posts of the day from a specified subreddit on Reddit, focusing on those with the most upvotes.

## Usage

### 1. Clone the Repository:
   ```bash
   git clone https://github.com/nyx6965/grawddit.git
   cd grawddit
   ```

### 2. Run the Project:
  
#### 2.1 Native Golang environment
   ```bash
    go build
    grawddit -subreddit yourdesiredsubreddit -limit 10 -sort new
   ```
   Replace `yourdesiredsubreddit` with the name of the subreddit you want to scrape.
   There is no support of scrapping images and videos yet. So that enter a subreddit the posts them.

#### 2.2 Docker environment
   ```
   docker build -t grawddit:latest .
   docker run -v ./data:/app/data -t grawddit:latest
   ```
   This requires docker to be installed on your machine. The data scraped by the tool is available in the `data` directory post run completion.
   
   The subreddit argument works as follows
   ```
   docker run -v ./data:/app/data -t grawddit:latest -subreddit yourdesiredsubreddit -limit 10 -sort new
   ``` 

## Configuration

You can customize the project by modifying the source code or by passing command-line arguments:

- `-subreddit`: Specify the subreddit you want to scrape (e.g., `-subreddit worldnews`).

## Contribution

Feel free to contribute to the project by submitting bug reports or feature requests.

## License

This project is licensed under the MIT License.

Happy scraping! 🚀
