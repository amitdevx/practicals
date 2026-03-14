from flask import Flask, render_template_string

app = Flask(__name__)

@app.route('/')
def index():
    html = """
    <html>
    <style>
        h1 { text-align: center; }
        .courses { padding: 20px; }
        ul { font-size: 18px; }
    </style>
    <h1>Savitribai Phule Pune University</h1>
    <div class="courses">
        <h2>Available Courses:</h2>
        <ul>
            <li>B.Tech - Computer Science</li>
            <li>B.Tech - Electronics</li>
            <li>M.Tech - Data Science</li>
            <li>B.Sc - Physics</li>
            <li>B.Sc - Chemistry</li>
        </ul>
        <p><strong>Established:</strong> 1949</p>
        <p><strong>Location:</strong> Pune, Maharashtra</p>
    </div>
    </html>
    """
    return render_template_string(html)

if __name__ == '__main__':
    app.run(debug=True)
