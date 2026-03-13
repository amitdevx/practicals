// diagram_gen.js – Generates 25 professional PNG diagrams for DS notes
'use strict';
const sharp = require('sharp');
const fs    = require('fs');
const OUT   = '/tmp/ds_diagrams';
if (!fs.existsSync(OUT)) fs.mkdirSync(OUT, { recursive: true });

// ── SVG helpers ────────────────────────────────────────────────────────────
const BLUE   = '#2563EB';
const LBLUE  = '#DBEAFE';
const WHITE  = '#FFFFFF';
const BLACK  = '#1E293B';
const RED    = '#DC2626';
const GREEN  = '#16A34A';
const ORANGE = '#EA580C';
const PURPLE = '#7C3AED';
const GRAY   = '#94A3B8';
const DARK   = '#0F172A';

// Drop-shadow filter (compatible with librsvg)
const DEFS = `<defs>
  <filter id="ds" x="-25%" y="-25%" width="160%" height="160%">
    <feGaussianBlur in="SourceAlpha" stdDeviation="3" result="blur"/>
    <feOffset dx="2" dy="3" in="blur" result="shadow"/>
    <feFlood flood-color="#00000033" result="col"/>
    <feComposite in="col" in2="shadow" operator="in" result="cshadow"/>
    <feMerge><feMergeNode in="cshadow"/><feMergeNode in="SourceGraphic"/></feMerge>
  </filter>
  <marker id="arr" markerWidth="10" markerHeight="7" refX="9" refY="3.5" orient="auto">
    <polygon points="0 0, 10 3.5, 0 7" fill="${BLACK}"/>
  </marker>
  <marker id="arr-grn" markerWidth="10" markerHeight="7" refX="9" refY="3.5" orient="auto">
    <polygon points="0 0, 10 3.5, 0 7" fill="${GREEN}"/>
  </marker>
  <marker id="arr-red" markerWidth="10" markerHeight="7" refX="9" refY="3.5" orient="auto">
    <polygon points="0 0, 10 3.5, 0 7" fill="${RED}"/>
  </marker>
</defs>`;

function svg(w, h, body) {
  return `<svg xmlns="http://www.w3.org/2000/svg" width="${w}" height="${h}" viewBox="0 0 ${w} ${h}">
  <rect width="${w}" height="${h}" fill="#F8FAFC" rx="8"/>
  ${DEFS}
  ${body}
</svg>`;
}

function xmlEsc(s) {
  return String(s).replace(/&/g,'&amp;').replace(/</g,'&lt;').replace(/>/g,'&gt;');
}

function title(text, x, y, color = DARK) {
  return `<text x="${x}" y="${y}" text-anchor="middle" font-family="Georgia,serif" font-size="15" font-weight="bold" fill="${color}">${xmlEsc(text)}</text>`;
}

function circle(x, y, r, fill, stroke, label, textFill = WHITE, fs = 13, bold = true) {
  const fw = bold ? 'bold' : 'normal';
  return `<circle cx="${x}" cy="${y}" r="${r}" fill="${fill}" stroke="${stroke}" stroke-width="2" filter="url(#ds)"/>
<text x="${x}" y="${y+5}" text-anchor="middle" font-family="Arial,sans-serif" font-size="${fs}" font-weight="${fw}" fill="${textFill}">${xmlEsc(label)}</text>`;
}

function line(x1, y1, x2, y2, color = GRAY, sw = 2) {
  return `<line x1="${x1}" y1="${y1}" x2="${x2}" y2="${y2}" stroke="${color}" stroke-width="${sw}"/>`;
}

function arrow(x1, y1, x2, y2, color = BLACK, marker = 'arr') {
  const dx = x2 - x1, dy = y2 - y1;
  const len = Math.sqrt(dx*dx + dy*dy);
  const ux = dx/len, uy = dy/len;
  const ex = x2 - ux*14, ey = y2 - uy*14;
  return `<line x1="${x1}" y1="${y1}" x2="${ex}" y2="${ey}" stroke="${color}" stroke-width="2" marker-end="url(#${marker})"/>`;
}

function roundRect(x, y, w, h, fill, stroke, rx = 8) {
  return `<rect x="${x}" y="${y}" width="${w}" height="${h}" rx="${rx}" fill="${fill}" stroke="${stroke}" stroke-width="2" filter="url(#ds)"/>`;
}

function text(x, y, txt, color = DARK, fs = 12, anchor = 'middle', bold = false) {
  const fw = bold ? 'bold' : 'normal';
  return `<text x="${x}" y="${y}" text-anchor="${anchor}" font-family="Arial,sans-serif" font-size="${fs}" font-weight="${fw}" fill="${color}">${xmlEsc(txt)}</text>`;
}

// ── Tree layout helper ─────────────────────────────────────────────────────
// nodes: [{id, label, parent, color, textColor}]
// Returns: positions {id: {x, y}}
function layoutTree(nodes, levelH = 70, unitW = 50) {
  const childrenOf = {};
  const root = [];
  nodes.forEach(n => {
    if (!childrenOf[n.id]) childrenOf[n.id] = [];
    if (n.parent === null || n.parent === undefined) { root.push(n.id); }
    else {
      if (!childrenOf[n.parent]) childrenOf[n.parent] = [];
      childrenOf[n.parent].push(n.id);
    }
  });
  const pos = {};
  let counter = 0;
  function assign(id, depth) {
    const ch = childrenOf[id] || [];
    ch.forEach(c => assign(c, depth + 1));
    if (ch.length === 0) { pos[id] = { x: counter * unitW, y: depth * levelH }; counter++; }
    else {
      const xs = ch.map(c => pos[c].x);
      pos[id] = { x: (Math.min(...xs) + Math.max(...xs)) / 2, y: depth * levelH };
    }
  }
  root.forEach(r => assign(r, 0));
  // Normalise
  const minX = Math.min(...Object.values(pos).map(p => p.x));
  Object.values(pos).forEach(p => p.x -= minX);
  return pos;
}

function drawTree(nodes, pos, R = 22, ox = 0, oy = 0, edgeColor = GRAY, edgeSW = 2) {
  let out = '';
  // edges first
  nodes.forEach(n => {
    if (n.parent !== null && n.parent !== undefined) {
      const p = pos[n.parent], c = pos[n.id];
      out += line(p.x + ox, p.y + oy, c.x + ox, c.y + oy, edgeColor, edgeSW);
    }
  });
  // nodes
  nodes.forEach(n => {
    const p = pos[n.id];
    out += circle(p.x + ox, p.y + oy, R, n.color || BLUE, n.stroke || '#1D4ED8', n.label, n.textColor || WHITE, n.fs || 12);
  });
  return out;
}

// ── Save helper ────────────────────────────────────────────────────────────
const DIMS = {};   // tracks { name: {w,h} } of output PNGs

async function save(filename, svgStr) {
  const out = `${OUT}/${filename}`;
  // density:216 = 3× base 72dpi → triples pixel dimensions for crisp output
  await sharp(Buffer.from(svgStr), { density: 216 }).png({ quality: 100 }).toFile(out);
  const meta = await sharp(out).metadata();
  const key = filename.replace('.png', '');
  DIMS[key] = { w: meta.width, h: meta.height };
  console.log(`✓ ${filename}  (${meta.width}×${meta.height})`);
}

// ── VS Code Dark Theme Code Image Renderer ──────────────────────────────────
function codeImg(lines) {
  const BG='#1E1E1E', LN_BG='#252526', LN_FG='#858585';
  const DEF='#D4D4D4', KW='#569CD6', TY='#4EC9B0', FN='#DCDCAA';
  const STR='#CE9178', CMT='#6A9955', NUM='#B5CEA8';
  const FONT_SZ=13, LH=21, LNW=42, PL=56, PT=12, CHAR_W=7.8;

  const KEYWORDS=new Set(['void','int','bool','char','float','double','return',
    'if','else','for','while','do','struct','typedef','NULL','true','false',
    'break','continue','static','const','unsigned','long','short','auto',
    'switch','case','default','sizeof','extern','register','volatile','printf',
    'scanf','malloc','free','min','max','INF','INT_MAX']);
  const TYPES=new Set(['Node','Queue','Stack','Graph','Edge','BPlusTree',
    'BPlusNode','Tree','AVLNode','RBNode','TreeNode','MinHeap','MaxHeap']);

  function tok(line) {
    const res=[];
    if(!line||line.trim()===''){res.push({t:line||'',c:DEF});return res;}
    const tr=line.trimStart();
    if(tr.startsWith('//')){res.push({t:line,c:CMT});return res;}
    let i=0;
    while(i<line.length){
      if(line[i]==='/'&&line[i+1]==='/'){res.push({t:line.slice(i),c:CMT});break;}
      if(line[i]==='"'){
        let j=i+1;
        while(j<line.length&&line[j]!=='"'){if(line[j]==='\\')j++;j++;}
        j++;res.push({t:line.slice(i,j),c:STR});i=j;continue;
      }
      if(line[i]==="'"){
        let j=i+1;
        while(j<line.length&&line[j]!=="'"){if(line[j]==='\\')j++;j++;}
        j++;res.push({t:line.slice(i,j),c:STR});i=j;continue;
      }
      if(/\d/.test(line[i])&&(i===0||!/\w/.test(line[i-1]))){
        let j=i;while(j<line.length&&/[\d.]/.test(line[j]))j++;
        res.push({t:line.slice(i,j),c:NUM});i=j;continue;
      }
      if(/[a-zA-Z_]/.test(line[i])){
        let j=i;while(j<line.length&&/\w/.test(line[j]))j++;
        const w=line.slice(i,j);
        let c=DEF;
        if(KEYWORDS.has(w))c=KW;
        else if(TYPES.has(w))c=TY;
        else if(line[j]==='(')c=FN;
        res.push({t:w,c});i=j;continue;
      }
      res.push({t:line[i],c:DEF});i++;
    }
    return res;
  }

  const maxLen=Math.max(20,...lines.map(l=>l.length));
  const W=Math.max(480,Math.round(PL+maxLen*CHAR_W+20));
  const H=PT*2+lines.length*LH+8;
  let body='';
  body+=`<rect width="${W}" height="${H}" fill="${BG}"/>`;
  body+=`<rect width="${LNW}" height="${H}" fill="${LN_BG}"/>`;
  lines.forEach((line,i)=>{
    const y=PT+(i+1)*LH;
    body+=`<text x="${LNW-6}" y="${y}" font-family="Consolas,'Courier New',monospace" font-size="${FONT_SZ}" fill="${LN_FG}" text-anchor="end" dominant-baseline="alphabetic">${i+1}</text>`;
    const tokens=tok(line);
    let x=PL;
    tokens.forEach(({t,c})=>{
      if(!t)return;
      body+=`<text x="${x}" y="${y}" font-family="Consolas,'Courier New',monospace" font-size="${FONT_SZ}" fill="${c}" dominant-baseline="alphabetic" xml:space="preserve">${xmlEsc(t)}</text>`;
      x+=t.length*CHAR_W;
    });
  });
  return `<svg xmlns="http://www.w3.org/2000/svg" width="${W}" height="${H}" viewBox="0 0 ${W} ${H}">${body}</svg>`;
}

// ══════════════════════════════════════════════════════════════════════════
// 1. ch1_terminology.png – Binary tree A(root), B,C, D,E,F,G, H,I
// ══════════════════════════════════════════════════════════════════════════
async function gen_ch1_terminology() {
  const nodes = [
    {id:'A', label:'A', parent:null},
    {id:'B', label:'B', parent:'A'},
    {id:'C', label:'C', parent:'A'},
    {id:'D', label:'D', parent:'B'},
    {id:'E', label:'E', parent:'B'},
    {id:'F', label:'F', parent:'C'},
    {id:'G', label:'G', parent:'C'},
    {id:'H', label:'H', parent:'D'},
    {id:'I', label:'I', parent:'E'},
  ];
  const pos = layoutTree(nodes, 72, 58);
  const allX = Object.values(pos).map(p=>p.x);
  const W = Math.max(...allX) + 80, H = 400;
  const ox = 40, oy = 60;
  let body = title('Binary Tree – Terminology', W/2, 28, DARK);
  // Annotation labels
  body += drawTree(nodes, pos, 22, ox, oy);
  // Annotations
  const ap = pos['A'];
  body += text(ap.x+ox+28, ap.y+oy+4, '← Root', DARK, 11, 'start');
  const hp = pos['H'], ip = pos['I'];
  body += text(hp.x+ox, hp.y+oy+36, 'Leaf', GREEN, 11, 'middle', true);
  body += text(ip.x+ox, ip.y+oy+36, 'Leaf', GREEN, 11, 'middle', true);
  body += text(ox-10, oy+4, 'L0', PURPLE, 11, 'start');
  body += text(ox-10, oy+72+4, 'L1', PURPLE, 11, 'start');
  body += text(ox-10, oy+144+4, 'L2', PURPLE, 11, 'start');
  body += text(ox-10, oy+216+4, 'L3', PURPLE, 11, 'start');
  await save('ch1_terminology.png', svg(W+40, H, body));
}

// ══════════════════════════════════════════════════════════════════════════
// 2. ch1_bst.png – BST root=50
// ══════════════════════════════════════════════════════════════════════════
async function gen_ch1_bst() {
  const nodes = [
    {id:50, label:'50', parent:null},
    {id:30, label:'30', parent:50},
    {id:70, label:'70', parent:50},
    {id:20, label:'20', parent:30},
    {id:40, label:'40', parent:30},
    {id:60, label:'60', parent:70},
    {id:80, label:'80', parent:70},
  ];
  const pos = layoutTree(nodes, 75, 65);
  const allX = Object.values(pos).map(p=>p.x);
  const W = Math.max(...allX)+80, H = 330;
  const ox=40, oy=55;
  let body = title('Binary Search Tree (BST)', W/2, 26, DARK);
  body += drawTree(nodes, pos, 22, ox, oy);
  // BST property labels
  body += text(10, H-20, 'Left subtree < Parent < Right subtree', BLUE, 11, 'start', true);
  await save('ch1_bst.png', svg(W+40, H, body));
}

// ══════════════════════════════════════════════════════════════════════════
// 3. ch1_bst_insert.png – BST after inserting 50,30,70,20,40,60,80,10,90
// ══════════════════════════════════════════════════════════════════════════
async function gen_ch1_bst_insert() {
  const nodes = [
    {id:50, label:'50', parent:null},
    {id:30, label:'30', parent:50},
    {id:70, label:'70', parent:50},
    {id:20, label:'20', parent:30},
    {id:40, label:'40', parent:30},
    {id:60, label:'60', parent:70},
    {id:80, label:'80', parent:70},
    {id:10, label:'10', parent:20},
    {id:90, label:'90', parent:80},
  ];
  const pos = layoutTree(nodes, 72, 60);
  const allX = Object.values(pos).map(p=>p.x);
  const W = Math.max(...allX)+80, H = 380;
  const ox=40, oy=55;
  let body = title('BST after insertions: 50,30,70,20,40,60,80,10,90', W/2, 26, DARK);
  body += drawTree(nodes, pos, 22, ox, oy);
  await save('ch1_bst_insert.png', svg(W+40, H, body));
}

// ══════════════════════════════════════════════════════════════════════════
// 4. ch1_traversal.png – Tree 1(root), 2(left,4,5), 3(right,6,7)
// ══════════════════════════════════════════════════════════════════════════
async function gen_ch1_traversal() {
  const nodes = [
    {id:1, label:'1', parent:null},
    {id:2, label:'2', parent:1},
    {id:3, label:'3', parent:1},
    {id:4, label:'4', parent:2},
    {id:5, label:'5', parent:2},
    {id:6, label:'6', parent:3},
    {id:7, label:'7', parent:3},
  ];
  const pos = layoutTree(nodes, 75, 65);
  const allX = Object.values(pos).map(p=>p.x);
  const W = Math.max(...allX)+80, H = 340;
  const ox=40, oy=55;
  let body = title('Tree Traversals', W/2, 22, DARK);
  body += drawTree(nodes, pos, 22, ox, oy);
  body += text(W/2, H-75, 'Inorder (LNR):    4  2  5  1  6  3  7', DARK, 11, 'middle');
  body += text(W/2, H-55, 'Preorder (NLR):   1  2  4  5  3  6  7', DARK, 11, 'middle');
  body += text(W/2, H-35, 'Postorder (LRN):  4  5  2  6  7  3  1', DARK, 11, 'middle');
  await save('ch1_traversal.png', svg(W+40, H, body));
}

