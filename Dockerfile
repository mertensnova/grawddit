FROM golang:latest

# Install Google Chrome
RUN apt-get update && apt-get install -y wget gnupg2
RUN wget -q -O - https://dl-ssl.google.com/linux/linux_signing_key.pub | apt-key add -
RUN echo "deb [arch=amd64] http://dl.google.com/linux/chrome/deb/ stable main" >> /etc/apt/sources.list.d/google.list
RUN apt-get update && apt-get install -y google-chrome-stable

# Set work directory
WORKDIR /app
# Copy Files
COPY . .
# Install go packages
RUN go mod download
# Build app
RUN CGO_ENABLED=0 GOOS=linux go build -o grawddit .
# Entrypoint
ENTRYPOINT ["./grawddit"]