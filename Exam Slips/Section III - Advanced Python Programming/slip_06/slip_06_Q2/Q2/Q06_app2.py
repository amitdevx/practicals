from flask import Flask, render_template_string
app = Flask(__name__)
template = '''
<html>
<style>
  h1 { text-align: center; }
  .skills { overflow: auto; height: 100px; border: 1px solid; padding: 10px; }
</style>
<h1>My Portfolio - Amit Divekar</h1>
<h2>Qualifications</h2>
<ul>
  <li>B.Tech - Computer Science</li>
  <li>Advanced Python Programming Certification</li>
</ul>
<h2>Skills</h2>
<div class='skills'>
  <p>Python, Flask, Django, HTML, CSS, JavaScript, SQL, Data Analysis, Web Development, Machine Learning</p>
</div>
</html>
'''
@app.route('/')
def portfolio():
    return render_template_string(template)
if __name__ == '__main__':
    app.run(debug=True)