// ══════════════════════════════════════════════════════════════════════════
// 5. ch1_max_heap.png
// ══════════════════════════════════════════════════════════════════════════
async function gen_ch1_max_heap() {
  const nodes = [
    {id:90, label:'90', parent:null},
    {id:80, label:'80', parent:90},
    {id:75, label:'75', parent:90},
    {id:70, label:'70', parent:80},
    {id:60, label:'60', parent:80},
    {id:50, label:'50', parent:75},
    {id:45, label:'45', parent:75},
    {id:10, label:'10', parent:70},
    {id:30, label:'30', parent:70},
  ];
  const pos = layoutTree(nodes, 72, 60);
  const allX = Object.values(pos).map(p=>p.x);
  const W = Math.max(...allX)+80, H = 380;
  const ox=40, oy=60;
  // Color root differently
  nodes[0].color='#B45309'; nodes[0].stroke='#92400E';
  let body = title('Max-Heap (parent ≥ children)', W/2, 26, DARK);
  body += drawTree(nodes, pos, 22, ox, oy);
  body += text(W/2, H-15, '90 is always at root (maximum element)', '#B45309', 11, 'middle', true);
  await save('ch1_max_heap.png', svg(W+40, H, body));
}

// ══════════════════════════════════════════════════════════════════════════
// 6. ch1_min_heap.png
// ══════════════════════════════════════════════════════════════════════════
async function gen_ch1_min_heap() {
  const nodes = [
    {id:10, label:'10', parent:null},
    {id:30, label:'30', parent:10},
    {id:20, label:'20', parent:10},
    {id:50, label:'50', parent:30},
    {id:40, label:'40', parent:30},
    {id:35, label:'35', parent:20},
    {id:45, label:'45', parent:20},
    {id:60, label:'60', parent:50},
    {id:70, label:'70', parent:50},
  ];
  const pos = layoutTree(nodes, 72, 60);
  const allX = Object.values(pos).map(p=>p.x);
  const W = Math.max(...allX)+80, H = 380;
  const ox=40, oy=60;
  nodes[0].color=GREEN; nodes[0].stroke='#15803D';
  let body = title('Min-Heap (parent ≤ children)', W/2, 26, DARK);
  body += drawTree(nodes, pos, 22, ox, oy);
  body += text(W/2, H-15, '10 is always at root (minimum element)', GREEN, 11, 'middle', true);
  await save('ch1_min_heap.png', svg(W+40, H, body));
}

// ══════════════════════════════════════════════════════════════════════════
// 7. ch1_complete_bt.png – Complete binary tree 10 nodes
// ══════════════════════════════════════════════════════════════════════════
async function gen_ch1_complete_bt() {
  const nodes = [
    {id:1,label:'1',parent:null},
    {id:2,label:'2',parent:1},
    {id:3,label:'3',parent:1},
    {id:4,label:'4',parent:2},
    {id:5,label:'5',parent:2},
    {id:6,label:'6',parent:3},
    {id:7,label:'7',parent:3},
    {id:8,label:'8',parent:4},
    {id:9,label:'9',parent:4},
    {id:10,label:'10',parent:5},
  ];
  const pos = layoutTree(nodes, 72, 60);
  const allX = Object.values(pos).map(p=>p.x);
  const W = Math.max(...allX)+80, H = 380;
  const ox=40, oy=60;
  let body = title('Complete Binary Tree (10 nodes)', W/2, 26, DARK);
  body += drawTree(nodes, pos, 22, ox, oy);
  body += text(W/2, H-15, 'Last level filled left-to-right', BLUE, 11, 'middle', true);
  await save('ch1_complete_bt.png', svg(W+40, H, body));
}

// ══════════════════════════════════════════════════════════════════════════
// Rotation diagrams helpers
// ══════════════════════════════════════════════════════════════════════════
function drawSmallTree(nodes2, ox, oy, R=20) {
  // nodes2: [{lbl, px, py, parent_px, parent_py, color, bf}]
  // positions are relative to ox, oy
  let out = '';
  // edges first
  nodes2.forEach(n => {
    if (n.ppx !== undefined) {
      out += line(n.ppx+ox, n.ppy+oy, n.px+ox, n.py+oy, GRAY, 2);
    }
  });
  // nodes
  nodes2.forEach(n => {
    const fill = n.color || BLUE;
    const stroke = n.stroke || '#1D4ED8';
    out += circle(n.px+ox, n.py+oy, R, fill, stroke, n.lbl, n.textFill||WHITE, 12);
    if (n.bf !== undefined) {
      out += text(n.px+ox+R+4, n.py+oy-R+4, 'bf='+n.bf, RED, 10, 'start');
    }
  });
  return out;
}

// ══════════════════════════════════════════════════════════════════════════
// 8. ch2_avl_ll.png – LL Rotation
// ══════════════════════════════════════════════════════════════════════════
async function gen_ch2_avl_ll() {
  const W=780, H=280;
  let body = title('AVL LL Rotation (Right Rotation)', W/2, 22, DARK);
  // Before: 30 BF=+2, left=20 BF=+1, left=10 BF=0
  const before = [
    {lbl:'30', px:0, py:0, bf:'+2'},
    {lbl:'20', px:-50, py:70, ppx:0, ppy:0, bf:'+1'},
    {lbl:'10', px:-100, py:140, ppx:-50, ppy:70, bf:'0'},
  ];
  body += text(160, 50, 'BEFORE (Imbalanced)', RED, 13, 'middle', true);
  body += drawSmallTree(before, 200, 80);
  // Arrow
  body += text(390, 145, '⟹', DARK, 30, 'middle');
  // After: 20 root, left=10, right=30
  const after = [
    {lbl:'20', px:0, py:0, bf:'0'},
    {lbl:'10', px:-50, py:70, ppx:0, ppy:0, bf:'0'},
    {lbl:'30', px:50, py:70, ppx:0, ppy:0, bf:'0'},
  ];
  body += text(590, 50, 'AFTER (Balanced)', GREEN, 13, 'middle', true);
  body += drawSmallTree(after, 580, 80);
  body += text(W/2, H-18, 'B becomes root  |  C becomes right child of B  |  B\'s right subtree → C\'s left', DARK, 10, 'middle');
  await save('ch2_avl_ll.png', svg(W, H, body));
}

// ══════════════════════════════════════════════════════════════════════════
// 9. ch2_avl_rr.png – RR Rotation
// ══════════════════════════════════════════════════════════════════════════
async function gen_ch2_avl_rr() {
  const W=780, H=280;
  let body = title('AVL RR Rotation (Left Rotation)', W/2, 22, DARK);
  const before = [
    {lbl:'10', px:0, py:0, bf:'-2'},
    {lbl:'20', px:50, py:70, ppx:0, ppy:0, bf:'-1'},
    {lbl:'30', px:100, py:140, ppx:50, ppy:70, bf:'0'},
  ];
  body += text(160, 50, 'BEFORE (Imbalanced)', RED, 13, 'middle', true);
  body += drawSmallTree(before, 130, 80);
  body += text(390, 145, '⟹', DARK, 30, 'middle');
  const after = [
    {lbl:'20', px:0, py:0, bf:'0'},
    {lbl:'10', px:-50, py:70, ppx:0, ppy:0, bf:'0'},
    {lbl:'30', px:50, py:70, ppx:0, ppy:0, bf:'0'},
  ];
  body += text(590, 50, 'AFTER (Balanced)', GREEN, 13, 'middle', true);
  body += drawSmallTree(after, 580, 80);
  body += text(W/2, H-18, 'B becomes root  |  A becomes left child of B  |  B\'s left subtree → A\'s right', DARK, 10, 'middle');
  await save('ch2_avl_rr.png', svg(W, H, body));
}

// ══════════════════════════════════════════════════════════════════════════
// 10. ch2_avl_lr.png – LR Rotation
// ══════════════════════════════════════════════════════════════════════════
async function gen_ch2_avl_lr() {
  const W=860, H=300;
  let body = title('AVL LR Rotation (Left-Right, Two Steps)', W/2, 22, DARK);
  // Step 1: Before
  const t1 = [
    {lbl:'30', px:0, py:0, bf:'+2'},
    {lbl:'10', px:-50, py:70, ppx:0, ppy:0, bf:'-1'},
    {lbl:'20', px:0, py:140, ppx:-50, ppy:70, bf:'0'},
  ];
  body += text(120, 50, 'BEFORE', RED, 12, 'middle', true);
  body += drawSmallTree(t1, 130, 75);
  body += text(290, 145, '→', DARK, 24, 'middle');
  // Step 2: After left rotate 10
  const t2 = [
    {lbl:'30', px:0, py:0, bf:'+2'},
    {lbl:'20', px:-50, py:70, ppx:0, ppy:0, bf:'+1'},
    {lbl:'10', px:-100, py:140, ppx:-50, ppy:70, bf:'0'},
  ];
  body += text(430, 50, 'Step 1: Left rotate 10', ORANGE, 11, 'middle', true);
  body += drawSmallTree(t2, 460, 75);
  body += text(600, 145, '→', DARK, 24, 'middle');
  // Step 3: After right rotate 30
  const t3 = [
    {lbl:'20', px:0, py:0, bf:'0'},
    {lbl:'10', px:-50, py:70, ppx:0, ppy:0, bf:'0'},
    {lbl:'30', px:50, py:70, ppx:0, ppy:0, bf:'0'},
  ];
  body += text(730, 50, 'Step 2: Right rotate 30', GREEN, 11, 'middle', true);
  body += drawSmallTree(t3, 730, 75);
  body += text(W/2, H-18, 'LR Case: BF(node)=+2 and BF(left child)=-1  →  Left rotate left child, then Right rotate node', DARK, 10, 'middle');
  await save('ch2_avl_lr.png', svg(W, H, body));
}

// ══════════════════════════════════════════════════════════════════════════
// 11. ch2_avl_rl.png – RL Rotation
// ══════════════════════════════════════════════════════════════════════════
async function gen_ch2_avl_rl() {
  const W=860, H=300;
  let body = title('AVL RL Rotation (Right-Left, Two Steps)', W/2, 22, DARK);
  const t1 = [
    {lbl:'10', px:0, py:0, bf:'-2'},
    {lbl:'30', px:50, py:70, ppx:0, ppy:0, bf:'+1'},
    {lbl:'20', px:0, py:140, ppx:50, ppy:70, bf:'0'},
  ];
  body += text(120, 50, 'BEFORE', RED, 12, 'middle', true);
  body += drawSmallTree(t1, 100, 75);
  body += text(290, 145, '→', DARK, 24, 'middle');
  const t2 = [
    {lbl:'10', px:0, py:0, bf:'-2'},
    {lbl:'20', px:50, py:70, ppx:0, ppy:0, bf:'-1'},
    {lbl:'30', px:100, py:140, ppx:50, ppy:70, bf:'0'},
  ];
  body += text(430, 50, 'Step 1: Right rotate 30', ORANGE, 11, 'middle', true);
  body += drawSmallTree(t2, 400, 75);
  body += text(600, 145, '→', DARK, 24, 'middle');
  const t3 = [
    {lbl:'20', px:0, py:0, bf:'0'},
    {lbl:'10', px:-50, py:70, ppx:0, ppy:0, bf:'0'},
    {lbl:'30', px:50, py:70, ppx:0, ppy:0, bf:'0'},
  ];
  body += text(730, 50, 'Step 2: Left rotate 10', GREEN, 11, 'middle', true);
  body += drawSmallTree(t3, 730, 75);
  body += text(W/2, H-18, 'RL Case: BF(node)=-2 and BF(right child)=+1  →  Right rotate right child, then Left rotate node', DARK, 10, 'middle');
  await save('ch2_avl_rl.png', svg(W, H, body));
}

// ══════════════════════════════════════════════════════════════════════════
// 12. ch2_avl_final.png – AVL after 30,20,10,40,35
// ══════════════════════════════════════════════════════════════════════════
async function gen_ch2_avl_final() {
  const nodes = [
    {id:30, label:'30', parent:null},
    {id:20, label:'20', parent:30},
    {id:35, label:'35', parent:30},
    {id:10, label:'10', parent:20},
    {id:40, label:'40', parent:35},
  ];
  const pos = layoutTree(nodes, 75, 70);
  const allX = Object.values(pos).map(p=>p.x);
  const W = Math.max(...allX)+120, H = 310;
  const ox=60, oy=60;
  let body = title('AVL Tree after inserting: 30, 20, 10, 40, 35', W/2, 24, DARK);
  body += drawTree(nodes, pos, 22, ox, oy);
  // BF labels
  const bfs = {30:'0', 20:'-1', 35:'-1', 10:'0', 40:'0'};
  nodes.forEach(n=>{
    const p=pos[n.id];
    body += text(p.x+ox+25, p.y+oy-14, 'bf='+bfs[n.id], RED, 10, 'start');
  });
  body += text(W/2, H-18, 'All nodes balanced: |BF| ≤ 1', GREEN, 11, 'middle', true);
  await save('ch2_avl_final.png', svg(W+40, H, body));
}

// ══════════════════════════════════════════════════════════════════════════
// 13. ch2_rbt.png – Red-Black Tree
// ══════════════════════════════════════════════════════════════════════════
async function gen_ch2_rbt() {
  // 20(B), left=10(B), right=30(B, left=25(R), right=40(R))
  const B = BLACK, R_= RED;
  const nodes = [
    {id:20, label:'20', parent:null,  color:'#1E293B', stroke:'#0F172A', textColor:WHITE},
    {id:10, label:'10', parent:20,   color:'#1E293B', stroke:'#0F172A', textColor:WHITE},
    {id:30, label:'30', parent:20,   color:'#1E293B', stroke:'#0F172A', textColor:WHITE},
    {id:25, label:'25', parent:30,   color:RED,       stroke:'#991B1B', textColor:WHITE},
    {id:40, label:'40', parent:30,   color:RED,       stroke:'#991B1B', textColor:WHITE},
  ];
  const pos = layoutTree(nodes, 75, 70);
  const allX = Object.values(pos).map(p=>p.x);
  const W = Math.max(...allX)+120, H = 310;
  const ox=60, oy=60;
  let body = title('Red-Black Tree Example', W/2, 24, DARK);
  body += drawTree(nodes, pos, 22, ox, oy);
  // Legend
  body += roundRect(20, H-55, 100, 22, '#1E293B', '#0F172A', 4);
  body += text(70, H-39, 'BLACK node', WHITE, 10, 'middle');
  body += roundRect(140, H-55, 100, 22, RED, '#991B1B', 4);
  body += text(190, H-39, 'RED node', WHITE, 10, 'middle');
  body += text(W/2, H-15, 'Properties: Root=Black, No two consecutive Reds, Equal Black-Height', DARK, 10, 'middle');
  await save('ch2_rbt.png', svg(W+40, H, body));
}

// ══════════════════════════════════════════════════════════════════════════
// 14. ch2_btree.png – B-Tree order 3
// ══════════════════════════════════════════════════════════════════════════
async function gen_ch2_btree() {
  const W=460, H=240;
  let body = title('B-Tree of Order 3  (2-3 Tree)', W/2, 22, DARK);
  // Internal node [10|20]
  const iw=100, ih=36, ix=(W-iw)/2, iy=55;
  body += roundRect(ix, iy, iw, ih, LBLUE, BLUE);
  body += text(ix+iw/2-15, iy+ih/2+5, '10', BLUE, 14, 'middle', true);
  body += `<line x1="${ix+iw/2}" y1="${iy}" x2="${ix+iw/2}" y2="${iy+ih}" stroke="${BLUE}" stroke-width="1.5"/>`;
  body += text(ix+iw/2+15, iy+ih/2+5, '20', BLUE, 14, 'middle', true);
  // Leaves
  const ly = 155;
  // [5]
  const l1x=50, l1w=60;
  body += roundRect(l1x, ly, l1w, ih, '#F0FDF4', GREEN);
  body += text(l1x+l1w/2, ly+ih/2+5, '5', GREEN, 14, 'middle', true);
  // [15]
  const l2x=W/2-30, l2w=60;
  body += roundRect(l2x, ly, l2w, ih, '#F0FDF4', GREEN);
  body += text(l2x+l2w/2, ly+ih/2+5, '15', GREEN, 14, 'middle', true);
  // [25|30]
  const l3x=W-130, l3w=100;
  body += roundRect(l3x, ly, l3w, ih, '#F0FDF4', GREEN);
  body += text(l3x+l3w/2-15, ly+ih/2+5, '25', GREEN, 14, 'middle', true);
  body += `<line x1="${l3x+l3w/2}" y1="${ly}" x2="${l3x+l3w/2}" y2="${ly+ih}" stroke="${GREEN}" stroke-width="1.5"/>`;
  body += text(l3x+l3w/2+15, ly+ih/2+5, '30', GREEN, 14, 'middle', true);
  // Edges
  body += line(ix+20, iy+ih, l1x+l1w/2, ly, GRAY, 2);
  body += line(ix+iw/2, iy+ih, l2x+l2w/2, ly, GRAY, 2);
  body += line(ix+iw-20, iy+ih, l3x+l3w/2, ly, GRAY, 2);
  body += text(W/2, H-15, 'Internal=[10|20]  Leaves=[5],[15],[25|30]  All leaves at same level', DARK, 10, 'middle');
  await save('ch2_btree.png', svg(W, H, body));
}

