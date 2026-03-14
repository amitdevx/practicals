from flask import Flask, render_template_string
from pathlib import Path

app = Flask(__name__)

@app.route('/')
def index():
    slip_dir = Path(__file__).resolve().parent
    file_path = slip_dir / "sample_notes.txt"
    file_path.write_text("""Sem IV Advanced Python practicals.
Focus on pandas, flask, and regex modules.
Practice every day.
""", encoding="utf-8")
    
    with file_path.open("r", encoding="utf-8") as handle:
        content = handle.read()
    
    characters = len(content)
    words = len(content.split())
    lines = len(content.splitlines())
    
    html = f"""
    <html>
    <h1>File Analysis</h1>
    <pre>
    File: sample_notes.txt
    Characters: {characters}
    Words: {words}
    Lines: {lines}
    
    Content:
    {content}
    </pre>
    </html>
    """
    return render_template_string(html)

if __name__ == '__main__':
    app.run(debug=True)
