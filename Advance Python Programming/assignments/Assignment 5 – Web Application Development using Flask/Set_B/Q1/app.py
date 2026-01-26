from flask import Flask, render_template, request, redirect, session
import psycopg2

app = Flask(__name__)
app.secret_key = "secretkey123"

def get_db_connection():
    conn = psycopg2.connect(
        host="localhost",
        database="userdb",
        user="postgres",
        password="amit123"
    )
    return conn

@app.route("/")
def home():
    if "user" in session:
        return f"<h1>Welcome {session['user']}!</h1><a href='/logout'>Logout</a>"
    return redirect("/login")

@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        username = request.form["username"]
        password = request.form["password"]
        
        conn = get_db_connection()
        cur = conn.cursor()
        cur.execute("INSERT INTO users (username, password) VALUES (%s, %s)", (username, password))
        conn.commit()
        cur.close()
        conn.close()
        
        return redirect("/login")
    
    return render_template("register.html")

@app.route("/login", methods=["GET", "POST"])
def login():
    if request.method == "POST":
        username = request.form["username"]
        password = request.form["password"]
        
        conn = get_db_connection()
        cur = conn.cursor()
        cur.execute("SELECT * FROM users WHERE username=%s AND password=%s", (username, password))
        user = cur.fetchone()
        cur.close()
        conn.close()
        
        if user:
            session["user"] = username
            return redirect("/")
        else:
            return "Invalid credentials! <a href='/login'>Try again</a>"
    
    return render_template("login.html")

@app.route("/logout")
def logout():
    session.pop("user", None)
    return redirect("/login")

if __name__ == "__main__":
    app.run(debug=True, port=5005)

# SQL: CREATE TABLE users (id SERIAL PRIMARY KEY, username VARCHAR(50), password VARCHAR(50));
