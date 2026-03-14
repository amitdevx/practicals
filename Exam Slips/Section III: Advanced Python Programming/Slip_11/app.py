import sqlite3
from flask import Flask, render_template, request, redirect, url_for

def init_db():
    conn = sqlite3.connect('tasks.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS tasks (id INTEGER PRIMARY KEY, name TEXT)''')
    conn.commit()
    conn.close()

app = Flask(__name__)
init_db()

@app.route('/')
def index():
    conn = sqlite3.connect('tasks.db')
    c = conn.cursor()
    c.execute("SELECT * FROM tasks")
    tasks = c.fetchall()
    conn.close()
    return render_template('index.html', tasks=tasks)

@app.route('/add', methods=['POST'])
def add_task():
    task_name = request.form['task_name']
    conn = sqlite3.connect('tasks.db')
    c = conn.cursor()
    c.execute("INSERT INTO tasks (name) VALUES (?)", (task_name,))
    conn.commit()
    conn.close()
    return redirect(url_for('index'))

if __name__ == "__main__":
    app.run(debug=True)
