from flask import Flask, render_template, request, redirect
import psycopg2

app = Flask(__name__)

def get_db_connection():
    conn = psycopg2.connect(
        host="localhost",
        database="taskdb",
        user="postgres",
        password="amit123"
    )
    return conn

@app.route("/", methods=["GET", "POST"])
def tasks():
    conn = get_db_connection()
    cur = conn.cursor()
    
    if request.method == "POST":
        task_name = request.form["task_name"]
        cur.execute("INSERT INTO tasks (task_name) VALUES (%s)", (task_name,))
        conn.commit()
    
    cur.execute("SELECT * FROM tasks")
    tasks = cur.fetchall()
    cur.close()
    conn.close()
    
    return render_template("index.html", tasks=tasks)

if __name__ == "__main__":
    app.run(debug=True, port=5002)

# SQL to create table:
# CREATE TABLE tasks (id SERIAL PRIMARY KEY, task_name VARCHAR(200));
