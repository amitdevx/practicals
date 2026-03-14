from flask import Flask, render_template_string

app = Flask(__name__)

LIBRARY_NAME = "Visionary Science Library"
BOOKS = [
    {"title": "Clean Code", "author": "Robert C. Martin"},
    {"title": "Fluent Python", "author": "Luciano Ramalho"},
    {"title": "Python Tricks", "author": "Dan Bader"},
]

TEMPLATE = """
<!doctype html>
<title>{{ library }}</title>
<h1>{{ library }}</h1>
<table border=1 cellpadding=6>
  <tr><th>Title</th><th>Author</th></tr>
  {% for book in books %}
  <tr><td>{{ book.title }}</td><td>{{ book.author }}</td></tr>
  {% endfor %}
</table>
<p><strong style="color: blue;">"A reader lives a thousand lives before he dies."</strong></p>
"""

@app.route("/")
def home():
    return render_template_string(TEMPLATE, library=LIBRARY_NAME, books=BOOKS)

if __name__ == "__main__":
    app.run(debug=True, port=5002)
