from flask import Flask, render_template

app = Flask(__name__)

@app.route('/')
def home():
    courses = [
        "B.Sc. Computer Science",
        "B.Sc. Information Technology",
        "M.Sc. Data Science",
        "B.A. Economics",
        "B.Com. Accounting & Finance"
    ]
    return render_template('index.html', courses=courses)

if __name__ == "__main__":
    app.run(debug=True)
