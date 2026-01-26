from flask import Flask, render_template, request, redirect
import psycopg2

app = Flask(__name__)

def get_db_connection():
    conn = psycopg2.connect(
        host="localhost",
        database="studentdb",
        user="postgres",
        password="amit123"
    )
    return conn

@app.route("/")
def home():
    return render_template("register.html")

@app.route("/register", methods=["POST"])
def register():
    name = request.form["name"]
    roll = request.form["roll"]
    dept = request.form["dept"]
    
    conn = get_db_connection()
    cur = conn.cursor()
    cur.execute("INSERT INTO students (name, roll, dept) VALUES (%s, %s, %s)", (name, roll, dept))
    conn.commit()
    cur.close()
    conn.close()
    
    return redirect("/students")

@app.route("/students")
def students():
    conn = get_db_connection()
    cur = conn.cursor()
    cur.execute("SELECT * FROM students")
    students = cur.fetchall()
    cur.close()
    conn.close()
    
    return render_template("students.html", students=students)

if __name__ == "__main__":
    app.run(debug=True, port=5004)

# SQL: CREATE TABLE students (id SERIAL PRIMARY KEY, name VARCHAR(100), roll VARCHAR(20), dept VARCHAR(50));
