from flask import Flask, render_template_string
app = Flask(__name__)
template = '''
<html>
<h1>Central Library</h1>
<table border='1'>
  <tr><th>Title</th><th>Author</th></tr>
  <tr><td>Python Crash Course</td><td>Eric Matthes</td></tr>
  <tr><td>Clean Code</td><td>Robert C. Martin</td></tr>
  <tr><td>Design Patterns</td><td>Gang of Four</td></tr>
</table>
<p><b><font color='blue'>"A reader lives a thousand lives before he dies." - George R.R. Martin</font></b></p>
</html>
'''
@app.route('/')
def library():
    return render_template_string(template)
if __name__ == '__main__':
    app.run(debug=True)