// ══════════════════════════════════════════════════════════════════════════
// 15. ch2_bplustree.png – B+ Tree
// ══════════════════════════════════════════════════════════════════════════
async function gen_ch2_bplustree() {
  const W=520, H=270;
  let body = title('B+ Tree (leaves linked)', W/2, 22, DARK);
  // Internal node [10|20] in purple
  const iw=110, ih=36, ix=(W-iw)/2, iy=55;
  body += roundRect(ix, iy, iw, ih, '#EDE9FE', PURPLE);
  body += text(ix+iw/2-18, iy+ih/2+5, '10', PURPLE, 14, 'middle', true);
  body += `<line x1="${ix+iw/2}" y1="${iy}" x2="${ix+iw/2}" y2="${iy+ih}" stroke="${PURPLE}" stroke-width="1.5"/>`;
  body += text(ix+iw/2+18, iy+ih/2+5, '20', PURPLE, 14, 'middle', true);
  // Leaf nodes in blue
  const ly=155, lw=100, lh=36;
  const leaves = [{x:40,keys:['5','10']},{x:190,keys:['10','15']},{x:340,keys:['20','25']}];
  leaves.forEach(l=>{
    body += roundRect(l.x, ly, lw, lh, LBLUE, BLUE);
    body += text(l.x+lw/2-18, ly+lh/2+5, l.keys[0], BLUE, 13, 'middle', true);
    body += `<line x1="${l.x+lw/2}" y1="${ly}" x2="${l.x+lw/2}" y2="${ly+lh}" stroke="${BLUE}" stroke-width="1.5"/>`;
    body += text(l.x+lw/2+18, ly+lh/2+5, l.keys[1], BLUE, 13, 'middle', true);
  });
  // Edges from internal to leaves
  body += line(ix+20, iy+ih, leaves[0].x+lw/2, ly, GRAY, 2);
  body += line(ix+iw/2, iy+ih, leaves[1].x+lw/2, ly, GRAY, 2);
  body += line(ix+iw-20, iy+ih, leaves[2].x+lw/2, ly, GRAY, 2);
  // Link arrows between leaves
  body += arrow(leaves[0].x+lw, ly+lh/2, leaves[1].x-2, ly+lh/2, GREEN, 'arr-grn');
  body += arrow(leaves[1].x+lw, ly+lh/2, leaves[2].x-2, ly+lh/2, GREEN, 'arr-grn');
  body += text(W/2, H-40, 'Internal nodes: routing keys only (purple)', PURPLE, 10, 'middle');
  body += text(W/2, H-22, 'Leaf nodes: actual data, linked list → for range queries (green arrows)', GREEN, 10, 'middle');
  await save('ch2_bplustree.png', svg(W, H, body));
}

// ══════════════════════════════════════════════════════════════════════════
// Graph helpers
// ══════════════════════════════════════════════════════════════════════════
function gnode(x, y, lbl, color=BLUE, stroke='#1D4ED8', textColor=WHITE, R=22) {
  return circle(x, y, R, color, stroke, lbl, textColor, 12);
}

// ══════════════════════════════════════════════════════════════════════════
// 16. ch3_graph.png – Undirected graph 6 nodes hexagonal
// ══════════════════════════════════════════════════════════════════════════
async function gen_ch3_graph() {
  const W=440, H=360;
  // Hexagonal positions: A-F
  const cx=W/2, cy=H/2-20, r=130;
  const pts = {};
  ['A','B','C','D','E','F'].forEach((lbl,i)=>{
    const a = (i*60-90)*Math.PI/180;
    pts[lbl]={x:cx+r*Math.cos(a), y:cy+r*Math.sin(a)};
  });
  // 7 edges
  const edges = [['A','B'],['B','C'],['C','D'],['D','E'],['E','F'],['F','A'],['B','E']];
  let body = title('Graph  G(V, E)  –  Undirected', W/2, 22, DARK);
  edges.forEach(([u,v])=>{
    body += line(pts[u].x, pts[u].y, pts[v].x, pts[v].y, GRAY, 2.5);
  });
  Object.entries(pts).forEach(([lbl,p])=>{ body += gnode(p.x, p.y, lbl); });
  body += text(W/2, H-15, 'V={A,B,C,D,E,F}  |  E=7 edges  |  Undirected', DARK, 10, 'middle');
  await save('ch3_graph.png', svg(W, H, body));
}

// ══════════════════════════════════════════════════════════════════════════
// 17. ch3_directed.png – Directed graph 5 nodes
// ══════════════════════════════════════════════════════════════════════════
async function gen_ch3_directed() {
  const W=420, H=340;
  const pts = {
    1:{x:210,y:60}, 2:{x:90,y:160}, 3:{x:330,y:160}, 4:{x:90,y:280}, 5:{x:330,y:280}
  };
  const edges = [[1,2],[1,3],[2,4],[3,5],[2,3],[4,5]];
  let body = title('Directed Graph (Digraph)', W/2, 22, DARK);
  edges.forEach(([u,v])=>{ body += arrow(pts[u].x, pts[u].y, pts[v].x, pts[v].y, BLACK); });
  Object.entries(pts).forEach(([lbl,p])=>{ body += gnode(p.x, p.y, lbl); });
  body += text(W/2, H-15, 'Edges are directed (arrows)  |  In-degree and Out-degree matter', DARK, 10, 'middle');
  await save('ch3_directed.png', svg(W, H, body));
}

// ══════════════════════════════════════════════════════════════════════════
// 18. ch3_weighted.png – Weighted graph 6 nodes
// ══════════════════════════════════════════════════════════════════════════
async function gen_ch3_weighted() {
  const W=460, H=360;
  const pts = {
    A:{x:80,y:80}, B:{x:280,y:60}, C:{x:400,y:180},
    D:{x:300,y:300}, E:{x:120,y:300}, F:{x:230,y:190}
  };
  const edges = [
    ['A','B',4],['A','F',2],['B','C',5],['B','F',1],
    ['C','D',3],['D','E',6],['E','F',7],['F','C',8]
  ];
  let body = title('Weighted Graph', W/2, 22, DARK);
  edges.forEach(([u,v,w])=>{
    body += line(pts[u].x, pts[u].y, pts[v].x, pts[v].y, GRAY, 2);
    const mx=(pts[u].x+pts[v].x)/2, my=(pts[u].y+pts[v].y)/2;
    body += `<circle cx="${mx}" cy="${my}" r="11" fill="${WHITE}" stroke="${RED}" stroke-width="1.5"/>`;
    body += text(mx, my+4, String(w), RED, 11, 'middle', true);
  });
  Object.entries(pts).forEach(([lbl,p])=>{ body += gnode(p.x, p.y, lbl); });
  body += text(W/2, H-15, 'Edge weights shown in red circles', DARK, 10, 'middle');
  await save('ch3_weighted.png', svg(W, H, body));
}

// ══════════════════════════════════════════════════════════════════════════
// 19. ch3_mst.png – MST with green edges
// ══════════════════════════════════════════════════════════════════════════
async function gen_ch3_mst() {
  const W=460, H=360;
  const pts = {
    A:{x:80,y:80}, B:{x:280,y:60}, C:{x:400,y:180},
    D:{x:300,y:300}, E:{x:120,y:300}, F:{x:230,y:190}
  };
  const allEdges = [
    ['A','B',4,false],['A','F',2,true],['B','C',5,false],['B','F',1,true],
    ['C','D',3,true],['D','E',6,true],['E','F',7,false],['F','C',8,false]
  ];
  // MST edges: A-F(2), B-F(1), C-D(3), A-B(4), D-E(6) = spanning 6 nodes w/ 5 edges
  // Let's redo: MST = B-F(1), A-F(2), C-D(3), A-B(4), D-E(6)
  const mstSet = new Set(['A-F','B-F','C-D','A-B','D-E']);
  let body = title('Minimum Spanning Tree (MST)', W/2, 22, DARK);
  allEdges.forEach(([u,v,w])=>{
    const key1=`${u}-${v}`, key2=`${v}-${u}`;
    const isMST = mstSet.has(key1)||mstSet.has(key2);
    const col = isMST ? GREEN : '#CBD5E1';
    const sw  = isMST ? 3.5 : 1.5;
    body += line(pts[u].x, pts[u].y, pts[v].x, pts[v].y, col, sw);
    const mx=(pts[u].x+pts[v].x)/2, my=(pts[u].y+pts[v].y)/2;
    const bgCol = isMST ? '#F0FDF4' : WHITE;
    const txtCol = isMST ? GREEN : '#94A3B8';
    body += `<circle cx="${mx}" cy="${my}" r="11" fill="${bgCol}" stroke="${txtCol}" stroke-width="1.5"/>`;
    body += text(mx, my+4, String(w), isMST?GREEN:GRAY, 11, 'middle', true);
  });
  Object.entries(pts).forEach(([lbl,p])=>{
    body += gnode(p.x, p.y, lbl, BLUE, '#1D4ED8');
  });
  body += text(W/2, H-30, 'MST edges highlighted in GREEN (Kruskal\'s: sort by weight, no cycle)', GREEN, 10, 'middle', true);
  body += text(W/2, H-14, 'Total MST weight = 1+2+3+4+6 = 16', DARK, 10, 'middle');
  await save('ch3_mst.png', svg(W, H, body));
}

// ══════════════════════════════════════════════════════════════════════════
// 20. ch3_bfs.png – BFS tree levels
// ══════════════════════════════════════════════════════════════════════════
async function gen_ch3_bfs() {
  const nodes = [
    {id:1, label:'1', parent:null, color:GREEN, stroke:'#15803D'},
    {id:2, label:'2', parent:1},
    {id:3, label:'3', parent:1},
    {id:4, label:'4', parent:2},
    {id:5, label:'5', parent:2},
    {id:6, label:'6', parent:3},
    {id:7, label:'7', parent:3},
  ];
  const pos = layoutTree(nodes, 78, 68);
  const allX = Object.values(pos).map(p=>p.x);
  const W = Math.max(...allX)+120, H = 340;
  const ox=60, oy=65;
  let body = title('BFS Traversal: Level by Level', W/2, 24, DARK);
  body += drawTree(nodes, pos, 22, ox, oy);
  // Level labels
  body += text(22, oy+5, 'L0', PURPLE, 11, 'middle', true);
  body += text(22, oy+78+5, 'L1', PURPLE, 11, 'middle', true);
  body += text(22, oy+156+5, 'L2', PURPLE, 11, 'middle', true);
  body += text(W/2, H-30, 'Order: 1 → 2, 3 → 4, 5, 6, 7', DARK, 11, 'middle', true);
  body += text(W/2, H-14, 'Uses Queue. Time: O(V+E). Space: O(V)', DARK, 10, 'middle');
  await save('ch3_bfs.png', svg(W+40, H, body));
}

// ══════════════════════════════════════════════════════════════════════════
// 21. ch3_dfs.png – DFS path
// ══════════════════════════════════════════════════════════════════════════
async function gen_ch3_dfs() {
  const W=440, H=360;
  const pts = {1:{x:220,y:60},2:{x:100,y:160},3:{x:340,y:160},4:{x:60,y:280},5:{x:160,y:280},6:{x:300,y:280},7:{x:400,y:280}};
  // DFS order: 1→2→4→5→3→6→7 (tree edges in orange, back-edges in grey)
  const dfsEdges = [[1,2],[2,4],[2,5],[1,3],[3,6],[3,7]];
  const visited = [1,2,4,5,3,6,7];
  let body = title('DFS Traversal Path', W/2, 22, DARK);
  dfsEdges.forEach(([u,v])=>{
    body += line(pts[u].x, pts[u].y, pts[v].x, pts[v].y, ORANGE, 3);
  });
  visited.forEach((n,i)=>{
    body += gnode(pts[n].x, pts[n].y, String(n), ORANGE, '#C2410C');
    body += text(pts[n].x+27, pts[n].y-18, String(i+1), '#7C2D12', 10, 'middle', true);
  });
  body += text(W/2, H-30, 'DFS Order: 1→2→4→5→3→6→7 (orange path)', ORANGE, 11, 'middle', true);
  body += text(W/2, H-14, 'Uses Stack/Recursion. Time: O(V+E). Space: O(V)', DARK, 10, 'middle');
  await save('ch3_dfs.png', svg(W, H, body));
}

// ══════════════════════════════════════════════════════════════════════════
// 22. ch3_dijkstra.png – Dijkstra shortest path from A
// ══════════════════════════════════════════════════════════════════════════
async function gen_ch3_dijkstra() {
  const W=480, H=370;
  const pts = {
    A:{x:80,y:180}, B:{x:220,y:70}, C:{x:380,y:70},
    D:{x:380,y:290}, E:{x:220,y:290}
  };
  const edges = [
    ['A','B',4,true], ['A','E',7,false], ['B','C',3,true],
    ['B','E',2,false], ['C','D',6,true], ['D','E',5,false],['E','C',8,false]
  ];
  const dists = {A:'0',B:'4',C:'7',D:'13',E:'6'};
  let body = title("Dijkstra's SSSP from A", W/2, 22, DARK);
  edges.forEach(([u,v,w,isSP])=>{
    const col = isSP ? GREEN : GRAY;
    const sw  = isSP ? 3 : 1.5;
    body += line(pts[u].x, pts[u].y, pts[v].x, pts[v].y, col, sw);
    const mx=(pts[u].x+pts[v].x)/2, my=(pts[u].y+pts[v].y)/2;
    body += `<circle cx="${mx}" cy="${my}" r="11" fill="${WHITE}" stroke="${isSP?GREEN:RED}" stroke-width="1.5"/>`;
    body += text(mx, my+4, String(w), isSP?GREEN:RED, 11, 'middle', true);
  });
  Object.entries(pts).forEach(([lbl,p])=>{
    const isA = lbl==='A';
    body += gnode(p.x, p.y, lbl, isA?ORANGE:BLUE, isA?'#C2410C':'#1D4ED8');
    body += `<rect x="${p.x-16}" y="${p.y+26}" width="32" height="18" rx="4" fill="${WHITE}" stroke="${BLUE}" stroke-width="1"/>`;
    body += text(p.x, p.y+38, 'd='+dists[lbl], DARK, 10, 'middle', true);
  });
  body += text(W/2, H-30, 'Shortest path: A→B(4)→C(7)→D(13)  |  A→B→E(6)', DARK, 10, 'middle');
  body += text(W/2, H-14, 'Green = shortest path edges. d[v] = shortest distance from A', GREEN, 10, 'middle');
  await save('ch3_dijkstra.png', svg(W, H, body));
}

// ══════════════════════════════════════════════════════════════════════════
// Hash table helpers
// ══════════════════════════════════════════════════════════════════════════
function hashTable(slots, ox, oy, slotH=32, slotW=60, indexW=40) {
  let out = '';
  const totalH = slots.length * slotH;
  // Header
  out += roundRect(ox, oy, indexW, slotH, PURPLE, '#5B21B6');
  out += text(ox+indexW/2, oy+slotH/2+5, 'Idx', WHITE, 11, 'middle', true);
  out += roundRect(ox+indexW, oy, slotW, slotH, BLUE, '#1D4ED8');
  out += text(ox+indexW+slotW/2, oy+slotH/2+5, 'Value', WHITE, 11, 'middle', true);
  slots.forEach((s, i) => {
    const y = oy + (i+1)*slotH;
    const idxFill = '#EDE9FE';
    const valFill = s.value ? LBLUE : '#F1F5F9';
    out += roundRect(ox, y, indexW, slotH, idxFill, '#A78BFA', 0);
    out += text(ox+indexW/2, y+slotH/2+5, String(s.idx), PURPLE, 11, 'middle', true);
    out += roundRect(ox+indexW, y, slotW, slotH, valFill, s.value?BLUE:GRAY, 0);
    if (s.value) out += text(ox+indexW+slotW/2, y+slotH/2+5, String(s.value), BLUE, 11, 'middle', true);
    else out += text(ox+indexW+slotW/2, y+slotH/2+5, '—', GRAY, 11, 'middle');
    if (s.note) out += text(ox+indexW+slotW+8, y+slotH/2+5, s.note, ORANGE, 10, 'start');
  });
  return out;
}

// ══════════════════════════════════════════════════════════════════════════
// 23. ch4_linear_probe.png
// ══════════════════════════════════════════════════════════════════════════
async function gen_ch4_linear_probe() {
  const W=400, H=420;
  const slots = [
    {idx:0, value:'700'},
    {idx:1, value:'50'},
    {idx:2, value:'85', note:'← probe 1'},
    {idx:3, value:'92', note:'← probe 2'},
    {idx:4, value:'73', note:'← probe 1'},
    {idx:5, value:'101',note:'← probe 2'},
    {idx:6, value:'76'},
    {idx:7, value:''},
    {idx:8, value:''},
    {idx:9, value:''},
  ];
  let body = title('Linear Probing – h(k) = k mod 10', W/2, 22, DARK);
  body += hashTable(slots, 60, 45, 32, 80, 44);
  body += text(W/2, H-35, 'h(k,i) = (h(k) + i) mod m', DARK, 11, 'middle', true);
  body += text(W/2, H-18, 'Problem: Primary Clustering (long runs form)', RED, 10, 'middle');
  await save('ch4_linear_probe.png', svg(W, H, body));
}

