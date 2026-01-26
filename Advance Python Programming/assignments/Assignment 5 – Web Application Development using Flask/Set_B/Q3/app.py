from flask import Flask, render_template, request, redirect
import psycopg2

app = Flask(__name__)

def get_db_connection():
    conn = psycopg2.connect(
        host="localhost",
        database="attendancedb",
        user="postgres",
        password="amit123"
    )
    return conn

@app.route("/", methods=["GET", "POST"])
def home():
    conn = get_db_connection()
    cur = conn.cursor()
    
    if request.method == "POST":
        name = request.form["name"]
        status = request.form["status"]
        cur.execute("INSERT INTO attendance (name, status) VALUES (%s, %s)", (name, status))
        conn.commit()
    
    cur.execute("SELECT * FROM attendance")
    records = cur.fetchall()
    
    cur.execute("SELECT COUNT(*) FROM attendance WHERE status='Present'")
    present = cur.fetchone()[0]
    
    cur.execute("SELECT COUNT(*) FROM attendance WHERE status='Absent'")
    absent = cur.fetchone()[0]
    
    cur.close()
    conn.close()
    
    return render_template("index.html", records=records, present=present, absent=absent)

if __name__ == "__main__":
    app.run(debug=True, port=5007)

# SQL: CREATE TABLE attendance (id SERIAL PRIMARY KEY, name VARCHAR(100), status VARCHAR(10));
