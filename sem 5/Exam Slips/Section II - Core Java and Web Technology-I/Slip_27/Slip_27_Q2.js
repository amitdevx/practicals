// Read JSON, Modify properties, and Write back
const fs = require('fs');

const jsonPath = 'profile.json';
const initialData = { username: "amit_dev", role: "Student", active: false };

fs.writeFileSync(jsonPath, JSON.stringify(initialData, null, 2));

// Read & parse
const fileData = fs.readFileSync(jsonPath, 'utf8');
const user = JSON.parse(fileData);
console.log('Original Object:', user);

// Modify selected properties
user.role = "Administrator";
user.active = true;
user.lastLogin = "2026-09-26";

// Write back
fs.writeFileSync(jsonPath, JSON.stringify(user, null, 2));
console.log('Updated Object written to file:');
console.log(fs.readFileSync(jsonPath, 'utf8'));

fs.unlinkSync(jsonPath);