// ══════════════════════════════════════════════════════════════════════════
// 24. ch4_quadratic.png
// ══════════════════════════════════════════════════════════════════════════
async function gen_ch4_quadratic() {
  const W=400, H=420;
  const slots = [
    {idx:0, value:'700'},
    {idx:1, value:'50'},
    {idx:2, value:'85', note:'← i=1: 1+1²=2'},
    {idx:3, value:'73'},
    {idx:4, value:'101',note:'← i=1: 3+1²=4'},
    {idx:5, value:'92', note:'← i=2: 1+2²=5'},
    {idx:6, value:'76'},
    {idx:7, value:''},
    {idx:8, value:''},
    {idx:9, value:''},
  ];
  let body = title('Quadratic Probing – h(k) = k mod 10', W/2, 22, DARK);
  body += hashTable(slots, 60, 45, 32, 80, 44);
  body += text(W/2, H-35, 'h(k,i) = (h(k) + i²) mod m', DARK, 11, 'middle', true);
  body += text(W/2, H-18, 'Secondary clustering: synonyms follow same probe sequence', ORANGE, 10, 'middle');
  await save('ch4_quadratic.png', svg(W, H, body));
}

// ══════════════════════════════════════════════════════════════════════════
// 25. ch4_chaining.png – Separate chaining
// ══════════════════════════════════════════════════════════════════════════
async function gen_ch4_chaining() {
  const W=520, H=380;
  // Slots 0-6 with chains
  const rows = [
    {idx:0, chain:['700']},
    {idx:1, chain:['50','85','92']},
    {idx:2, chain:[]},
    {idx:3, chain:['73','101']},
    {idx:4, chain:[]},
    {idx:5, chain:[]},
    {idx:6, chain:['76']},
  ];
  const slotH=38, indexW=40, nodeW=48, nodeH=28, ox=40, oy=50;
  let body = title('Separate Chaining – h(k) = k mod 7', W/2, 22, DARK);
  // Header
  body += roundRect(ox, oy, indexW, slotH, PURPLE, '#5B21B6');
  body += text(ox+indexW/2, oy+slotH/2+5, 'Idx', WHITE, 11, 'middle', true);
  rows.forEach((row, i) => {
    const y = oy + (i+1)*slotH;
    // Index cell
    body += roundRect(ox, y, indexW, slotH, '#EDE9FE', '#A78BFA', 0);
    body += text(ox+indexW/2, y+slotH/2+5, String(row.idx), PURPLE, 12, 'middle', true);
    // Arrow stub
    const ax = ox + indexW;
    if (row.chain.length > 0) {
      body += `<line x1="${ax}" y1="${y+slotH/2}" x2="${ax+20}" y2="${y+slotH/2}" stroke="${BLUE}" stroke-width="2" marker-end="url(#arr)"/>`;
    } else {
      body += `<line x1="${ax}" y1="${y+slotH/2}" x2="${ax+30}" y2="${y+slotH/2}" stroke="${GRAY}" stroke-width="1.5"/>`;
      body += text(ax+35, y+slotH/2+5, 'NULL', GRAY, 10, 'start');
    }
    // Chain nodes
    row.chain.forEach((val, j) => {
      const nx = ax + 24 + j*(nodeW+24);
      body += roundRect(nx, y+5, nodeW, nodeH, LBLUE, BLUE, 6);
      body += text(nx+nodeW/2, y+5+nodeH/2+4, val, BLUE, 11, 'middle', true);
      if (j < row.chain.length-1) {
        body += `<line x1="${nx+nodeW}" y1="${y+slotH/2}" x2="${nx+nodeW+20}" y2="${y+slotH/2}" stroke="${BLUE}" stroke-width="2" marker-end="url(#arr)"/>`;
      } else {
        body += `<line x1="${nx+nodeW}" y1="${y+slotH/2}" x2="${nx+nodeW+18}" y2="${y+slotH/2}" stroke="${GRAY}" stroke-width="1.5"/>`;
        body += text(nx+nodeW+22, y+slotH/2+5, 'NULL', GRAY, 9, 'start');
      }
    });
  });
  body += text(W/2, H-18, 'Each slot has a linked list of synonyms. No clustering. λ can exceed 1.0', DARK, 10, 'middle');
  await save('ch4_chaining.png', svg(W, H, body));
}


// ══════════════════════════════════════════════════════════════════════════
// NEW DIAGRAMS d01–d34
// ══════════════════════════════════════════════════════════════════════════
async function gen_d01() {
  const W=580, H=420;
  const nodes = [
    {id:'A',label:'A',parent:null},
    {id:'B',label:'B',parent:'A'},
    {id:'C',label:'C',parent:'A'},
    {id:'D',label:'D',parent:'B'},
    {id:'E',label:'E',parent:'B'},
    {id:'F',label:'F',parent:'C'},
    {id:'G',label:'G',parent:'C'},
    {id:'H',label:'H',parent:'D'},
  ];
  const pos = layoutTree(nodes, 80, 70);
  const ox=80, oy=70;
  let b = title('Binary Tree — All Terminologies', W/2, 26, DARK);
  b += drawTree(nodes, pos, 22, ox, oy);
  const ap=pos['A']; b += text(ap.x+ox+28, ap.y+oy+5,'← Root (Level 0)', DARK,11,'start');
  b += text(20, oy+5,'L0',PURPLE,11,'start');
  b += text(20, oy+80+5,'L1',PURPLE,11,'start');
  b += text(20, oy+160+5,'L2',PURPLE,11,'start');
  b += text(20, oy+240+5,'L3',PURPLE,11,'start');
  b += text(pos['H'].x+ox, pos['H'].y+oy+36,'Leaf',GREEN,10,'middle',true);
  b += text(pos['E'].x+ox, pos['E'].y+oy+36,'Leaf',GREEN,10,'middle',true);
  b += text(pos['F'].x+ox, pos['F'].y+oy+36,'Leaf',GREEN,10,'middle',true);
  b += text(pos['G'].x+ox, pos['G'].y+oy+36,'Leaf',GREEN,10,'middle',true);
  b += text(W/2, H-30,'Height=3  |  Degree(A)=2  |  Internal: B,C,D  |  Leaves: H,E,F,G',DARK,11,'middle');
  await save('ch1_tree_terms.png', svg(W,H,b));
}

async function gen_d02() {
  const W=420, H=280;
  const nodes=[
    {id:1,label:'1',parent:null},
    {id:2,label:'2',parent:1},
    {id:3,label:'3',parent:1},
    {id:4,label:'4',parent:2},
    {id:5,label:'5',parent:2},
    {id:6,label:'6',parent:3},
    {id:7,label:'7',parent:3},
  ];
  const pos=layoutTree(nodes,75,60);
  const ox=40,oy=55;
  let b=title('General Binary Tree',W/2,26,DARK);
  b+=drawTree(nodes,pos,22,ox,oy);
  await save('ch1_gen_binary.png',svg(W,H,b));
}

async function gen_d03() {
  const W=480, H=380;
  let b=title('Left Skewed  vs  Right Skewed Tree',W/2,26,DARK);
  b+=`<line x1="240" y1="40" x2="240" y2="360" stroke="${GRAY}" stroke-width="1.5" stroke-dasharray="6,4"/>`;
  const lx=100, ly=80, gap=70;
  b+=line(lx,ly,lx-30,ly+gap,GRAY);
  b+=line(lx-30,ly+gap,lx-60,ly+gap*2,GRAY);
  b+=circle(lx,ly,22,BLUE,'#1D4ED8','30');
  b+=circle(lx-30,ly+gap,22,BLUE,'#1D4ED8','20');
  b+=circle(lx-60,ly+gap*2,22,BLUE,'#1D4ED8','10');
  b+=text(lx, ly+gap*3+10,'Left Skewed Tree',DARK,11,'middle',true);
  const rx=360, ry=80;
  b+=line(rx,ry,rx+30,ry+gap,GRAY);
  b+=line(rx+30,ry+gap,rx+60,ry+gap*2,GRAY);
  b+=circle(rx,ry,22,BLUE,'#1D4ED8','10');
  b+=circle(rx+30,ry+gap,22,BLUE,'#1D4ED8','20');
  b+=circle(rx+60,ry+gap*2,22,BLUE,'#1D4ED8','30');
  b+=text(rx, ry+gap*3+10,'Right Skewed Tree',DARK,11,'middle',true);
  b+=text(W/2,H-25,'Height = n-1 for n nodes (worst case)',DARK,11,'middle');
  await save('ch1_skewed.png',svg(W,H,b));
}

async function gen_d04() {
  const W=420, H=280;
  const nodes=[
    {id:'A',label:'A',parent:null},
    {id:'B',label:'B',parent:'A'},
    {id:'C',label:'C',parent:'A'},
    {id:'D',label:'D',parent:'B'},
    {id:'E',label:'E',parent:'B'},
    {id:'F',label:'F',parent:'C'},
    {id:'G',label:'G',parent:'C'},
  ];
  const pos=layoutTree(nodes,75,60);
  const ox=50,oy=55;
  let b=title('Strictly Binary Tree',W/2,26,DARK);
  b+=drawTree(nodes,pos,22,ox,oy);
  b+=text(W/2,H-20,'Every node has exactly 0 or 2 children',DARK,11,'middle');
  await save('ch1_strictly_binary.png',svg(W,H,b));
}

async function gen_d05() {
  const W=660, H=340;
  const nodes=[
    {id:1,label:'1',parent:null},
    {id:2,label:'2',parent:1},{id:3,label:'3',parent:1},
    {id:4,label:'4',parent:2},{id:5,label:'5',parent:2},{id:6,label:'6',parent:3},{id:7,label:'7',parent:3},
    {id:8,label:'8',parent:4},{id:9,label:'9',parent:4},
    {id:10,label:'10',parent:5},{id:11,label:'11',parent:5},
    {id:12,label:'12',parent:6},{id:13,label:'13',parent:6},
    {id:14,label:'14',parent:7},{id:15,label:'15',parent:7},
  ];
  const pos=layoutTree(nodes,72,44);
  const allX=Object.values(pos).map(p=>p.x);
  const maxX=Math.max(...allX);
  const ox=Math.max(30,(W-maxX-60)/2), oy=55;
  let b=title('Full Binary Tree (Height=3, 15 nodes)',W/2,26,DARK);
  b+=drawTree(nodes,pos,18,ox,oy);
  b+=text(W/2,H-18,'Leaves=8 (level 3), Internal=7, Total=15=2^4-1',DARK,11,'middle');
  await save('ch1_full_bt.png',svg(W,H,b));
}

async function gen_d06() {
  const W=400, H=280;
  const nodes=[
    {id:'*',x:200,y:70,fill:ORANGE},
    {id:'+',x:110,y:150,fill:ORANGE},
    {id:'-',x:290,y:150,fill:ORANGE},
    {id:'a',x:60,y:230,fill:BLUE},
    {id:'b',x:160,y:230,fill:BLUE},
    {id:'c',x:240,y:230,fill:BLUE},
    {id:'d',x:340,y:230,fill:BLUE},
  ];
  let b=title('Expression Tree: (a + b) \u00d7 (c \u2212 d)',W/2,26,DARK);
  b+=line(200,70,110,150,GRAY);
  b+=line(200,70,290,150,GRAY);
  b+=line(110,150,60,230,GRAY);
  b+=line(110,150,160,230,GRAY);
  b+=line(290,150,240,230,GRAY);
  b+=line(290,150,340,230,GRAY);
  nodes.forEach(n=>{ b+=circle(n.x,n.y,22,n.fill,n.fill===ORANGE?'#C2410C':'#1D4ED8',n.id); });
  b+=text(W/2,H-18,'Operators: Orange | Operands: Blue',DARK,10,'middle');
  await save('ch1_expr1.png',svg(W,H,b));
}

async function gen_d07() {
  const W=520, H=340;
  let b=title('Expression Tree: a\u00d7b + c\u00f7d \u2212 e',W/2,26,DARK);
  const layout={
    '-':{x:260,y:70},
    '+':{x:160,y:150},
    'e':{x:380,y:150},
    '*':{x:90,y:230},
    '/':{x:240,y:230},
    'a':{x:50,y:310},
    'b':{x:130,y:310},
    'c':{x:200,y:310},
    'd':{x:280,y:310},
  };
  const edges=[
    ['-','+'],
    ['-','e'],
    ['+','*'],
    ['+','/'],
    ['*','a'],
    ['*','b'],
    ['/','c'],
    ['/','d'],
  ];
  edges.forEach(([p,c])=>{
    const pp=layout[p], cp=layout[c];
    b+=line(pp.x,pp.y,cp.x,cp.y,GRAY);
  });
  Object.entries(layout).forEach(([id,pos])=>{
    const isOp=['-','+','*','/'].includes(id);
    b+=circle(pos.x,pos.y,22,isOp?ORANGE:BLUE,isOp?'#C2410C':'#1D4ED8',xmlEsc(id));
  });
  b+=text(W/2,H-14,'Inorder: a*b+c/d-e | Postorder: ab* cd/ + e -',DARK,10,'middle');
  await save('ch1_expr2.png',svg(W,H,b));
}

async function gen_d08() {
  const W=600, H=400;
  let b=title('Linked Representation of BST',W/2,26,DARK);
  function nodeBox(x,y,lptr,data,rptr) {
    const bw=48,bh=34;
    let s='';
    s+=roundRect(x,y,bw,bh,'#FEF3C7','#D97706',0);
    s+=text(x+bw/2,y+bh/2+5,lptr,'#92400E',10,'middle');
    s+=roundRect(x+bw,y,bw,bh,LBLUE,BLUE,0);
    s+=text(x+bw+bw/2,y+bh/2+5,String(data),BLUE,11,'middle',true);
    s+=roundRect(x+bw*2,y,bw,bh,'#FEF3C7','#D97706',0);
    s+=text(x+bw*3-bw/2,y+bh/2+5,rptr,'#92400E',10,'middle');
    return s;
  }
  b+=nodeBox(240,80,'NULL','50','\u25cf');
  b+=nodeBox(80,200,'\u25cf','30','\u25cf');
  b+=nodeBox(400,200,'NULL','70','NULL');
  b+=nodeBox(80,310,'NULL','20','NULL');
  b+=arrow(264,114,128,200,DARK);
  b+=arrow(288,114,424,200,DARK);
  b+=arrow(104,234,128,310,DARK);
  b+=text(W/2,H-20,'Each node: [LEFT_PTR | DATA | RIGHT_PTR]',DARK,11,'middle');
  await save('ch1_linked_bst.png',svg(W,H,b));
}

async function gen_d09() {
  const W=680, H=320;
  let b=title('BST Construction: Step-by-step Insertion',W/2,26,DARK);
  const nodes1=[
    {id:50,label:'50',parent:null},
    {id:30,label:'30',parent:50},
    {id:70,label:'70',parent:50},
  ];
  const pos1=layoutTree(nodes1,80,60);
  b+=text(170,50,'After insert 50,30,70',DARK,11,'middle',true);
  b+=drawTree(nodes1,pos1,22,80,70);
  b+=`<line x1="340" y1="40" x2="340" y2="300" stroke="${GRAY}" stroke-width="1.5" stroke-dasharray="6,4"/>`;
  const nodes2=[
    {id:50,label:'50',parent:null},
    {id:30,label:'30',parent:50},
    {id:70,label:'70',parent:50},
    {id:20,label:'20',parent:30},
    {id:40,label:'40',parent:30},
    {id:60,label:'60',parent:70},
    {id:80,label:'80',parent:70},
  ];
  const pos2=layoutTree(nodes2,68,50);
  b+=text(510,50,'After insert 20,40,60,80',DARK,11,'middle',true);
  b+=drawTree(nodes2,pos2,20,360,70);
  await save('ch1_bst_steps.png',svg(W,H,b));
}

async function gen_d10() {
  const W=640, H=300;
  let b=title('Delete Leaf Node 40',W/2,26,DARK);
  const before=[
    {id:50,label:'50',parent:null},
    {id:30,label:'30',parent:50},
    {id:70,label:'70',parent:50},
    {id:20,label:'20',parent:30},
    {id:40,label:'40',parent:30,color:RED,stroke:'#991B1B'},
  ];
  const posB=layoutTree(before,72,55);
  b+=text(140,50,'Before',DARK,12,'middle',true);
  b+=drawTree(before,posB,22,40,70);
  b+=`<line x1="320" y1="40" x2="320" y2="280" stroke="${GRAY}" stroke-width="1.5" stroke-dasharray="6,4"/>`;
  const after=[
    {id:50,label:'50',parent:null},
    {id:30,label:'30',parent:50},
    {id:70,label:'70',parent:50},
    {id:20,label:'20',parent:30},
  ];
  const posA=layoutTree(after,72,55);
  b+=text(490,50,'After (40 deleted)',DARK,12,'middle',true);
  b+=drawTree(after,posA,22,360,70);
  b+=text(W/2,H-18,'Node 40 was a leaf — simply remove it',DARK,11,'middle');
  await save('ch1_bst_del_leaf.png',svg(W,H,b));
}

