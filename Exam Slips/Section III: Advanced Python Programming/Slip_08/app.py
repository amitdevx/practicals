from flask import Flask, render_template

app = Flask(__name__)

@app.route('/')
def home():
    courses = [
        "B.Sc. Computer Science",
        "M.Sc. Data Science",
        "B.A. Economics",
        "B.Voc. Media & Communication"
    ]
    return render_template('index.html', courses=courses)

if __name__ == "__main__":
    app.run(debug=True)
