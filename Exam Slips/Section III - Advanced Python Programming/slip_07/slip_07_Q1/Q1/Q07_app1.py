from flask import Flask, render_template

app = Flask(__name__)

@app.route('/')
def home():
    books = [
        {'title': 'The Great Gatsby', 'author': 'F. Scott Fitzgerald'},
        {'title': 'To Kill a Mockingbird', 'author': 'Harper Lee'},
        {'title': '1984', 'author': 'George Orwell'},
        {'title': 'Pride and Prejudice', 'author': 'Jane Austen'}
    ]
    return render_template('index.html', books=books)

if __name__ == "__main__":
    app.run(debug=True)