async function gen_d11() {
  const W=700, H=320;
  let b=title('Delete Root 50 \u2192 Replaced by Inorder Successor 60',W/2,26,DARK);
  const before=[
    {id:50,label:'50',parent:null,color:RED,stroke:'#991B1B'},
    {id:30,label:'30',parent:50},
    {id:70,label:'70',parent:50},
    {id:20,label:'20',parent:30},
    {id:40,label:'40',parent:30},
    {id:60,label:'60',parent:70,color:GREEN,stroke:'#166534'},
    {id:80,label:'80',parent:70},
  ];
  const posB=layoutTree(before,68,48);
  b+=text(170,50,'Before (50=red, 60=green)',DARK,11,'middle',true);
  b+=drawTree(before,posB,20,30,70);
  b+=`<line x1="350" y1="40" x2="350" y2="300" stroke="${GRAY}" stroke-width="1.5" stroke-dasharray="6,4"/>`;
  const after=[
    {id:60,label:'60',parent:null,color:GREEN,stroke:'#166534'},
    {id:30,label:'30',parent:60},
    {id:70,label:'70',parent:60},
    {id:20,label:'20',parent:30},
    {id:40,label:'40',parent:30},
    {id:80,label:'80',parent:70},
  ];
  const posA=layoutTree(after,68,48);
  b+=text(530,50,'After (60 is new root)',DARK,11,'middle',true);
  b+=drawTree(after,posA,20,370,70);
  b+=text(W/2,H-16,'Inorder successor of 50 = leftmost in right subtree = 60',DARK,11,'middle');
  await save('ch1_bst_del_root.png',svg(W,H,b));
}

async function gen_d12() {
  const W=560, H=320;
  let b=title('BST Search for key=60 (path highlighted)',W/2,26,DARK);
  const nodes=[
    {id:50,label:'50',parent:null,color:GREEN,stroke:'#166534'},
    {id:30,label:'30',parent:50},
    {id:70,label:'70',parent:50,color:GREEN,stroke:'#166534'},
    {id:20,label:'20',parent:30},
    {id:40,label:'40',parent:30},
    {id:60,label:'60',parent:70,color:ORANGE,stroke:'#C2410C'},
    {id:80,label:'80',parent:70},
  ];
  const pos=layoutTree(nodes,75,55);
  const ox=50,oy=60;
  b+=drawTree(nodes,pos,22,ox,oy);
  const p50=pos[50], p70=pos[70], p60=pos[60];
  b+=line(p50.x+ox,p50.y+oy,p70.x+ox,p70.y+oy,GREEN,3);
  b+=line(p70.x+ox,p70.y+oy,p60.x+ox,p60.y+oy,GREEN,3);
  b+=circle(p50.x+ox,p50.y+oy,22,GREEN,'#166534','50');
  b+=circle(p70.x+ox,p70.y+oy,22,GREEN,'#166534','70');
  b+=circle(p60.x+ox,p60.y+oy,22,ORANGE,'#C2410C','60');
  b+=text(W/2,H-20,'Path: 50\u219260>50\u2192go right\u219270<70\u2192go left\u219260=60\u2714 FOUND!',DARK,10,'middle');
  await save('ch1_bst_search.png',svg(W,H,b));
}

async function gen_d13() {
  const W=720, H=300;
  let b=title('Original Tree vs Mirror Image',W/2,26,DARK);
  const orig=[
    {id:1,label:'1',parent:null},
    {id:2,label:'2',parent:1},
    {id:3,label:'3',parent:1},
    {id:4,label:'4',parent:2},
    {id:5,label:'5',parent:2},
    {id:6,label:'6',parent:3},
    {id:7,label:'7',parent:3},
  ];
  const posO=layoutTree(orig,72,50);
  b+=text(150,50,'Original',DARK,12,'middle',true);
  b+=drawTree(orig,posO,22,30,70);
  b+=text(360,160,'\u27F9 Mirror',DARK,14,'middle',true);
  const mir=[
    {id:1,label:'1',parent:null},
    {id:3,label:'3',parent:1},
    {id:2,label:'2',parent:1},
    {id:7,label:'7',parent:3},
    {id:6,label:'6',parent:3},
    {id:5,label:'5',parent:2},
    {id:4,label:'4',parent:2},
  ];
  const posM=layoutTree(mir,72,50);
  b+=text(570,50,'Mirror',DARK,12,'middle',true);
  b+=drawTree(mir,posM,22,400,70);
  await save('ch1_mirror.png',svg(W,H,b));
}

async function gen_d14() {
  const W=620, H=320;
  let b=title('Balance Factors in AVL Trees',W/2,26,DARK);
  const nodes=[
    {id:50,label:'50',parent:null,color:GREEN,stroke:'#166534'},
    {id:30,label:'30',parent:50,color:GREEN,stroke:'#166534'},
    {id:70,label:'70',parent:50,color:GREEN,stroke:'#166534'},
    {id:20,label:'20',parent:30,color:GREEN,stroke:'#166534'},
  ];
  const pos=layoutTree(nodes,80,65);
  const ox=50,oy=70;
  b+=drawTree(nodes,pos,22,ox,oy);
  [[50,'BF=0'],[30,'BF=+1'],[70,'BF=0'],[20,'BF=0']].forEach(([id,lbl])=>{
    const p=pos[id];
    b+=text(p.x+ox+28,p.y+oy+5,lbl,DARK,10,'start');
  });
  b+=`<line x1="350" y1="40" x2="350" y2="300" stroke="${GRAY}" stroke-width="1.5" stroke-dasharray="6,4"/>`;
  b+=text(490,50,'Imbalanced (BF=+2)',RED,12,'middle',true);
  b+=line(490,90,440,160,GRAY);
  b+=line(440,160,400,230,GRAY);
  b+=circle(490,90,22,RED,'#991B1B','30');
  b+=text(520,95,'BF=+2',RED,10,'start',true);
  b+=circle(440,160,22,ORANGE,'#C2410C','20');
  b+=text(472,165,'BF=+1',ORANGE,10,'start');
  b+=circle(400,230,22,GREEN,'#166534','10');
  b+=text(428,235,'BF=0',GREEN,10,'start');
  b+=text(490,290,'Rotation needed!',RED,11,'middle',true);
  await save('ch2_balance_factors.png',svg(W,H,b));
}

async function gen_d15() {
  const W=800, H=280;
  let b=title('LL Rotation: Insert 30, 20, 10',W/2,26,DARK);
  const stages=[
    {lbl:'Insert 30',cx:80,nodes:[{x:80,y:100,v:'30',c:BLUE}],edges:[]},
    {lbl:'Insert 20',cx:220,nodes:[
      {x:220,y:100,v:'30',c:BLUE},
      {x:190,y:175,v:'20',c:BLUE},
    ],edges:[[220,100,190,175]]},
    {lbl:'Insert 10 (LL!)',cx:420,nodes:[
      {x:420,y:100,v:'30',c:RED},
      {x:390,y:175,v:'20',c:BLUE},
      {x:360,y:250,v:'10',c:BLUE},
    ],edges:[[420,100,390,175],[390,175,360,250]]},
    {lbl:'After LL Rotation',cx:620,nodes:[
      {x:620,y:130,v:'20',c:GREEN},
      {x:580,y:205,v:'10',c:BLUE},
      {x:660,y:205,v:'30',c:BLUE},
    ],edges:[[620,130,580,205],[620,130,660,205]]},
  ];
  stages.forEach(s=>{
    b+=text(s.cx,52,s.lbl,DARK,11,'middle',true);
    (s.edges||[]).forEach(([x1,y1,x2,y2])=>b+=line(x1,y1,x2,y2,GRAY));
    s.nodes.forEach(n=>b+=circle(n.x,n.y,20,n.c,n.c===RED?'#991B1B':'#1D4ED8',n.v));
    if(s.lbl.includes('LL!')) b+=text(s.cx+50,s.nodes[0].y,'BF=+2',RED,10,'start',true);
  });
  [175,365,555].forEach(ax=>b+=arrow(ax,150,ax+40,150,DARK));
  await save('ch2_ll_case.png',svg(W,H,b));
}

async function gen_d16() {
  const W=800, H=280;
  let b=title('RR Rotation: Insert 10, 20, 30',W/2,26,DARK);
  const stages=[
    {lbl:'Insert 10',nodes:[{x:80,y:100,v:'10',c:BLUE}],edges:[]},
    {lbl:'Insert 20',nodes:[{x:220,y:100,v:'10',c:BLUE},{x:250,y:175,v:'20',c:BLUE}],edges:[[220,100,250,175]]},
    {lbl:'Insert 30 (RR!)',nodes:[
      {x:420,y:100,v:'10',c:RED},
      {x:450,y:175,v:'20',c:BLUE},
      {x:480,y:250,v:'30',c:BLUE},
    ],edges:[[420,100,450,175],[450,175,480,250]]},
    {lbl:'After RR Rotation',nodes:[
      {x:620,y:130,v:'20',c:GREEN},
      {x:580,y:205,v:'10',c:BLUE},
      {x:660,y:205,v:'30',c:BLUE},
    ],edges:[[620,130,580,205],[620,130,660,205]]},
  ];
  stages.forEach((s,i)=>{
    const labelX=s.nodes[0].x+(i>=2?30:0);
    b+=text(labelX,52,s.lbl,DARK,11,'middle',true);
    s.edges.forEach(([x1,y1,x2,y2])=>b+=line(x1,y1,x2,y2,GRAY));
    s.nodes.forEach(n=>b+=circle(n.x,n.y,20,n.c,n.c===RED?'#991B1B':'#1D4ED8',n.v));
  });
  [175,365,555].forEach(ax=>b+=arrow(ax,150,ax+40,150,DARK));
  await save('ch2_rr_case.png',svg(W,H,b));
}

async function gen_d17() {
  const W=860, H=320;
  const BK='#1F2937';
  let b=title('RBT Insertions: 10\u219220\u219230\u219215',W/2,26,DARK);
  b+=text(80,52,'1: Insert 10',DARK,11,'middle',true);
  b+=circle(80,120,22,BK,'#111827','10');
  b+=text(80,152,'B',WHITE,9,'middle');
  b+=text(230,52,'2: Insert 20',DARK,11,'middle',true);
  b+=line(230,120,260,185,GRAY);
  b+=circle(230,120,22,BK,'#111827','10');
  b+=circle(260,185,22,RED,'#991B1B','20');
  b+=text(430,52,'3: Insert 30\u2192rotate',DARK,11,'middle',true);
  b+=line(430,120,395,185,GRAY);
  b+=line(430,120,465,185,GRAY);
  b+=circle(430,120,22,BK,'#111827','20');
  b+=circle(395,185,22,RED,'#991B1B','10');
  b+=circle(465,185,22,RED,'#991B1B','30');
  b+=text(660,52,'4: Insert 15\u2192recolor',DARK,11,'middle',true);
  b+=line(660,120,620,185,GRAY);
  b+=line(660,120,700,185,GRAY);
  b+=line(620,185,640,250,GRAY);
  b+=circle(660,120,22,BK,'#111827','20');
  b+=circle(620,185,22,BK,'#111827','10');
  b+=circle(700,185,22,BK,'#111827','30');
  b+=circle(640,250,22,RED,'#991B1B','15');
  [145,315,510].forEach(ax=>b+=arrow(ax,140,ax+30,140,DARK));
  b+=text(W/2,H-16,'BLACK=dark gray, RED=red. Root always BLACK.',DARK,10,'middle');
  await save('ch2_rbt_insert.png',svg(W,H,b));
}

async function gen_d18() {
  const W=640, H=380;
  let b=title('B-Tree Order 3: Inserting 5, 3, 8, 1, 4',W/2,26,DARK);
  function btNode(x,y,keys,w,h) {
    w=w||60; h=h||32;
    let s=roundRect(x-w/2,y-h/2,w,h,LBLUE,BLUE,10);
    s+=text(x,y+5,keys,BLUE,12,'middle',true);
    return s;
  }
  b+=text(80,55,'[5]',DARK,11,'middle',true);
  b+=btNode(80,90,'5');
  b+=text(220,55,'[3|5]',DARK,11,'middle',true);
  b+=btNode(220,90,'3|5',70);
  b+=text(380,55,'split\u21923|5\u21928',DARK,11,'middle',true);
  b+=btNode(380,90,'5');
  b+=btNode(330,155,'3');
  b+=btNode(430,155,'8');
  b+=line(380,107,330,138,GRAY);
  b+=line(380,107,430,138,GRAY);
  b+=text(530,55,'add 1,4',DARK,11,'middle',true);
  b+=btNode(530,90,'5');
  b+=btNode(490,155,'1|3',70);
  b+=btNode(570,155,'8');
  b+=line(530,107,490,138,GRAY);
  b+=line(530,107,570,138,GRAY);
  b+=btNode(490,225,'4');
  b+=line(490,172,490,208,GRAY);
  b+=text(W/2,H-20,'Overflow triggers split; median promoted to parent',DARK,11,'middle');
  await save('ch2_btree_insert.png',svg(W,H,b));
}

async function gen_d19() {
  const W=500, H=380;
  let b=title('Graph Terminology',W/2,26,DARK);
  const verts={A:{x:250,y:80},B:{x:130,y:170},C:{x:370,y:170},D:{x:130,y:280},E:{x:370,y:280}};
  const edges=[['A','B'],['A','C'],['B','C'],['B','D'],['B','E'],['C','E']];
  edges.forEach(([u,v])=>b+=line(verts[u].x,verts[u].y,verts[v].x,verts[v].y,GRAY,2));
  Object.entries(verts).forEach(([id,p])=>b+=circle(p.x,p.y,22,BLUE,'#1D4ED8',id));
  b+=text(250,54,'Vertex A',DARK,10,'middle');
  b+=text(55,170,'Vertex B',DARK,10,'middle');
  b+=arrow(190,90,220,78,DARK);
  b+=text(80,225,'Degree(B)=4',PURPLE,11,'start',true);
  b+=text(80,245,'(connects to A,C,D,E)',DARK,10,'start');
  b+=text(250,340,'Path: A\u2192B\u2192D',GREEN,11,'middle',true);
  b+=text(250,358,'Edge between A-B',DARK,10,'middle');
  await save('ch3_graph_terms.png',svg(W,H,b));
}

async function gen_d20() {
  const W=640, H=380;
  let b=title('Graph \u2192 Adjacency List Representation',W/2,26,DARK);
  const verts={1:{x:80,y:110},2:{x:200,y:80},3:{x:200,y:200},4:{x:120,y:220}};
  const edges=[[1,2],[1,3],[2,3],[2,4],[3,4]];
  edges.forEach(([u,v])=>b+=line(verts[u].x,verts[u].y,verts[v].x,verts[v].y,GRAY,2));
  Object.entries(verts).forEach(([id,p])=>b+=circle(p.x,p.y,22,BLUE,'#1D4ED8',id));
  b+=text(140,50,'Graph (4 nodes)',DARK,12,'middle',true);
  b+=`<line x1="280" y1="40" x2="280" y2="360" stroke="${GRAY}" stroke-width="1.5" stroke-dasharray="5,4"/>`;
  b+=text(460,50,'Adjacency List',DARK,12,'middle',true);
  const lists=[
    [1,['2','3']],
    [2,['1','3','4']],
    [3,['1','2','4']],
    [4,['2','3']],
  ];
  lists.forEach(([vtx,nbrs],i)=>{
    const y=80+i*72;
    b+=roundRect(300,y,36,28,PURPLE,'#5B21B6',6);
    b+=text(318,y+19,String(vtx),WHITE,12,'middle',true);
    let x=346;
    nbrs.forEach((n)=>{
      x+=16;
      b+=roundRect(x,y,38,28,LBLUE,BLUE,6);
      b+=text(x+19,y+19,n,BLUE,11,'middle',true);
      x+=38;
    });
    b+=text(x+4,y+19,'NULL',GRAY,9,'start');
  });
  await save('ch3_adj_list.png',svg(W,H,b));
}

