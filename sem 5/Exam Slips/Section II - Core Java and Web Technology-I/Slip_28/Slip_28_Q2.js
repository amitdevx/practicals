// List files in directory and filter by extensions (.txt, .json, .js)
const fs = require('fs');
const path = require('path');

const targetDir = '.';
const allowedExtensions = ['.txt', '.json', '.js'];

console.log(`Filtering files in '${targetDir}' for: ${allowedExtensions.join(', ')}`);

const files = fs.readdirSync(targetDir);
const filtered = files.filter(f => allowedExtensions.includes(path.extname(f)));

console.log('Matching Files:');
filtered.forEach(f => console.log('  ->', f));
