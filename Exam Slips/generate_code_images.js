// generate_code_images.js - Convert all C and SQL code to PNG images with VS Code dark theme
'use strict';

const sharp = require('sharp');
const fs = require('fs');
const path = require('path');

// VS Code Dark+ theme colors
const THEME = {
  bg: '#1E1E1E',
  fg: '#D4D4D4',
  comment: '#6A9955',
  keyword: '#569CD6',
  string: '#CE9178',
  number: '#B5CEA8',
  function: '#DCDCAA',
  type: '#4EC9B0',
  operator: '#D4D4D4',
  lineNum: '#858585',
  lineNumBg: '#1E1E1E',
};

// C keywords
const C_KEYWORDS = new Set([
  'int', 'char', 'float', 'double', 'void', 'long', 'short', 'unsigned', 'signed',
  'struct', 'typedef', 'enum', 'union', 'const', 'static', 'extern', 'auto', 'register',
  'if', 'else', 'while', 'for', 'do', 'switch', 'case', 'default', 'break', 'continue',
  'return', 'goto', 'sizeof'
]);

// SQL keywords
const SQL_KEYWORDS = new Set([
  'SELECT', 'FROM', 'WHERE', 'INSERT', 'INTO', 'VALUES', 'UPDATE', 'SET', 'DELETE',
  'CREATE', 'TABLE', 'DROP', 'ALTER', 'PRIMARY', 'KEY', 'FOREIGN', 'REFERENCES',
  'AS', 'DECLARE', 'BEGIN', 'END', 'IF', 'THEN', 'ELSE', 'ELSIF', 'LOOP', 'WHILE',
  'FOR', 'IN', 'RETURN', 'RETURNS', 'FUNCTION', 'PROCEDURE', 'TRIGGER', 'BEFORE',
  'AFTER', 'EACH', 'ROW', 'VARCHAR', 'INT', 'DATE', 'NUMERIC', 'CHECK', 'UNIQUE',
  'NOT', 'NULL', 'AND', 'OR', 'LIKE', 'BETWEEN', 'ORDER', 'BY', 'GROUP', 'HAVING',
  'JOIN', 'LEFT', 'RIGHT', 'INNER', 'OUTER', 'ON', 'CASCADE', 'CONSTRAINT', 'INDEX',
  'LANGUAGE', 'plpgsql', 'NOTICE', 'RAISE', 'EXCEPTION', 'COUNT', 'SUM', 'AVG', 'MAX', 'MIN'
]);

function xmlEscape(str) {
  return String(str)
    .replace(/&/g, '&amp;')
    .replace(/</g, '&lt;')
    .replace(/>/g, '&gt;')
    .replace(/"/g, '&quot;');
}

function highlightCCode(code) {
  const lines = code.split('\n');
  let html = '';
  
  lines.forEach((line, idx) => {
    const lineNum = idx + 1;
    let highlighted = line;
    
    // Highlight strings
    highlighted = highlighted.replace(/"([^"]*)"/g, (m, str) => {
      return `<tspan fill="${THEME.string}">"${xmlEscape(str)}"</tspan>`;
    });
    
    // Highlight numbers
    highlighted = highlighted.replace(/\b(\d+)\b/g, (m) => {
      return `<tspan fill="${THEME.number}">${m}</tspan>`;
    });
    
    // Highlight keywords
    C_KEYWORDS.forEach(kw => {
      const regex = new RegExp(`\\b(${kw})\\b`, 'g');
      highlighted = highlighted.replace(regex, `<tspan fill="${THEME.keyword}">${kw}</tspan>`);
    });
    
    // Highlight function calls (word followed by ()
    highlighted = highlighted.replace(/\b([a-zA-Z_]\w*)\s*\(/g, (m, fn) => {
      return `<tspan fill="${THEME.function}">${fn}</tspan>(`;
    });
    
    // Highlight types
    highlighted = highlighted.replace(/\b(Node|struct)\b/g, (m) => {
      return `<tspan fill="${THEME.type}">${m}</tspan>`;
    });
    
    html += `<tspan x="80" dy="18" fill="${THEME.lineNum}" font-family="Consolas,Monaco,monospace">${lineNum.toString().padStart(3, ' ')}</tspan>`;
    html += `<tspan x="150" fill="${THEME.fg}" font-family="Consolas,Monaco,monospace">${highlighted}</tspan>\n`;
  });
  
  return html;
}

function highlightSQLCode(code) {
  const lines = code.split('\n');
  let html = '';
  
  lines.forEach((line, idx) => {
    const lineNum = idx + 1;
    let highlighted = xmlEscape(line);
    
    // Highlight strings
    highlighted = highlighted.replace(/'([^']*)'/g, (m, str) => {
      return `<tspan fill="${THEME.string}">'${str}'</tspan>`;
    });
    
    // Highlight numbers
    highlighted = highlighted.replace(/\b(\d+)\b/g, (m) => {
      return `<tspan fill="${THEME.number}">${m}</tspan>`;
    });
    
    // Highlight SQL keywords
    SQL_KEYWORDS.forEach(kw => {
      const regex = new RegExp(`\\b(${kw})\\b`, 'gi');
      highlighted = highlighted.replace(regex, (m) => {
        return `<tspan fill="${THEME.keyword}">${m}</tspan>`;
      });
    });
    
    // Highlight function names
    highlighted = highlighted.replace(/\b([a-zA-Z_]\w*)\s*\(/g, (m, fn) => {
      return `<tspan fill="${THEME.function}">${fn}</tspan>(`;
    });
    
    html += `<tspan x="80" dy="18" fill="${THEME.lineNum}">${lineNum.toString().padStart(3, ' ')}</tspan>`;
    html += `<tspan x="150" fill="${THEME.fg}">${highlighted}</tspan>\n`;
  });
  
  return html;
}

