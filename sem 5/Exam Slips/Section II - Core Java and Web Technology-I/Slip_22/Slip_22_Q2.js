// Asynchronous File Operations using Node.js fs module
const fs = require('fs');

const filename = 'async_demo.txt';

fs.writeFile(filename, 'Initial content written asynchronously.', (err) => {
    if (err) throw err;
    console.log('[+] File written successfully.');

    fs.readFile(filename, 'utf8', (err, data) => {
        if (err) throw err;
        console.log('[+] File contents:', data);

        fs.unlink(filename, (err) => {
            if (err) throw err;
            console.log('[+] File cleaned up.');
        });
    });
});