async function gen_d21() {
  const W=640, H=380;
  let b=title('Directed Graph \u2192 Inverse Adjacency List',W/2,26,DARK);
  const verts={1:{x:80,y:110},2:{x:200,y:80},3:{x:200,y:200},4:{x:120,y:220}};
  const dedges=[[1,2],[1,3],[2,4],[3,4]];
  dedges.forEach(([u,v])=>b+=arrow(verts[u].x,verts[u].y,verts[v].x,verts[v].y,DARK));
  Object.entries(verts).forEach(([id,p])=>b+=circle(p.x,p.y,22,BLUE,'#1D4ED8',id));
  b+=text(140,50,'Directed Graph',DARK,12,'middle',true);
  b+=`<line x1="280" y1="40" x2="280" y2="360" stroke="${GRAY}" stroke-width="1.5" stroke-dasharray="5,4"/>`;
  b+=text(460,50,'Inverse Adj. List (Predecessors)',DARK,11,'middle',true);
  const invLists=[
    [1,[]],
    [2,['1']],
    [3,['1']],
    [4,['2','3']],
  ];
  invLists.forEach(([vtx,preds],i)=>{
    const y=80+i*72;
    b+=roundRect(300,y,36,28,PURPLE,'#5B21B6',6);
    b+=text(318,y+19,String(vtx),WHITE,12,'middle',true);
    if(preds.length===0){
      b+=text(350,y+19,'[ ]',GRAY,10,'start');
    } else {
      let x=344;
      preds.forEach(n=>{
        x+=16;
        b+=roundRect(x,y,38,28,LBLUE,BLUE,6);
        b+=text(x+19,y+19,n,BLUE,11,'middle',true);
        x+=38;
      });
      b+=text(x+4,y+19,'NULL',GRAY,9,'start');
    }
  });
  await save('ch3_inv_adj.png',svg(W,H,b));
}

async function gen_d22() {
  const W=460, H=380;
  let b=title('DFS from Vertex 1 \u2014 Order: 1,2,4,5,3,6',W/2,26,DARK);
  const verts={1:{x:230,y:80},2:{x:130,y:170},3:{x:330,y:170},4:{x:80,y:260},5:{x:180,y:260},6:{x:330,y:260}};
  [[1,2],[1,3],[2,4],[2,5],[3,6]].forEach(([u,v])=>b+=line(verts[u].x,verts[u].y,verts[v].x,verts[v].y,GRAY,2));
  [[1,2],[2,4],[2,5],[1,3],[3,6]].forEach(([u,v])=>b+=line(verts[u].x,verts[u].y,verts[v].x,verts[v].y,RED,3));
  const order={1:1,2:2,4:3,5:4,3:5,6:6};
  Object.entries(verts).forEach(([id,p])=>{
    b+=circle(p.x,p.y,22,BLUE,'#1D4ED8',id);
    b+=text(p.x+27,p.y-12,''+order[id],ORANGE,11,'start',true);
  });
  b+=text(W/2,310,'RED edges = DFS tree edges',RED,11,'middle',true);
  b+=text(W/2,330,'Numbers = DFS visit order',DARK,11,'middle');
  b+=text(W/2,H-15,'Stack: [1] \u2192 [2,3] \u2192 [4,5,3] \u2192 ...',DARK,10,'middle');
  await save('ch3_dfs_example.png',svg(W,H,b));
}

async function gen_d23() {
  const W=500, H=340;
  let b=title('Topological Sort \u2014 Kahn\'s Algorithm',W/2,26,DARK);
  const verts={
    A:{x:140,y:80},B:{x:320,y:80},
    C:{x:80,y:185},D:{x:250,y:185},E:{x:420,y:185},
    F:{x:250,y:290},
  };
  [['A','C'],['A','D'],['B','D'],['B','E'],['C','F'],['D','F'],['E','F']].forEach(([u,v])=>
    b+=arrow(verts[u].x,verts[u].y,verts[v].x,verts[v].y,DARK)
  );
  Object.entries(verts).forEach(([id,p])=>b+=circle(p.x,p.y,22,BLUE,'#1D4ED8',id));
  b+=text(W/2,55,'Layer 0: A, B',PURPLE,11,'middle');
  b+=text(W/2,160,'Layer 1: C, D, E',PURPLE,11,'middle');
  b+=text(W/2,268,'Layer 2: F',PURPLE,11,'middle');
  b+=text(W/2,H-16,'Topological Order: A, B, C, D, E, F',GREEN,12,'middle',true);
  await save('ch3_topo_sort.png',svg(W,H,b));
}

async function gen_d24() {
  const W=620, H=380;
  let b=title('Floyd-Warshall: Initial \u2192 Final Distance Matrix',W/2,26,DARK);
  const initial=[
    ['','0','1','2','3'],
    ['0','0','3','8','\u221e'],
    ['1','\u221e','0','-4','1'],
    ['2','\u221e','\u221e','0','7'],
    ['3','2','\u221e','5','0'],
  ];
  const fin=[
    ['','0','1','2','3'],
    ['0','0','1','-3','2'],
    ['1','3','0','-4','1'],
    ['2','10','7','0','7'],
    ['3','2','-1','-5','0'],
  ];
  function drawMatrix(ox,oy,data,lbl) {
    let s=text(ox+80,oy-12,lbl,DARK,12,'middle',true);
    const cw=36,rh=28;
    data.forEach((row,ri)=>{
      row.forEach((cell,ci)=>{
        const x=ox+ci*cw,y=oy+ri*rh;
        const isHeader=ri===0||ci===0;
        const fill=isHeader?LBLUE:(ri%2===0?'#F8FAFC':'#FFFFFF');
        const stroke=isHeader?BLUE:GRAY;
        s+=`<rect x="${x}" y="${y}" width="${cw}" height="${rh}" fill="${fill}" stroke="${stroke}" stroke-width="1"/>`;
        s+=text(x+cw/2,y+rh/2+5,String(cell),isHeader?BLUE:DARK,10,'middle');
      });
    });
    return s;
  }
  b+=drawMatrix(20,60,initial,'Initial D');
  b+=text(310,200,'\u27F9',DARK,24,'middle');
  b+=drawMatrix(340,60,fin,'Final D');
  b+=text(W/2,H-16,'Negative values allowed; diagonal always 0',DARK,10,'middle');
  await save('ch3_floyd.png',svg(W,H,b));
}

async function gen_d25() {
  const W=540, H=420;
  let b=title('Social Network Graph Analysis',W/2,26,DARK);
  const verts={
    Alice:{x:200,y:100},Bob:{x:340,y:100},
    Charlie:{x:440,y:200},David:{x:270,y:200},
    Eve:{x:420,y:310},Frank:{x:90,y:200},
  };
  [['Alice','Bob'],['Bob','Charlie'],['Alice','David'],['Bob','David'],['Charlie','Eve'],['Alice','Frank']].forEach(([u,v])=>
    b+=line(verts[u].x,verts[u].y,verts[v].x,verts[v].y,GRAY,2)
  );
  Object.entries(verts).forEach(([name,p])=>b+=circle(p.x,p.y,28,BLUE,'#1D4ED8',name.substring(0,3)));
  Object.entries(verts).forEach(([name,p])=>b+=text(p.x,p.y+42,name,DARK,10,'middle'));
  b+=text(340,72,'Degree=4\n(Hub)',PURPLE,10,'middle',true);
  b+=text(90,235,'Bridge\nVertex',RED,10,'middle',true);
  b+=text(W/2,H-18,'Nodes=people, Edges=friendships | Hub=high-degree node',DARK,10,'middle');
  await save('ch3_social.png',svg(W,H,b));
}

async function gen_d26() {
  const W=600, H=380;
  let b=title('Concept of Hashing \u2014 Keys to Hash Table',W/2,26,DARK);
  const keys=[{k:'K1=25',h:3},{k:'K2=67',h:4},{k:'K3=89',h:5},{k:'K4=42',h:0}];
  keys.forEach((kv,i)=>{
    const y=90+i*60;
    b+=roundRect(20,y-15,90,30,LBLUE,BLUE,6);
    b+=text(65,y+5,kv.k,BLUE,11,'middle',true);
    b+=arrow(112,y,210,180+kv.h*10,DARK);
  });
  b+=roundRect(215,145,140,60,'#EDE9FE','#7C3AED',10);
  b+=text(285,170,'Hash Function',PURPLE,11,'middle',true);
  b+=text(285,186,'h(k) = k mod 7',PURPLE,10,'middle');
  [3,4,5,0].forEach((slot,i)=>{
    b+=arrow(357,175+i*5, 420,90+slot*38,GREEN);
  });
  for(let i=0;i<7;i++){
    const y=72+i*38;
    b+=roundRect(425,y,130,32,i%2===0?'#F0FDF4':'#ECFDF5',GREEN,4);
    b+=text(448,y+20,String(i),GREEN,11,'start',true);
    if(i===0) b+=text(490,y+20,'42',DARK,10,'start');
    else if(i===3) b+=text(490,y+20,'25',DARK,10,'start');
    else if(i===4) b+=text(490,y+20,'67',DARK,10,'start');
    else if(i===5) b+=text(490,y+20,'89',DARK,10,'start');
    else b+=text(490,y+20,'\u2014',GRAY,10,'start');
  }
  b+=text(W/2,H-16,'Keys map directly to table indices via hash function',DARK,10,'middle');
  await save('ch4_hash_concept.png',svg(W,H,b));
}

async function gen_d27() {
  const W=480, H=280;
  let b=title('Folding Method: Key=123203241, m=1000',W/2,26,DARK);
  const groups=['123','203','241'];
  const colors=[BLUE,PURPLE,GREEN];
  groups.forEach((g,i)=>{
    const x=60+i*120;
    const fill=colors[i]===BLUE?LBLUE:'#EDE9FE';
    b+=roundRect(x,70,80,36,fill,colors[i],8);
    b+=text(x+40,93,g,colors[i],15,'middle',true);
  });
  b+=text(160,90,'+',DARK,18,'middle',true);
  b+=text(280,90,'+',DARK,18,'middle',true);
  b+=arrow(240,116,240,155,DARK);
  b+=roundRect(170,160,140,36,LBLUE,BLUE,8);
  b+=text(240,183,'123+203+241 = 567',BLUE,12,'middle',true);
  b+=arrow(240,200,240,230,DARK);
  b+=text(240,250,'h(k) = 567 mod 1000 = 567',GREEN,12,'middle',true);
  b+=text(10,52,'Key: 123203241 \u2192 split into 3-digit groups',DARK,11,'start');
  await save('ch4_folding.png',svg(W,H,b));
}

async function gen_d28() {
  const W=460, H=380;
  let b=title('Double Hashing: h1=k mod 7, h2=1+(k mod 6)',W/2,26,DARK);
  const slotData=['700','50','\u2014','\u2014','92','\u2014','76'];
  for(let i=0;i<7;i++){
    const y=60+i*38;
    b+=roundRect(30,y,50,32,'#F8FAFC',GRAY,0);
    b+=text(55,y+20,String(i),DARK,11,'middle',true);
    b+=roundRect(80,y,100,32,slotData[i]==='\u2014'?'#F8FAFC':LBLUE,slotData[i]==='\u2014'?GRAY:BLUE,0);
    b+=text(130,y+20,slotData[i],slotData[i]==='\u2014'?GRAY:BLUE,11,'middle');
  }
  b+=text(240,75,'h1(22) = 22 mod 7 = 1',DARK,11,'start');
  b+=text(240,100,'Slot 1 = 50 \u2260 22 (collision!)',RED,11,'start');
  b+=text(240,130,'h2(22) = 1+(22 mod 6)',DARK,11,'start');
  b+=text(240,148,'     = 1+4 = 5',DARK,11,'start');
  b+=text(240,175,'Probe: (1+1\u00d75) mod 7 = 6',DARK,11,'start');
  b+=text(240,200,'Slot 6 = empty \u2713 Insert!',GREEN,11,'start',true);
  b+=roundRect(30,60+6*38,50,32,'#F0FDF4',GREEN,0);
  b+=text(55,60+6*38+20,'6',DARK,11,'middle',true);
  b+=roundRect(80,60+6*38,100,32,'#DCFCE7',GREEN,0);
  b+=text(130,60+6*38+20,'22',GREEN,11,'middle',true);
  b+=text(W/2,H-16,'Different step sizes eliminate secondary clustering',DARK,10,'middle');
  await save('ch4_double_hash.png',svg(W,H,b));
}

async function gen_d29() {
  const W=660, H=300;
  let b=title('AVL Deletion: Delete 30 (no rotation needed)',W/2,26,DARK);
  const before=[
    {id:50,label:'50',parent:null},
    {id:30,label:'30',parent:50,color:RED,stroke:'#991B1B'},
    {id:70,label:'70',parent:50},
    {id:20,label:'20',parent:30},
    {id:60,label:'60',parent:70},
    {id:80,label:'80',parent:70},
  ];
  const posB=layoutTree(before,72,55);
  b+=text(150,50,'Before',DARK,12,'middle',true);
  b+=drawTree(before,posB,22,30,70);
  b+=text(150,H-20,'BF(50)=0',DARK,10,'middle');
  b+=`<line x1="320" y1="40" x2="320" y2="280" stroke="${GRAY}" stroke-width="1.5" stroke-dasharray="6,4"/>`;
  const after=[
    {id:50,label:'50',parent:null},
    {id:20,label:'20',parent:50},
    {id:70,label:'70',parent:50},
    {id:60,label:'60',parent:70},
    {id:80,label:'80',parent:70},
  ];
  const posA=layoutTree(after,72,55);
  b+=text(490,50,'After (30 deleted)',DARK,12,'middle',true);
  b+=drawTree(after,posA,22,350,70);
  b+=text(490,H-20,'BF(50)=-1 \u2713 Still balanced',GREEN,10,'middle');
  await save('ch2_avl_delete.png',svg(W,H,b));
}

async function gen_d30() {
  const W=460, H=340;
  const BK='#1F2937';
  let b=title('Red-Black Tree \u2014 Black Height Property',W/2,26,DARK);
  b+=line(230,90,140,175,GRAY,2);
  b+=line(230,90,320,175,GRAY,2);
  b+=line(140,175,100,260,GRAY,2);
  b+=line(140,175,180,260,GRAY,2);
  b+=line(320,175,280,260,GRAY,2);
  b+=line(320,175,360,260,GRAY,2);
  b+=circle(230,90,26,BK,'#111827','20');
  b+=circle(140,175,26,BK,'#111827','10');
  b+=circle(320,175,26,BK,'#111827','30');
  [[100,260],[180,260],[280,260],[360,260]].forEach(([x,y])=>{
    b+=roundRect(x-14,y-10,28,20,BK,'#111827',3);
    b+=text(x,y+4,'NIL',WHITE,8,'middle');
  });
  b+=text(268,93,'bh=2',PURPLE,11,'start');
  b+=text(174,178,'bh=1',PURPLE,11,'start');
  b+=text(354,178,'bh=1',PURPLE,11,'start');
  [100,180,280,360].forEach(x=>b+=text(x+16,266,'bh=0',GRAY,9,'start'));
  b+=text(W/2,H-20,'Black height = # BLACK nodes on any path to leaf (excluding self)',DARK,10,'middle');
  await save('ch2_black_height.png',svg(W,H,b));
}

async function gen_d31() {
  const W=560, H=320;
  let b=title('Graph with 3 Connected Components',W/2,26,DARK);
  const c1={1:{x:100,y:150},2:{x:160,y:100},3:{x:160,y:200}};
  [[1,2],[2,3],[1,3]].forEach(([u,v])=>b+=line(c1[u].x,c1[u].y,c1[v].x,c1[v].y,BLUE,2));
  Object.entries(c1).forEach(([id,p])=>b+=circle(p.x,p.y,22,BLUE,'#1D4ED8',id));
  b+=`<rect x="62" y="65" width="130" height="165" fill="none" stroke="${BLUE}" stroke-width="1.5" stroke-dasharray="8,4" rx="10"/>`;
  b+=text(127,55,'Component 1',BLUE,11,'middle',true);
  const c2={4:{x:300,y:130},5:{x:380,y:130},6:{x:340,y:200}};
  [[4,5],[5,6],[4,6]].forEach(([u,v])=>b+=line(c2[u].x,c2[u].y,c2[v].x,c2[v].y,GREEN,2));
  Object.entries(c2).forEach(([id,p])=>b+=circle(p.x,p.y,22,GREEN,'#166534',id));
  b+=`<rect x="264" y="90" width="140" height="140" fill="none" stroke="${GREEN}" stroke-width="1.5" stroke-dasharray="8,4" rx="10"/>`;
  b+=text(334,80,'Component 2',GREEN,11,'middle',true);
  b+=circle(490,150,22,PURPLE,'#5B21B6','7');
  b+=`<rect x="455" y="110" width="70" height="80" fill="none" stroke="${PURPLE}" stroke-width="1.5" stroke-dasharray="8,4" rx="10"/>`;
  b+=text(490,100,'Component 3',PURPLE,11,'middle',true);
  b+=text(W/2,H-16,'DFS/BFS restarts for each unvisited vertex to find all components',DARK,10,'middle');
  await save('ch3_components.png',svg(W,H,b));
}

async function gen_d32() {
  const W=420, H=360;
  let b=title('Bipartite Graph \u2014 Two Disjoint Sets',W/2,26,DARK);
  const setU={1:{x:120,y:110},3:{x:120,y:200},5:{x:120,y:290}};
  const setV={2:{x:300,y:110},4:{x:300,y:200},6:{x:300,y:290}};
  [['1','2'],['1','4'],['3','2'],['3','6'],['5','4'],['5','6']].forEach(([u,v])=>{
    const a=setU[u], c=setV[v];
    b+=line(a.x,a.y,c.x,c.y,GRAY,2);
  });
  Object.entries(setU).forEach(([id,p])=>b+=circle(p.x,p.y,22,BLUE,'#1D4ED8',id));
  Object.entries(setV).forEach(([id,p])=>b+=circle(p.x,p.y,22,GREEN,'#166534',id));
  b+=text(120,58,'Set U',BLUE,13,'middle',true);
  b+=text(300,58,'Set V',GREEN,13,'middle',true);
  b+=text(W/2,H-16,'No edges within same set! All edges cross between U and V',DARK,10,'middle');
  await save('ch3_bipartite.png',svg(W,H,b));
}

