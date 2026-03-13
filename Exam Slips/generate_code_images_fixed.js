// Fixed version - simpler highlighting without nested tspans
'use strict';

const sharp = require('sharp');
const fs = require('fs');
const path = require('path');

const THEME = {
  bg: '#1E1E1E',
  fg: '#D4D4D4',
  keyword: '#569CD6',
  string: '#CE9178',
  number: '#B5CEA8',
  function: '#DCDCAA',
  type: '#4EC9B0',
  comment: '#6A9955',
  lineNum: '#858585',
  preprocessor: '#C586C0',
};

function xmlEscape(str) {
  return String(str)
    .replace(/&/g, '&amp;')
    .replace(/</g, '&lt;')
    .replace(/>/g, '&gt;')
    .replace(/"/g, '&quot;')
    .replace(/'/g, '&apos;');
}

function generateCodeSVG(code, title) {
  const lines = code.split('\n');
  const lineHeight = 18;
  const padding = 50;
  const titleBarHeight = 42;
  const lineNumWidth = 70;
  const codeStartX = lineNumWidth + 30;
  const width = 1400;
  const maxLines = Math.min(lines.length, 100); // Limit to 100 lines
  const height = titleBarHeight + padding + (maxLines * lineHeight) + padding;
  
  let codeContent = '';
  
  for (let i = 0; i < maxLines; i++) {
    const lineNum = (i + 1).toString().padStart(4, ' ');
    const y = titleBarHeight + padding + (i * lineHeight);
    const escapedLine = xmlEscape(lines[i]);
    
    // Line number
    codeContent += `  <text x="30" y="${y}" font-family="Consolas,Monaco,Courier,monospace" font-size="13" fill="${THEME.lineNum}">${lineNum}</text>\n`;
    
    // Code line (plain, no syntax highlighting to avoid XML issues)
    codeContent += `  <text x="${codeStartX}" y="${y}" font-family="Consolas,Monaco,Courier,monospace" font-size="13" fill="${THEME.fg}" xml:space="preserve">${escapedLine}</text>\n`;
  }
  
  if (lines.length > maxLines) {
    const y = titleBarHeight + padding + (maxLines * lineHeight) + 10;
    codeContent += `  <text x="30" y="${y}" font-family="Consolas,Monaco,monospace" font-size="12" fill="${THEME.comment}">... (${lines.length - maxLines} more lines omitted)</text>\n`;
  }
  
  const svg = `<svg xmlns="http://www.w3.org/2000/svg" width="${width}" height="${height}">
  <rect width="${width}" height="${height}" fill="${THEME.bg}" rx="10"/>
  <rect width="${width}" height="${titleBarHeight}" fill="#252526" rx="10"/>
  <rect y="${titleBarHeight}" width="${width}" height="${height - titleBarHeight}" fill="${THEME.bg}"/>
  
  <text x="20" y="27" font-family="Segoe UI,system-ui,sans-serif" font-size="13" fill="${THEME.fg}" font-weight="600">${xmlEscape(title)}</text>
  
  <circle cx="${width-70}" cy="20" r="5.5" fill="#ED594A"/>
  <circle cx="${width-50}" cy="20" r="5.5" fill="#FDD800"/>
  <circle cx="${width-30}" cy="20" r="5.5" fill="#5AC05A"/>
  
${codeContent}
</svg>`;
  
  return svg;
}

async function generateImage(code, outputPath, title) {
  try {
    const svg = generateCodeSVG(code, title);
    const buffer = Buffer.from(svg, 'utf-8');
    
    await sharp(buffer)
      .png({ compressionLevel: 9 })
      .toFile(outputPath);
    
    return true;
  } catch (err) {
    console.error(`  ✗ Error: ${err.message}`);
    return false;
  }
}

async function main() {
  const baseDir = '/home/amitdevx/jupyter_notebook/sem4/Exam Slips';
  const outputDir = path.join(baseDir, 'code_images');
  
  if (!fs.existsSync(outputDir)) {
    fs.mkdirSync(outputDir, { recursive: true });
  }
  
  console.log('🎨 Generating code images with VS Code dark theme...\n');
  
  let totalGenerated = 0;
  let totalErrors = 0;
  
  for (let slip = 1; slip <= 30; slip++) {
    const slipNum = slip.toString().padStart(2, '0');
    process.stdout.write(`📂 Slip ${slipNum}: `);
    
    const slipFolder = path.join(outputDir, `Slip_${slipNum}`);
    if (!fs.existsSync(slipFolder)) {
      fs.mkdirSync(slipFolder, { recursive: true });
    }
    
    let slipCount = 0;
    
    // DS OptionA
    const dsDir = path.join(baseDir, 'Section I: Data Structures-II', `Slip_${slipNum}`);
    const optAFile = path.join(dsDir, `Slip_${slipNum}_Q1_OptionA.c`);
    
    if (fs.existsSync(optAFile)) {
      let code = fs.readFileSync(optAFile, 'utf-8');
      
      if (code.includes('#include "btree.h"')) {
        const btreeFile = path.join(dsDir, 'btree.h');
        if (fs.existsSync(btreeFile)) {
          let btree = fs.readFileSync(btreeFile, 'utf-8');
          btree = btree.replace(/#ifndef.*?#define.*?\n/gs, '').replace(/#endif/g, '').trim();
          btree = btree.replace(/#include\s*<stdio\.h>/g, '').replace(/#include\s*<stdlib\.h>/g, '');
          code = code.replace('#include "btree.h"', '\n' + btree.trim());
        }
      }
      
      const outPath = path.join(slipFolder, `Slip_${slipNum}_Q1_OptionA.png`);
      if (await generateImage(code, outPath, `Slip ${slipNum} - Q1 Option A (C)`)) {
        slipCount++;
        totalGenerated++;
      } else {
        totalErrors++;
      }
    }
    
    // DS OptionB
    const optBFile = path.join(dsDir, `Slip_${slipNum}_Q1_OptionB.c`);
    
    if (fs.existsSync(optBFile)) {
      let code = fs.readFileSync(optBFile, 'utf-8');
      
      if (code.includes('#include "btree.h"')) {
        const btreeFile = path.join(dsDir, 'btree.h');
        if (fs.existsSync(btreeFile)) {
          let btree = fs.readFileSync(btreeFile, 'utf-8');
          btree = btree.replace(/#ifndef.*?#define.*?\n/gs, '').replace(/#endif/g, '').trim();
          btree = btree.replace(/#include\s*<stdio\.h>/g, '').replace(/#include\s*<stdlib\.h>/g, '');
          code = code.replace('#include "btree.h"', '\n' + btree.trim());
        }
      }
      
      const outPath = path.join(slipFolder, `Slip_${slipNum}_Q1_OptionB.png`);
      if (await generateImage(code, outPath, `Slip ${slipNum} - Q1 Option B (C)`)) {
        slipCount++;
        totalGenerated++;
      } else {
        totalErrors++;
      }
    }
    
    // DBMS SQL
    const dbmsDir = path.join(baseDir, 'Section II: Database Management Systems II', `Slip_${slipNum}`);
    const sqlFile = path.join(dbmsDir, `Slip_${slipNum}_DBMS_Solution.sql`);
    
    if (fs.existsSync(sqlFile)) {
      const code = fs.readFileSync(sqlFile, 'utf-8');
      const outPath = path.join(slipFolder, `Slip_${slipNum}_DBMS_Solution.png`);
      if (await generateImage(code, outPath, `Slip ${slipNum} - DBMS Solution (SQL)`)) {
        slipCount++;
        totalGenerated++;
      } else {
        totalErrors++;
      }
    }
    
    console.log(`✓ ${slipCount} images`);
  }
  
  console.log('\n' + '='.repeat(60));
  console.log(`✅ Complete! Generated ${totalGenerated} code images`);
  if (totalErrors > 0) {
    console.log(`⚠️  ${totalErrors} errors`);
  }
  console.log(`📁 Output: ${outputDir}`);
  console.log('='.repeat(60));
}

main().catch(err => {
  console.error('Fatal error:', err);
  process.exit(1);
});
