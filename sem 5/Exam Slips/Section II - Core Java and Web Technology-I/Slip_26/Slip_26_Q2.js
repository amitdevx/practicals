// Copy, Rename and Delete Files Asynchronously using Node.js fs
const fs = require('fs');

const src = 'source.txt';
const copy = 'copy.txt';
const renamed = 'renamed.txt';

fs.writeFileSync(src, 'Sample data to copy.');

fs.copyFile(src, copy, (err) => {
    if (err) throw err;
    console.log('[+] File copied successfully.');

    fs.rename(copy, renamed, (err) => {
        if (err) throw err;
        console.log('[+] File renamed successfully.');

        fs.unlink(renamed, (err) => {
            if (err) throw err;
            console.log('[+] File deleted successfully.');
            fs.unlinkSync(src);
        });
    });
});
