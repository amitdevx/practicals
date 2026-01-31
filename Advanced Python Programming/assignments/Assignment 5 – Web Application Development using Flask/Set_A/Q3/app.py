from flask import Flask, render_template, request, redirect
import psycopg2
import os

app = Flask(__name__)

def get_db_connection():
    conn = psycopg2.connect(
        host=os.environ.get("DB_HOST", "localhost"),
        database="contactdb",
        user=os.environ.get("DB_USER", "postgres"),
        password=os.environ.get("DB_PASSWORD", "amit123")
    )
    return conn

@app.route("/")
def home():
    return render_template("form.html")

@app.route("/add", methods=["POST"])
def add_contact():
    name = request.form["name"]
    phone = request.form["phone"]
    
    conn = get_db_connection()
    cur = conn.cursor()
    cur.execute("INSERT INTO contacts (name, phone) VALUES (%s, %s)", (name, phone))
    conn.commit()
    cur.close()
    conn.close()
    
    return redirect("/contacts")

@app.route("/contacts")
def contacts():
    conn = get_db_connection()
    cur = conn.cursor()
    cur.execute("SELECT * FROM contacts")
    contacts = cur.fetchall()
    cur.close()
    conn.close()
    
    return render_template("contacts.html", contacts=contacts)

if __name__ == "__main__":
    app.run(debug=True, port=5003)

# SQL: CREATE TABLE contacts (id SERIAL PRIMARY KEY, name VARCHAR(100), phone VARCHAR(15));
