from flask import Flask, render_template_string
app = Flask(__name__)
template = '''
<html>
<style>h1 { text-align: center; }</style>
<h1>Savitribai Phule Pune University</h1>
<h2>Courses Offered:</h2>
<ul>
  <li>B.Tech - Computer Science</li>
  <li>B.Tech - Electronics</li>
  <li>M.Tech - Data Science</li>
  <li>B.Sc - Physics</li>
  <li>B.Sc - Chemistry</li>
</ul>
<img src='https://via.placeholder.com/300' alt='College'>
</html>
'''
@app.route('/')
def college():
    return render_template_string(template)
if __name__ == '__main__':
    app.run(debug=True)
