// Generate PNG images for all C and SQL code with VS Code dark theme
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

const C_KW = ['int','char','float','double','void','long','short','unsigned','signed','struct','typedef','enum','union','const','static','extern','if','else','while','for','do','switch','case','default','break','continue','return','sizeof','NULL'];
const SQL_KW = ['SELECT','FROM','WHERE','INSERT','INTO','VALUES','UPDATE','SET','DELETE','CREATE','TABLE','DROP','ALTER','PRIMARY','KEY','FOREIGN','REFERENCES','AS','DECLARE','BEGIN','END','IF','THEN','ELSE','ELSIF','LOOP','WHILE','FOR','IN','RETURN','RETURNS','FUNCTION','PROCEDURE','TRIGGER','BEFORE','AFTER','EACH','ROW','VARCHAR','INT','DATE','NUMERIC','CHECK','UNIQUE','NOT','NULL','AND','OR','LIKE','BETWEEN','ORDER','BY','GROUP','HAVING','JOIN','LEFT','RIGHT','INNER','OUTER','ON','CASCADE','CONSTRAINT','LANGUAGE','plpgsql','RAISE','NOTICE','EXCEPTION','COUNT','SUM','AVG','MAX','MIN'];

function xmlEscape(str) {
  return String(str).replace(/&/g,'&amp;').replace(/</g,'&lt;').replace(/>/g,'&gt;').replace(/"/g,'&quot;').replace(/'/g,'&apos;');
}

function highlightC(line) {
  let result = xmlEscape(line);
  
  // Preprocessor directives
  result = result.replace(/^(\s*)(#\w+.*?)$/g, (m, ws, directive) => {
    return `${ws}<tspan fill="${THEME.preprocessor}">${directive}</tspan>`;
  });
  
  // Strings
  result = result.replace(/"([^"]*)"/g, `<tspan fill="${THEME.string}">"$1"</tspan>`);
  
  // Numbers
  result = result.replace(/\b(\d+)\b/g, `<tspan fill="${THEME.number}">$1</tspan>`);
  
  // Keywords
  C_KW.forEach(kw => {
    const re = new RegExp(`\\b(${kw})\\b`, 'g');
    result = result.replace(re, `<tspan fill="${THEME.keyword}">$1</tspan>`);
  });
  
  // Types
  result = result.replace(/\b(Node|Tree|Graph|Stack|Queue)\b/g, `<tspan fill="${THEME.type}">$1</tspan>`);
  
  return result;
}

function highlightSQL(line) {
  let result = xmlEscape(line);
  
  // Strings
  result = result.replace(/'([^']*)'/g, `<tspan fill="${THEME.string}">'$1'</tspan>`);
  
  // Numbers
  result = result.replace(/\b(\d+)\b/g, `<tspan fill="${THEME.number}">$1</tspan>`);
  
  // Keywords (case-insensitive)
  SQL_KW.forEach(kw => {
    const re = new RegExp(`\\b(${kw})\\b`, 'gi');
    result = result.replace(re, (match) => `<tspan fill="${THEME.keyword}">${match}</tspan>`);
  });
  
  return result;
}

