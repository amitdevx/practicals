// Node.js Path Module Operations
const path = require('path');

const samplePath = '/home/user/docs/file.txt';

console.log("=== Node.js Path Module Operations ===");
console.log("Joined Path:   ", path.join('/root', 'projects', 'node_app', 'index.js'));
console.log("Resolved Path: ", path.resolve('temp', 'sample.txt'));
console.log("Directory Name:", path.dirname(samplePath));
console.log("Base Name:     ", path.basename(samplePath));
console.log("Extension:     ", path.extname(samplePath));
console.log("Parsed Object: ", path.parse(samplePath));