function generateCodeSVG(code, lang, title) {
  const lines = code.split('\n');
  const lineCount = lines.length;
  const width = 1400;
  const height = Math.max(600, lineCount * 18 + 120);
  
  const highlighted = lang === 'c' ? highlightCCode(code) : highlightSQLCode(code);
  
  const svg = `<?xml version="1.0" encoding="UTF-8"?>
<svg xmlns="http://www.w3.org/2000/svg" width="${width}" height="${height}" viewBox="0 0 ${width} ${height}">
  <!-- Background -->
  <rect width="${width}" height="${height}" fill="${THEME.bg}" rx="12"/>
  
  <!-- Title bar -->
  <rect width="${width}" height="40" fill="#252526" rx="12"/>
  <rect y="40" width="${width}" height="${height-40}" fill="${THEME.bg}"/>
  
  <!-- Title -->
  <text x="20" y="26" font-family="Segoe UI,Arial,sans-serif" font-size="13" fill="${THEME.fg}" font-weight="600">${xmlEscape(title)}</text>
  
  <!-- Code -->
  <text x="0" y="70" font-size="14" xml:space="preserve">
${highlighted}
  </text>
</svg>`;
  
  return svg;
}

async function generateImage(code, lang, outputPath, title) {
  const svg = generateCodeSVG(code, lang, title);
  const buffer = Buffer.from(svg, 'utf-8');
  
  await sharp(buffer)
    .png()
    .toFile(outputPath);
  
  console.log(`✓ Generated: ${outputPath}`);
}

async function processAllSlips() {
  const baseDir = '/home/amitdevx/jupyter_notebook/sem4/Exam Slips';
  const outputDir = path.join(baseDir, 'code_images');
  
  // Create output directory
  if (!fs.existsSync(outputDir)) {
    fs.mkdirSync(outputDir, { recursive: true });
  }
  
  console.log('Generating code images for all 30 slips...\n');
  
  for (let slip = 1; slip <= 30; slip++) {
    const slipNum = slip.toString().padStart(2, '0');
    console.log(`Processing Slip ${slipNum}...`);
    
    // Create slip folder
    const slipFolder = path.join(outputDir, `Slip_${slipNum}`);
    if (!fs.existsSync(slipFolder)) {
      fs.mkdirSync(slipFolder);
    }
    
    // DS OptionA
    const dsDir = path.join(baseDir, 'Section I: Data Structures-II', `Slip_${slipNum}`);
    const optA = path.join(dsDir, `Slip_${slipNum}_Q1_OptionA.c`);
    if (fs.existsSync(optA)) {
      let code = fs.readFileSync(optA, 'utf-8');
      
      // Inline btree.h if needed
      if (code.includes('#include "btree.h"')) {
        const btreeFile = path.join(dsDir, 'btree.h');
        if (fs.existsSync(btreeFile)) {
          let btree = fs.readFileSync(btreeFile, 'utf-8');
          btree = btree.replace(/#ifndef.*?#define.*?\n/gs, '');
          btree = btree.replace(/#endif/g, '');
          btree = btree.replace(/#include\s*<stdio\.h>/g, '');
          btree = btree.replace(/#include\s*<stdlib\.h>/g, '');
          btree = btree.trim();
          code = code.replace('#include "btree.h"', btree);
        }
      }
      
      const outPath = path.join(slipFolder, `Slip_${slipNum}_Q1_OptionA.png`);
      await generateImage(code, 'c', outPath, `Slip ${slipNum} - Q1 Option A (C)`);
    }
    
    // DS OptionB
    const optB = path.join(dsDir, `Slip_${slipNum}_Q1_OptionB.c`);
    if (fs.existsSync(optB)) {
      let code = fs.readFileSync(optB, 'utf-8');
      
      if (code.includes('#include "btree.h"')) {
        const btreeFile = path.join(dsDir, 'btree.h');
        if (fs.existsSync(btreeFile)) {
          let btree = fs.readFileSync(btreeFile, 'utf-8');
          btree = btree.replace(/#ifndef.*?#define.*?\n/gs, '');
          btree = btree.replace(/#endif/g, '');
          btree = btree.replace(/#include\s*<stdio\.h>/g, '');
          btree = btree.replace(/#include\s*<stdlib\.h>/g, '');
          btree = btree.trim();
          code = code.replace('#include "btree.h"', btree);
        }
      }
      
      const outPath = path.join(slipFolder, `Slip_${slipNum}_Q1_OptionB.png`);
      await generateImage(code, 'c', outPath, `Slip ${slipNum} - Q1 Option B (C)`);
    }
    
    // DBMS SQL
    const dbmsDir = path.join(baseDir, 'Section II: Database Management Systems II', `Slip_${slipNum}`);
    const sqlFile = path.join(dbmsDir, `Slip_${slipNum}_DBMS_Solution.sql`);
    if (fs.existsSync(sqlFile)) {
      const code = fs.readFileSync(sqlFile, 'utf-8');
      const outPath = path.join(slipFolder, `Slip_${slipNum}_DBMS_Solution.png`);
      await generateImage(code, 'sql', outPath, `Slip ${slipNum} - DBMS (SQL)`);
    }
    
    console.log(`  ✓ Slip ${slipNum} complete\n`);
  }
  
  console.log('\n✅ All code images generated!');
  console.log(`📁 Output directory: ${outputDir}`);
}

// Run
processAllSlips().catch(err => {
  console.error('Error:', err);
  process.exit(1);
});