async function gen_d33() {
  const W=560, H=340;
  let b=title('Strongly Connected Components (SCCs)',W/2,26,DARK);
  const verts={
    1:{x:100,y:140,c:RED,s:'#991B1B'},
    2:{x:180,y:140,c:RED,s:'#991B1B'},
    3:{x:290,y:140,c:BLUE,s:'#1D4ED8'},
    4:{x:370,y:140,c:BLUE,s:'#1D4ED8'},
    5:{x:460,y:100,c:GREEN,s:'#166534'},
    6:{x:460,y:185,c:GREEN,s:'#166534'},
  };
  b+=arrow(100,140,165,140,DARK);
  b+=arrow(180,140,115,140,DARK);
  b+=arrow(195,140,275,140,DARK);
  b+=arrow(290,140,355,140,DARK);
  b+=arrow(370,140,305,140,DARK);
  b+=arrow(385,130,450,108,DARK);
  b+=arrow(460,115,460,170,DARK);
  b+=arrow(460,185,460,155,DARK);
  Object.entries(verts).forEach(([id,v])=>b+=circle(v.x,v.y,22,v.c,v.s,id));
  b+=`<ellipse cx="140" cy="140" rx="60" ry="32" fill="none" stroke="${RED}" stroke-width="1.5" stroke-dasharray="8,4"/>`;
  b+=`<ellipse cx="330" cy="140" rx="60" ry="32" fill="none" stroke="${BLUE}" stroke-width="1.5" stroke-dasharray="8,4"/>`;
  b+=`<ellipse cx="460" cy="142" rx="30" ry="60" fill="none" stroke="${GREEN}" stroke-width="1.5" stroke-dasharray="8,4"/>`;
  b+=text(140,90,'SCC1: {1,2}',RED,11,'middle',true);
  b+=text(330,90,'SCC2: {3,4}',BLUE,11,'middle',true);
  b+=text(500,60,'SCC3:',GREEN,11,'start',true);
  b+=text(500,76,'{5,6}',GREEN,11,'start',true);
  b+=text(W/2,H-16,'Each SCC: all vertices mutually reachable via directed paths',DARK,10,'middle');
  await save('ch3_scc.png',svg(W,H,b));
}

async function gen_d34() {
  const W=640, H=380;
  let b=title('Rehashing: m=7 \u2192 m=17 (load factor exceeded)',W/2,26,DARK);
  b+=text(100,50,'Old Table (m=7)',DARK,12,'middle',true);
  const oldData=['700','50','\u2014','73','\u2014','\u2014','76'];
  oldData.forEach((v,i)=>{
    const y=70+i*36;
    b+=roundRect(30,y,50,30,'#F8FAFC',GRAY,0);
    b+=text(55,y+19,String(i),DARK,11,'middle');
    b+=roundRect(80,y,90,30,v==='\u2014'?'#F8FAFC':LBLUE,v==='\u2014'?GRAY:BLUE,0);
    b+=text(125,y+19,v,v==='\u2014'?GRAY:BLUE,11,'middle');
  });
  b+=text(100,H-30,'\u03b1 = 4/7 \u2248 0.57',DARK,10,'middle');
  b+=text(310,190,'\u27F9 Rehash',DARK,16,'middle',true);
  b+=text(310,212,'m\u2019 = 17',DARK,11,'middle');
  b+=text(500,50,'New Table (m=17)',DARK,12,'middle',true);
  const newData=Array(17).fill('\u2014');
  newData[3]='700'; newData[5]='73'; newData[8]='76'; newData[16]='50';
  const showSlots=[0,1,2,3,4,5,6,'...',14,15,16];
  let yi=70;
  showSlots.forEach(slot=>{
    const y=yi;
    if(typeof slot === 'string'){
      b+=text(500,y+14,'\u22ee',GRAY,14,'middle');
      yi+=22;
    } else {
      b+=roundRect(450,y,40,28,'#F8FAFC',GRAY,0);
      b+=text(470,y+18,String(slot),DARK,10,'middle');
      const val=newData[slot]||'\u2014';
      b+=roundRect(490,y,100,28,val==='\u2014'?'#F8FAFC':'#DCFCE7',val==='\u2014'?GRAY:GREEN,0);
      b+=text(540,y+18,val,val==='\u2014'?GRAY:GREEN,11,'middle');
      yi+=30;
    }
  });
  b+=text(500,H-30,'Keys spread more evenly \u2713',GREEN,10,'middle');
  await save('ch4_rehash.png',svg(W,H,b));
}


// ══════════════════════════════════════════════════════════════════════════
// ch1_bst_del_one_child.png – BST delete node with one child
// ══════════════════════════════════════════════════════════════════════════
async function gen_ch1_bst_del_one_child() {
  const W = 640, H = 300;
  let b = title('BST Delete: Node with One Child', W/2, 24, DARK);

  // Before tree: root=50, left=30(left=20), right=70
  const beforeNodes = [
    {id:'B50',label:'50',parent:null},
    {id:'B30',label:'30',parent:'B50'},
    {id:'B70',label:'70',parent:'B50'},
    {id:'B20',label:'20',parent:'B30'},
  ];
  const bPos = layoutTree(beforeNodes, 70, 52);
  // shift to left panel
  const bOx = 20, bOy = 55;
  b += text(140, 50, 'Before: Delete 30', DARK, 12, 'middle', true);
  b += drawTree(beforeNodes, bPos, 20, bOx, bOy);
  // highlight node 30 in red
  const p30 = bPos['B30'];
  b += circle(p30.x + bOx, p30.y + bOy, 20, RED, RED, '30', WHITE, 13, true);

  // After tree: root=50, left=20, right=70
  const afterNodes = [
    {id:'A50',label:'50',parent:null},
    {id:'A20',label:'20',parent:'A50'},
    {id:'A70',label:'70',parent:'A50'},
  ];
  const aPos = layoutTree(afterNodes, 70, 60);
  const aOx = 350, aOy = 55;
  b += text(490, 50, 'After: 20 takes place of 30', DARK, 12, 'middle', true);
  b += drawTree(afterNodes, aPos, 20, aOx, aOy);
  // highlight node 20 in green
  const pa20 = aPos['A20'];
  b += circle(pa20.x + aOx, pa20.y + aOy, 20, GREEN, GREEN, '20', WHITE, 13, true);

  // arrow between panels
  b += arrow(285, H/2, 340, H/2, BLUE);

  await save('ch1_bst_del_one_child.png', svg(W, H, b));
}

// ══════════════════════════════════════════════════════════════════════════
// ch2_avl_del_imbal.png – AVL delete causing potential imbalance
// ══════════════════════════════════════════════════════════════════════════
async function gen_ch2_avl_del_imbal() {
  const W = 620, H = 300;
  let b = title('AVL Delete: Before and After Deleting 10', W/2, 24, DARK);

  // Before: root=30(BF=0), left=20(BF=+1,left=10), right=40(BF=0)
  const beforeNodes = [
    {id:'B30',label:'30',parent:null},
    {id:'B20',label:'20',parent:'B30'},
    {id:'B40',label:'40',parent:'B30'},
    {id:'B10',label:'10',parent:'B20'},
    {id:'B25',label:'25',parent:'B20'},
  ];
  const bPos = layoutTree(beforeNodes, 68, 50);
  const bOx = 10, bOy = 55;
  b += text(145, 50, 'Before: Delete 10', DARK, 12, 'middle', true);
  b += drawTree(beforeNodes, bPos, 19, bOx, bOy);
  // label BF on each node
  b += text(bPos['B30'].x+bOx, bPos['B30'].y+bOy-28, 'BF=0', BLUE, 10, 'middle');
  b += text(bPos['B20'].x+bOx, bPos['B20'].y+bOy-28, 'BF=+1', BLUE, 10, 'middle');
  b += text(bPos['B40'].x+bOx, bPos['B40'].y+bOy-28, 'BF=0', BLUE, 10, 'middle');
  // highlight node 10 in red (to be deleted)
  const pb10 = bPos['B10'];
  b += circle(pb10.x+bOx, pb10.y+bOy, 19, RED, RED, '10', WHITE, 12, true);

  // After delete 10: root=30(BF=0), left=20(BF=0,right=25), right=40(BF=0)
  const afterNodes = [
    {id:'A30',label:'30',parent:null},
    {id:'A20',label:'20',parent:'A30'},
    {id:'A40',label:'40',parent:'A30'},
    {id:'A25',label:'25',parent:'A20'},
  ];
  const aPos = layoutTree(afterNodes, 68, 52);
  const aOx = 330, aOy = 55;
  b += text(480, 50, 'After Delete 10 (Balanced ✓)', DARK, 12, 'middle', true);
  b += drawTree(afterNodes, aPos, 19, aOx, aOy);
  b += text(aPos['A30'].x+aOx, aPos['A30'].y+aOy-28, 'BF=0', GREEN, 10, 'middle');
  b += text(aPos['A20'].x+aOx, aPos['A20'].y+aOy-28, 'BF=-1', GREEN, 10, 'middle');
  b += text(aPos['A40'].x+aOx, aPos['A40'].y+aOy-28, 'BF=0', GREEN, 10, 'middle');

  b += arrow(295, H/2, 325, H/2, BLUE);
  b += text(W/2, H-15, 'No rotation needed — still balanced', GREEN, 11, 'middle', true);

  await save('ch2_avl_del_imbal.png', svg(W, H, b));
}


