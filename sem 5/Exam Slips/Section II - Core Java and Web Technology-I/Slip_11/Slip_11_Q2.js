// Total and Average Marks using Arrow Functions and Template Literals
const calculateScore = (m1, m2, m3) => {
    const total = m1 + m2 + m3;
    const avg = total / 3;
    return { total, avg };
};

const sub1 = 78, sub2 = 85, sub3 = 90;
const { total, avg } = calculateScore(sub1, sub2, sub3);

console.log(`
Subject 1 Marks : ${sub1}
Subject 2 Marks : ${sub2}
Subject 3 Marks : ${sub3}
-------------------------
Total Marks     : ${total}
Average Marks   : ${avg.toFixed(2)}
`);
