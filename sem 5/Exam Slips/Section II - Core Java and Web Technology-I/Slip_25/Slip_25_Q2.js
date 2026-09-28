// Directory Management & JSON Parsing in Node.js
const fs = require('fs');
const path = require('path');

const dirName = 'test_dir';
const jsonFile = path.join(dirName, 'data.json');

// 1. Create Directory
if (!fs.existsSync(dirName)) {
    fs.mkdirSync(dirName);
    console.log(`[+] Directory '${dirName}' created.`);
}

// 2. Write structured JSON
const student = { name: "Snehal", roll: 105, marks: [85, 90, 78] };
fs.writeFileSync(jsonFile, JSON.stringify(student, null, 2));
console.log('[+] JSON data written.');

// 3. Read and Parse JSON
const rawData = fs.readFileSync(jsonFile, 'utf8');
const parsed = JSON.parse(rawData);
console.log('[+] Parsed JSON Student Name:', parsed.name);

// Cleanup
fs.unlinkSync(jsonFile);
fs.rmdirSync(dirName);
console.log('[+] Cleanup complete.');
