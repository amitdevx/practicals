// Test single code image generation
'use strict';

const sharp = require('sharp');
const fs = require('fs');

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
};

const testCode = `#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

Node* createNode(int data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int main() {
    Node *root = createNode(10);
    printf("Node created: %d\\n", root->data);
    return 0;
}`;

function xmlEscape(str) {
  return String(str)
    .replace(/&/g, '&amp;')
    .replace(/</g, '&lt;')
    .replace(/>/g, '&gt;')
    .replace(/"/g, '&quot;')
    .replace(/'/g, '&apos;');
}

function generateSimpleSVG(code, title) {
  const lines = code.split('\n');
  const lineHeight = 20;
  const padding = 60;
  const titleBarHeight = 45;
  const width = 1200;
  const height = titleBarHeight + padding + (lines.length * lineHeight) + padding;
  
  let codeLines = '';
  lines.forEach((line, idx) => {
    const lineNum = (idx + 1).toString().padStart(3, ' ');
    const y = titleBarHeight + padding + (idx * lineHeight);
    const escapedLine = xmlEscape(line);
    
    codeLines += `  <text x="30" y="${y}" font-family="Consolas,Monaco,Courier,monospace" font-size="14" fill="${THEME.lineNum}">${lineNum}</text>\n`;
    codeLines += `  <text x="90" y="${y}" font-family="Consolas,Monaco,Courier,monospace" font-size="14" fill="${THEME.fg}">${escapedLine}</text>\n`;
  });
  
  const svg = `<svg xmlns="http://www.w3.org/2000/svg" width="${width}" height="${height}">
  <rect width="${width}" height="${height}" fill="${THEME.bg}" rx="8"/>
  <rect width="${width}" height="${titleBarHeight}" fill="#252526" rx="8"/>
  <rect y="${titleBarHeight}" width="${width}" height="${height - titleBarHeight}" fill="${THEME.bg}"/>
  <text x="20" y="28" font-family="Segoe UI,Arial,sans-serif" font-size="14" fill="${THEME.fg}" font-weight="600">${xmlEscape(title)}</text>
  <circle cx="${width-60}" cy="22" r="6" fill="#ED594A"/>
  <circle cx="${width-40}" cy="22" r="6" fill="#FDD800"/>
  <circle cx="${width-20}" cy="22" r="6" fill="#5AC05A"/>
${codeLines}
</svg>`;
  
  return svg;
}

async function test() {
  const svg = generateSimpleSVG(testCode, 'Test - Binary Tree Node (C)');
  const buffer = Buffer.from(svg, 'utf-8');
  
  await sharp(buffer)
    .png()
    .toFile('/tmp/test_code.png');
  
  console.log('✓ Test image generated: /tmp/test_code.png');
  console.log(`  Size: ${Math.round(buffer.length / 1024)}KB SVG`);
}

test().catch(console.error);
