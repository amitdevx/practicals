// Node.js HTTP Server
const http = require('http');

const PORT = 3000;
const server = http.createServer((req, res) => {
    res.writeHead(200, { 'Content-Type': 'text/plain' });
    res.end('Hello from Node.js HTTP Server! Request received successfully.\n');
});

// Self-test snippet: listens briefly and confirms
server.listen(PORT, () => {
    console.log(`Server is running at http://localhost:${PORT}/`);
    server.close(); // Close immediately for test automation
});