function generateCodeSVG(code, lang, title) {
  const lines = code.split('\n');
  const lineHeight = 19;
  const padding = 50;
  const titleBarHeight = 42;
  const lineNumWidth = 80;
  const codeStartX = lineNumWidth + 20;
  const width = 1400;
  const maxLinesPerImage = 80; // Split if too many lines
  
  // Calculate actual lines needed
  const actualLines = Math.min(lines.length, maxLinesPerImage);
  const height = titleBarHeight + padding + (actualLines * lineHeight) + padding;
  
  let codeContent = '';
  
  for (let i = 0; i < actualLines; i++) {
    const lineNum = (i + 1).toString().padStart(4, ' ');
    const y = titleBarHeight + padding + (i * lineHeight);
    const highlighted = lang === 'c' ? highlightC(lines[i]) : highlightSQL(lines[i]);
    
    codeContent += `  <text x="30" y="${y}" font-family="Consolas,Monaco,monospace" font-size="13" fill="${THEME.lineNum}">${lineNum}</text>\n`;
    codeContent += `  <text x="${codeStartX}" y="${y}" font-family="Consolas,Monaco,monospace" font-size="13" xml:space="preserve">${highlighted}</text>\n`;
  }
  
  if (lines.length > maxLinesPerImage) {
    codeContent += `  <text x="30" y="${titleBarHeight + padding + (actualLines * lineHeight) + 20}" font-family="Consolas,Monaco,monospace" font-size="13" fill="${THEME.comment}">... (${lines.length - maxLinesPerImage} more lines)</text>\n`;
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

async function generateImage(code, lang, outputPath, title) {
  try {
    const svg = generateCodeSVG(code, lang, title);
    const buffer = Buffer.from(svg, 'utf-8');
    
    await sharp(buffer)
      .png({ compressionLevel: 9 })
      .toFile(outputPath);
    
    return true;
  } catch (err) {
    console.error(`  ✗ Error generating ${outputPath}:`, err.message);
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
  
  for (let slip = 1; slip <= 30; slip++) {
    const slipNum = slip.toString().padStart(2, '0');
    console.log(`📂 Slip ${slipNum}:`);
    
    const slipFolder = path.join(outputDir, `Slip_${slipNum}`);
    if (!fs.existsSync(slipFolder)) {
      fs.mkdirSync(slipFolder, { recursive: true });
    }
    
    // Process DS OptionA
    const dsDir = path.join(baseDir, 'Section I: Data Structures-II', `Slip_${slipNum}`);
    const optAFile = path.join(dsDir, `Slip_${slipNum}_Q1_OptionA.c`);
    
    if (fs.existsSync(optAFile)) {
      let code = fs.readFileSync(optAFile, 'utf-8');
      
      // Inline btree.h if needed
      if (code.includes('#include "btree.h"')) {
        const btreeFile = path.join(dsDir, 'btree.h');
        if (fs.existsSync(btreeFile)) {
          let btree = fs.readFileSync(btreeFile, 'utf-8');
          btree = btree.replace(/#ifndef.*?#define.*?\n/gs, '');
          btree = btree.replace(/#endif/g, '').trim();
          btree = btree.replace(/#include\s*<stdio\.h>/g, '');
          btree = btree.replace(/#include\s*<stdlib\.h>/g, '');
          code = code.replace('#include "btree.h"', '\n' + btree.trim());
        }
      }
      
      const outPath = path.join(slipFolder, `Slip_${slipNum}_Q1_OptionA.png`);
      const success = await generateImage(code, 'c', outPath, `Slip ${slipNum} - Q1 Option A`);
      if (success) {
        console.log(`  ✓ Q1 Option A`);
        totalGenerated++;
      }
    }
    
    // Process DS OptionB
    const optBFile = path.join(dsDir, `Slip_${slipNum}_Q1_OptionB.c`);
    
    if (fs.existsSync(optBFile)) {
      let code = fs.readFileSync(optBFile, 'utf-8');
      
      if (code.includes('#include "btree.h"')) {
        const btreeFile = path.join(dsDir, 'btree.h');
        if (fs.existsSync(btreeFile)) {
          let btree = fs.readFileSync(btreeFile, 'utf-8');
          btree = btree.replace(/#ifndef.*?#define.*?\n/gs, '');
          btree = btree.replace(/#endif/g, '').trim();
          btree = btree.replace(/#include\s*<stdio\.h>/g, '');
          btree = btree.replace(/#include\s*<stdlib\.h>/g, '');
          code = code.replace('#include "btree.h"', '\n' + btree.trim());
        }
      }
      
      const outPath = path.join(slipFolder, `Slip_${slipNum}_Q1_OptionB.png`);
      const success = await generateImage(code, 'c', outPath, `Slip ${slipNum} - Q1 Option B`);
      if (success) {
        console.log(`  ✓ Q1 Option B`);
        totalGenerated++;
      }
    }
    
    // Process DBMS SQL
    const dbmsDir = path.join(baseDir, 'Section II: Database Management Systems II', `Slip_${slipNum}`);
    const sqlFile = path.join(dbmsDir, `Slip_${slipNum}_DBMS_Solution.sql`);
    
    if (fs.existsSync(sqlFile)) {
      const code = fs.readFileSync(sqlFile, 'utf-8');
      const outPath = path.join(slipFolder, `Slip_${slipNum}_DBMS_Solution.png`);
      const success = await generateImage(code, 'sql', outPath, `Slip ${slipNum} - DBMS Solution`);
      if (success) {
        console.log(`  ✓ DBMS Solution`);
        totalGenerated++;
      }
    }
  }
  
  console.log('\n' + '='.repeat(60));
  console.log(`✅ Complete! Generated ${totalGenerated} code images`);
  console.log(`📁 Output: ${outputDir}`);
  console.log('='.repeat(60));
}

main().catch(err => {
  console.error('Fatal error:', err);
  process.exit(1);
});
