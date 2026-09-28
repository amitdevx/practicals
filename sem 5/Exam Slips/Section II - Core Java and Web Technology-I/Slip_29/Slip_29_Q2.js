// File statistics using fs.stat()
const fs = require('fs');

const target = __filename;

fs.stat(target, (err, stats) => {
    if (err) {
        console.error('Error fetching stats:', err);
        return;
    }
    console.log('=== File Statistics ===');
    console.log('Target:           ', target);
    console.log('File Size:        ', stats.size, 'bytes');
    console.log('Is Directory:     ', stats.isDirectory());
    console.log('Is File:          ', stats.isFile());
    console.log('Created At:       ', stats.birthtime);
    console.log('Last Modified:    ', stats.mtime);
    console.log('Last Accessed:    ', stats.atime);
});
