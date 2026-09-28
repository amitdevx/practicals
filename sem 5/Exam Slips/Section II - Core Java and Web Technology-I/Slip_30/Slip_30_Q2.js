// Mini File Management CLI in Node.js
const fs = require('fs');
const path = require('path');

const manageFile = (action, filename, content = '') => {
    switch (action) {
        case 'create':
            fs.writeFileSync(filename, content);
            console.log(`[+] Created '${filename}'.`);
            break;
        case 'read':
            if (fs.existsSync(filename)) {
                console.log(`--- Content of '${filename}' ---`);
                console.log(fs.readFileSync(filename, 'utf8'));
            } else {
                console.log(`[-] File '${filename}' not found.`);
            }
            break;
        case 'update':
            if (fs.existsSync(filename)) {
                fs.appendFileSync(filename, content);
                console.log(`[+] Appended content to '${filename}'.`);
            }
            break;
        case 'delete':
            if (fs.existsSync(filename)) {
                fs.unlinkSync(filename);
                console.log(`[+] Deleted '${filename}'.`);
            }
            break;
        default:
            console.log('Unknown action. Available: create, read, update, delete');
    }
};

// Demonstration
const testFile = 'cli_test.txt';
manageFile('create', testFile, 'Hello Node CLI!\n');
manageFile('update', testFile, 'Second Line added.\n');
manageFile('read', testFile);
manageFile('delete', testFile);