(async () => {
  console.log('Generating diagrams...\n');
  await gen_ch1_terminology();
  await gen_ch1_bst();
  await gen_ch1_bst_insert();
  await gen_ch1_traversal();
  await gen_ch1_max_heap();
  await gen_ch1_min_heap();
  await gen_ch1_complete_bt();
  await gen_ch2_avl_ll();
  await gen_ch2_avl_rr();
  await gen_ch2_avl_lr();
  await gen_ch2_avl_rl();
  await gen_ch2_avl_final();
  await gen_ch2_rbt();
  await gen_ch2_btree();
  await gen_ch2_bplustree();
  await gen_ch3_graph();
  await gen_ch3_directed();
  await gen_ch3_weighted();
  await gen_ch3_mst();
  await gen_ch3_bfs();
  await gen_ch3_dfs();
  await gen_ch3_dijkstra();
  await gen_ch4_linear_probe();
  await gen_ch4_quadratic();
  await gen_ch4_chaining();
  await gen_d01();
  await gen_d02();
  await gen_d03();
  await gen_d04();
  await gen_d05();
  await gen_d06();
  await gen_d07();
  await gen_d08();
  await gen_d09();
  await gen_d10();
  await gen_d11();
  await gen_d12();
  await gen_d13();
  await gen_d14();
  await gen_d15();
  await gen_d16();
  await gen_d17();
  await gen_d18();
  await gen_d19();
  await gen_d20();
  await gen_d21();
  await gen_d22();
  await gen_d23();
  await gen_d24();
  await gen_d25();
  await gen_d26();
  await gen_d27();
  await gen_d28();
  await gen_d29();
  await gen_d30();
  await gen_d31();
  await gen_d32();
  await gen_d33();
  await gen_d34();
  await gen_ch1_bst_del_one_child();
  await gen_ch2_avl_del_imbal();

  // ── CODE BLOCK GENERATORS ───────────────────────────────────────────────────
  async function gen_code(filename, lines){ await save(filename, codeImg(lines)); }

  await gen_code('code_tree_node.png', [
    'struct TreeNode {',
    '    int data;',
    '    struct TreeNode *left;   // pointer to left child',
    '    struct TreeNode *right;  // pointer to right child',
    '};',
  ]);

  await gen_code('code_bst_create.png', [
    'struct TreeNode* root = NULL;  // Empty BST',
    'root = insert(root, 50);       // 50 becomes root',
    'root = insert(root, 30);       // 30 goes left',
    'root = insert(root, 70);       // 70 goes right',
  ]);

  await gen_code('code_bst_insert.png', [
    'Node* insert(Node* root, int key) {',
    '   if (root == NULL)',
    '      return createNode(key);     // insert here',
    '   if (key < root->data)',
    '      root->left = insert(root->left, key);',
    '   else if (key > root->data)',
    '      root->right = insert(root->right, key);',
    '   return root;',
    '}',
  ]);

  await gen_code('code_bst_delete.png', [
    'Node* deleteNode(Node* root, int key) {',
    '   if (root == NULL) return NULL;',
    '   if (key < root->data)',
    '      root->left = deleteNode(root->left, key);',
    '   else if (key > root->data)',
    '      root->right = deleteNode(root->right, key);',
    '   else {                        // node found',
    '      if (root->left == NULL)  return root->right;',
    '      if (root->right == NULL) return root->left;',
    '      // Two children: replace with inorder successor',
    '      Node* succ = findMin(root->right);',
    '      root->data = succ->data;',
    '      root->right = deleteNode(root->right, succ->data);',
    '   }',
    '   return root;',
    '}',
  ]);

  await gen_code('code_bst_search.png', [
    'int search(Node* root, int key) {',
    '   if (root == NULL) return 0;    // Not found',
    '   if (root->data == key) return 1;  // Found',
    '   if (key < root->data)',
    '      return search(root->left, key);',
    '   else',
    '      return search(root->right, key);',
    '}',
  ]);

  await gen_code('code_preorder.png', [
    'void preorder(Node* root) {',
    '   if (root == NULL) return;',
    '   printf("%d ", root->data);   // Visit Node',
    '   preorder(root->left);        // Traverse Left',
    '   preorder(root->right);       // Traverse Right',
    '}',
  ]);

  await gen_code('code_inorder.png', [
    'void inorder(Node* root) {',
    '   if (root == NULL) return;',
    '   inorder(root->left);         // Traverse Left',
    '   printf("%d ", root->data);   // Visit Node',
    '   inorder(root->right);        // Traverse Right',
    '}',
  ]);

  await gen_code('code_postorder.png', [
    'void postorder(Node* root) {',
    '   if (root == NULL) return;',
    '   postorder(root->left);       // Traverse Left',
    '   postorder(root->right);      // Traverse Right',
    '   printf("%d ", root->data);   // Visit Node',
    '}',
  ]);

  await gen_code('code_levelorder.png', [
    'void levelOrder(Node* root) {',
    '   if (root == NULL) return;',
    '   Queue Q;',
    '   enqueue(Q, root);',
    '   while (!isEmpty(Q)) {',
    '      Node* curr = dequeue(Q);',
    '      printf("%d ", curr->data);       // Visit node',
    '      if (curr->left)  enqueue(Q, curr->left);',
    '      if (curr->right) enqueue(Q, curr->right);',
    '   }',
    '}',
  ]);

  await gen_code('code_count_leaves.png', [
    'int countLeaves(Node* root) {',
    '   if (root == NULL) return 0;',
    '   if (root->left == NULL && root->right == NULL)',
    '      return 1;                  // leaf node',
    '   return countLeaves(root->left) + countLeaves(root->right);',
    '}',
  ]);

  await gen_code('code_count_nonleaves.png', [
    'int countNonLeaves(Node* root) {',
    '   if (root == NULL) return 0;',
    '   if (root->left == NULL && root->right == NULL)',
    '      return 0;                  // leaf: skip',
    '   return 1 + countNonLeaves(root->left)',
    '            + countNonLeaves(root->right);',
    '}',
  ]);

  await gen_code('code_count_total.png', [
    'int countNodes(Node* root) {',
    '   if (root == NULL) return 0;',
    '   return 1 + countNodes(root->left)',
    '            + countNodes(root->right);',
    '}',
  ]);

  await gen_code('code_copy_tree.png', [
    'Node* copyTree(Node* root) {',
    '   if (root == NULL) return NULL;',
    '   Node* newNode = createNode(root->data);',
    '   newNode->left  = copyTree(root->left);   // copy left',
    '   newNode->right = copyTree(root->right);  // copy right',
    '   return newNode;',
    '}',
  ]);

  await gen_code('code_mirror.png', [
    'void mirror(Node* root) {',
    '   if (root == NULL) return;',
    '   // Swap left and right children',
    "   Node* temp  = root->left;",
    '   root->left  = root->right;',
    '   root->right = temp;',
    '   mirror(root->left);   // recurse left',
    '   mirror(root->right);  // recurse right',
    '}',
  ]);

  await gen_code('code_heapify.png', [
    'void maxHeapify(int arr[], int n, int i) {',
    '   int largest = i;           // assume root is largest',
    '   int left  = 2*i + 1;       // left child index',
    '   int right = 2*i + 2;       // right child index',
    '   if (left  < n && arr[left]  > arr[largest]) largest = left;',
    '   if (right < n && arr[right] > arr[largest]) largest = right;',
    '   if (largest != i) {         // root is not largest',
    '      int tmp = arr[i]; arr[i] = arr[largest]; arr[largest] = tmp;',
    '      maxHeapify(arr, n, largest);  // recurse',
    '   }',
    '}',
  ]);

  await gen_code('code_build_heap.png', [
    'void buildMaxHeap(int arr[], int n) {',
    '   // Start from last non-leaf node (index n/2-1)',
    '   for (int i = n/2 - 1; i >= 0; i--)',
    '      maxHeapify(arr, n, i);',
    '}',
  ]);

  await gen_code('code_heap_sort.png', [
    'void heapSort(int arr[], int n) {',
    '   buildMaxHeap(arr, n);          // Phase 1: build max heap',
    '   for (int i = n-1; i > 0; i--) {',
    '      // Move current max (root) to end',
    '      int tmp = arr[0]; arr[0] = arr[i]; arr[i] = tmp;',
    '      maxHeapify(arr, i, 0);      // heapify reduced heap',
    '   }',
    '}',
  ]);

  await gen_code('code_right_rotate.png', [
    'Node* rightRotate(Node* C) {',
    '   Node* B  = C->left;',
    "   Node* T2 = B->right;   // B's right subtree",
    '   B->right = C;           // C becomes right child of B',
    '   C->left  = T2;          // T2 becomes left child of C',
    '   updateHeight(C);        // update heights bottom-up',
    '   updateHeight(B);',
    '   return B;               // B is new root',
    '}',
  ]);

  await gen_code('code_left_rotate.png', [
    'Node* leftRotate(Node* A) {',
    '   Node* B  = A->right;',
    "   Node* T2 = B->left;    // B's left subtree",
    '   B->left  = A;           // A becomes left child of B',
    '   A->right = T2;          // T2 becomes right child of A',
    '   updateHeight(A);',
    '   updateHeight(B);',
    '   return B;               // B is new root',
    '}',
  ]);

  await gen_code('code_bplus_insert.png', [
    '/* B+ Tree Insert — Order m (max m-1 keys per node) */',
    'void bplus_insert(BPlusTree *T, int key) {',
    '   BPlusNode *leaf = findLeaf(T->root, key);',
    '   insertInLeaf(leaf, key);         // insert in sorted order',
    '   if (leaf->numKeys == m) {        // leaf overflow',
    '      BPlusNode *newLeaf = splitLeaf(leaf);',
    '      int upKey = newLeaf->keys[0]; // COPY key up to parent',
    '      insertInParent(leaf, upKey, newLeaf);',
    '   }',
    '}',
    'void insertInParent(BPlusNode *n, int key, BPlusNode *n2) {',
    '   if (n == root) { createNewRoot(n, key, n2); return; }',
    '   BPlusNode *p = findParent(n);',
    '   insertKey(p, key, n2);           // insert in parent',
    '   if (p->numKeys == m)             // parent overflow',
    '      splitInternal(p);             // push up, recurse',
    '}',
  ]);

  await gen_code('code_bfs.png', [
    'void BFS(int adj[V][V], int start) {',
    '   int visited[V] = {0};',
    '   int queue[V], front = 0, rear = 0;',
    '   visited[start] = 1;',
    '   queue[rear++] = start;',
    '   while (front < rear) {',
    '      int v = queue[front++];',
    '      printf("%d ", v);             // process vertex',
    '      for (int u = 0; u < V; u++)',
    '         if (adj[v][u] && !visited[u]) {',
    '            visited[u] = 1;',
    '            queue[rear++] = u;',
    '         }',
    '   }',
    '}',
  ]);

  await gen_code('code_dfs_recursive.png', [
    'void DFS(int adj[V][V], int v, int visited[]) {',
    '   visited[v] = 1;',
    '   printf("%d ", v);               // process vertex',
    '   for (int u = 0; u < V; u++)',
    '      if (adj[v][u] && !visited[u])',
    '         DFS(adj, u, visited);',
    '}',
    '// Initial call:',
    '// int visited[V]={0}; DFS(adj, start, visited);',
  ]);

  await gen_code('code_dfs_iterative.png', [
    'void DFS_iterative(int adj[V][V], int start) {',
    '   int visited[V] = {0};',
    '   int stack[V], top = -1;',
    '   stack[++top] = start;',
    '   while (top >= 0) {',
    '      int v = stack[top--];',
    '      if (!visited[v]) {',
    '         visited[v] = 1;',
    '         printf("%d ", v);',
    '         for (int u = V-1; u >= 0; u--)   // reverse for order',
    '            if (adj[v][u] && !visited[u])',
    '               stack[++top] = u;',
    '      }',
    '   }',
    '}',
  ]);

  await gen_code('code_prim.png', [
    'void prim(int graph[V][V]) {',
    '   int parent[V], key[V]; int inMST[V];',
    '   for (int i = 0; i < V; i++) {',
    '      key[i] = INT_MAX; inMST[i] = 0;',
    '   }',
    '   key[0] = 0; parent[0] = -1;     // start from vertex 0',
    '   for (int cnt = 0; cnt < V-1; cnt++) {',
    '      int u = minKey(key, inMST);   // pick min-key vertex',
    '      inMST[u] = 1;',
    '      for (int v = 0; v < V; v++)',
    '         if (graph[u][v] && !inMST[v]',
    '                         && graph[u][v] < key[v]) {',
    '            parent[v] = u;',
    '            key[v] = graph[u][v];',
    '         }',
    '   }',
    '}',
  ]);

  await gen_code('code_kruskal.png', [
    'int find(int parent[], int x) {',
    '   if (parent[x] != x)',
    '      parent[x] = find(parent, parent[x]); // path compression',
    '   return parent[x];',
    '}',
    'void kruskal(Edge edges[], int V, int E) {',
    '   sortByWeight(edges, E);           // sort edges ascending',
    '   int parent[V], rnk[V];',
    '   for (int i = 0; i < V; i++) { parent[i]=i; rnk[i]=0; }',
    '   for (int i = 0; i < E; i++) {',
    '      int u = find(parent, edges[i].src);',
    '      int v = find(parent, edges[i].dest);',
    '      if (u != v) {                  // no cycle',
    '         unionSets(parent, rnk, u, v);',
    '         printf("Edge: %d-%d\\n", edges[i].src, edges[i].dest);',
    '      }',
    '   }',
    '}',
  ]);

  await gen_code('code_dijkstra.png', [
    'void dijkstra(int graph[V][V], int src) {',
    '   int dist[V]; int visited[V];',
    '   for (int i = 0; i < V; i++) {',
    '      dist[i] = INT_MAX; visited[i] = 0;',
    '   }',
    '   dist[src] = 0;',
    '   for (int cnt = 0; cnt < V-1; cnt++) {',
    '      int u = minDist(dist, visited); // nearest unvisited',
    '      visited[u] = 1;',
    '      for (int v = 0; v < V; v++)',
    '         if (!visited[v] && graph[u][v] &&',
    '             dist[u] + graph[u][v] < dist[v])',
    '            dist[v] = dist[u] + graph[u][v]; // relax edge',
    '   }',
    '}',
  ]);

  await gen_code('code_floyd.png', [
    'void floydWarshall(int D[V][V]) {',
    '   // D[i][i]=0, D[i][j]=weight or INF if no edge',
    '   for (int k = 0; k < V; k++)     // intermediate vertex k',
    '      for (int i = 0; i < V; i++)',
    '         for (int j = 0; j < V; j++)',
    '            if (D[i][k]+D[k][j] < D[i][j])',
    '               D[i][j] = D[i][k] + D[k][j];',
    '}',
  ]);

  await gen_code('code_find_components.png', [
    'void findComponents(int adj[V][V]) {',
    '   int visited[V] = {0};',
    '   int comp = 0;',
    '   for (int v = 0; v < V; v++) {',
    '      if (!visited[v]) {',
    '         comp++;',
    '         printf("Component %d: ", comp);',
    '         DFS(adj, v, visited);      // prints all nodes',
    '         printf("\\n");',
    '      }',
    '   }',
    '   printf("Total components: %d\\n", comp);',
    '}',
  ]);

  await gen_code('code_cycle_undirected.png', [
    'int hasCycle_undirected(int adj[V][V]) {',
    '   int visited[V]={0}, parent[V];',
    '   int queue[V], front=0, rear=0;',
    '   for (int i = 0; i < V; i++) parent[i]=-1;',
    '   for (int s = 0; s < V; s++) {',
    '      if (visited[s]) continue;',
    '      visited[s]=1; queue[rear++]=s;',
    '      while (front < rear) {',
    '         int v = queue[front++];',
    '         for (int u = 0; u < V; u++)',
    '            if (adj[v][u]) {',
    '               if (!visited[u])',
    '               { visited[u]=1; parent[u]=v; queue[rear++]=u; }',
    '               else if (u != parent[v]) return 1; // cycle!',
    '            }',
    '      }',
    '   }',
    '   return 0;',
    '}',
  ]);

  await gen_code('code_cycle_directed.png', [
    '// color: 0=WHITE(unvisited), 1=GRAY(in stack), 2=BLACK(done)',
    'int dfsColor(int adj[V][V], int v, int color[]) {',
    '   color[v] = 1;                    // mark in-progress',
    '   for (int u = 0; u < V; u++)',
    '      if (adj[v][u]) {',
    '         if (color[u] == 1) return 1;  // back edge = cycle',
    '         if (color[u] == 0 && dfsColor(adj,u,color))',
    '            return 1;',
    '      }',
    '   color[v] = 2;                    // mark done',
    '   return 0;',
    '}',
    'int hasCycle_directed(int adj[V][V]) {',
    '   int color[V] = {0};',
    '   for (int v = 0; v < V; v++)',
    '      if (color[v]==0 && dfsColor(adj,v,color)) return 1;',
    '   return 0;',
    '}',
  ]);

  await gen_code('code_bellman_ford.png', [
    'void bellmanFord(Edge edges[], int V, int E, int src) {',
    '   int dist[V];',
    '   for (int i = 0; i < V; i++) dist[i] = INT_MAX;',
    '   dist[src] = 0;',
    '   for (int i = 1; i <= V-1; i++) {    // V-1 relaxations',
    '      for (int j = 0; j < E; j++) {',
    '         int u = edges[j].src;',
    '         int v = edges[j].dest;',
    '         int w = edges[j].weight;',
    '         if (dist[u] != INT_MAX && dist[u]+w < dist[v])',
    '            dist[v] = dist[u] + w;',
    '      }',
    '   }',
    '   // Detect negative-weight cycle',
    '   for (int j = 0; j < E; j++)',
    '      if (dist[edges[j].src]+edges[j].weight < dist[edges[j].dest])',
    '         printf("Negative weight cycle detected!\\n");',
    '}',
  ]);

  await gen_code('code_is_bipartite.png', [
    'int isBipartite(int adj[V][V]) {',
    '   int color[V];',
    '   for (int i = 0; i < V; i++) color[i] = -1;',
    '   int queue[V], front=0, rear=0;',
    '   color[0] = 0; queue[rear++] = 0;   // start BFS',
    '   while (front < rear) {',
    '      int v = queue[front++];',
    '      for (int u = 0; u < V; u++)',
    '         if (adj[v][u]) {',
    '            if (color[u] == -1) {',
    '               color[u] = 1 - color[v];  // alternate 0/1',
    '               queue[rear++] = u;',
    '            } else if (color[u] == color[v])',
    '               return 0;   // same color = NOT bipartite',
    '         }',
    '   }',
    '   return 1;',
    '}',
  ]);

  await gen_code('code_bellman_extra.png', [
    'void bellmanFord(Edge edges[], int V, int E, int src) {',
    '   int dist[V];',
    '   for (int i=0; i<V; i++) dist[i] = INT_MAX;',
    '   dist[src] = 0;',
    '   for (int i=1; i<=V-1; i++)          // V-1 passes',
    '      for (int j=0; j<E; j++) {',
    '         int u=edges[j].src, v=edges[j].dest, w=edges[j].weight;',
    '         if (dist[u]!=INT_MAX && dist[u]+w < dist[v])',
    '            dist[v] = dist[u] + w;',
    '      }',
    '   // Check for negative weight cycles',
    '   for (int j=0; j<E; j++)',
    '      if (dist[edges[j].src]+edges[j].weight < dist[edges[j].dest])',
    '         printf("Negative cycle exists!\\n");',
    '}',
  ]);

  await gen_code('code_cycle_und_extra.png', [
    'int hasCycle_undirected(int adj[V][V]) {',
    '   int visited[V]={0}, parent[V];',
    '   for (int i=0; i<V; i++) parent[i]=-1;',
    '   // BFS from each unvisited vertex',
    '   for (int s=0; s<V; s++) {',
    '      if (visited[s]) continue;',
    '      int q[V], f=0, r=0;',
    '      visited[s]=1; q[r++]=s;',
    '      while (f<r) {',
    '         int v=q[f++];',
    '         for (int u=0; u<V; u++)',
    '            if (adj[v][u]) {',
    '               if (!visited[u])',
    '               { visited[u]=1; parent[u]=v; q[r++]=u; }',
    '               else if (u!=parent[v]) return 1;',
    '            }',
    '      }',
    '   }',
    '   return 0;    // no cycle found',
    '}',
  ]);

  await gen_code('code_cycle_dir_extra.png', [
    '// 3-color DFS for directed graph cycle detection',
    '// WHITE=0 (unvisited), GRAY=1 (in stack), BLACK=2 (done)',
    'int dfsColor(int adj[V][V], int v, int color[]) {',
    '   color[v] = 1;                     // mark GRAY',
    '   for (int u=0; u<V; u++)',
    '      if (adj[v][u]) {',
    '         if (color[u]==1) return 1;  // back edge = cycle',
    '         if (color[u]==0 && dfsColor(adj,u,color)) return 1;',
    '      }',
    '   color[v] = 2; return 0;           // mark BLACK',
    '}',
    'int hasCycle_directed(int adj[V][V]) {',
    '   int color[V]={0};',
    '   for (int v=0; v<V; v++)',
    '      if (color[v]==0 && dfsColor(adj,v,color)) return 1;',
    '   return 0;',
    '}',
  ]);

  await gen_code('code_tarjan_scc.png', [
    'int disc[V], low[V], onStack[V], timer_cnt=0;',
    'int stack_arr[V], top_idx=-1;',
    '',
    'void tarjanDFS(int v) {',
    '   disc[v] = low[v] = ++timer_cnt;',
    '   stack_arr[++top_idx]=v; onStack[v]=1;',
    '   for (int u=0; u<V; u++) {',
    '      if (!adj[v][u]) continue;',
    '      if (disc[u]==-1) {             // not visited',
    '         tarjanDFS(u);',
    '         low[v] = (low[v]<low[u]) ? low[v] : low[u];',
    '      } else if (onStack[u])',
    '         low[v] = (low[v]<disc[u]) ? low[v] : disc[u];',
    '   }',
    '   if (low[v]==disc[v]) {            // v is SCC root',
    '      printf("SCC: ");',
    '      while (stack_arr[top_idx]!=v)',
    '         printf("%d ", stack_arr[top_idx--]);',
    '      printf("%d\\n", stack_arr[top_idx--]);',
    '   }',
    '}',
  ]);

  await gen_code('code_bipartite_extra.png', [
    'int isBipartite(int adj[V][V]) {',
    '   int color[V];',
    '   for (int i=0; i<V; i++) color[i]=-1; // -1 = uncolored',
    '   int queue[V], f=0, r=0;',
    '   color[0]=0; queue[r++]=0;',
    '   while (f<r) {',
    '      int v=queue[f++];',
    '      for (int u=0; u<V; u++)',
    '         if (adj[v][u]) {',
    '            if (color[u]==-1) {',
    '               color[u] = 1-color[v];  // alternate colors',
    '               queue[r++]=u;',
    '            } else if (color[u]==color[v])',
    '               return 0;  // NOT bipartite',
    '         }',
    '   }',
    '   return 1;',
    '}',
  ]);

  await gen_code('code_floyd_extra.png', [
    'void floydWarshall(int D[V][V]) {',
    '   /* Initialize: D[i][i]=0, D[i][j]=weight or INF */',
    '   for (int k=0; k<V; k++)          // k = intermediate',
    '      for (int i=0; i<V; i++)',
    '         for (int j=0; j<V; j++)',
    '            if (D[i][k]+D[k][j] < D[i][j])',
    '               D[i][j] = D[i][k] + D[k][j];',
    '}',
    '/* Time Complexity: O(V^3)',
    '   Space Complexity: O(V^2)',
    '   Handles negative weights (not negative cycles) */',
  ]);

  console.log('\n✅ All diagrams generated in /tmp/ds_diagrams/');
  // Write dimension manifest so notes script can preserve aspect ratios
  require('fs').writeFileSync('/tmp/ds_diagrams/dims.json', JSON.stringify(DIMS, null, 2));
  console.log('✅ dims.json written');
})();
