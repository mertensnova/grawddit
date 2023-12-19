const scrolls = 8
let scrollCount = 0

const scrollInterval = setInterval(() => {
    window.scrollTo(0, document.body.scrollHeight)
    scrollCount++

}, 500)

