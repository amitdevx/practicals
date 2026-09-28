// Student Report using Template Literals
const studentName = "Aarav Sharma";
const rollNo = 101;
const marks = {
    OperatingSystems: 88,
    CoreJava: 92,
    DataScience: 85
};

const total = marks.OperatingSystems + marks.CoreJava + marks.DataScience;
const percentage = (total / 300) * 100;
const result = percentage >= 40 ? "PASS" : "FAIL";

const report = `
=============================================
           STUDENT GRADE REPORT
=============================================
Student Name : ${studentName}
Roll Number  : ${rollNo}
---------------------------------------------
Subject                  Marks (Out of 100)
---------------------------------------------
Operating Systems        : ${marks.OperatingSystems}
Core Java & Web Tech     : ${marks.CoreJava}
Data Science & Analytics : ${marks.DataScience}
---------------------------------------------
Total Marks  : ${total} / 300
Percentage   : ${percentage.toFixed(2)}%
Final Status : ${result}
=============================================
`;

console.log(report);
