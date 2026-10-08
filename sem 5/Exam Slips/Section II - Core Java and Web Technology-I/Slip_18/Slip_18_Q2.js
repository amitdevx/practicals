const http = require('http');
const server = http.createServer((req, res) => {
    res.writeHead(200, { 'Content-Type': 'text/plain' });
    res.end('Hello from Node.js HTTP Server!');
});
server.listen(3000, () => {
    console.log('Server is running at http://localhost:3000/');
    setTimeout(() => process.exit(0), 1000); // Auto-close for testing
});
