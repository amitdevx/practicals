from flask import Flask, render_template_string, request, redirect, url_for
from sqlalchemy import Column, Integer, MetaData, String, Table, create_engine, select
import os

database_url = os.environ.get("DATABASE_URL", "sqlite+pysqlite:///tasks_demo.db")
engine = create_engine(database_url, future=True)
metadata = MetaData()
tasks_table = Table(
    "tasks",
    metadata,
    Column("id", Integer, primary_key=True, autoincrement=True),
    Column("task_name", String, nullable=False),
)
metadata.create_all(engine)

app = Flask(__name__)

TEMPLATE = """
<!doctype html>
<title>Task Manager</title>
<h1>Task Manager</h1>
<form method="post">
  <label for="task_name">Task:</label>
  <input type="text" id="task_name" name="task_name" required>
  <button type="submit">Add Task</button>
</form>
<ul>
{% for task in tasks %}
  <li>{{ task.task_name }}</li>
{% else %}
  <li>No tasks yet.</li>
{% endfor %}
</ul>
<p>Connected to: {{ database_url }}</p>
"""

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        task_name = request.form.get("task_name", "").strip()
        if task_name:
            with engine.begin() as connection:
                connection.execute(tasks_table.insert().values(task_name=task_name))
        return redirect(url_for("index"))

    with engine.connect() as connection:
        rows = connection.execute(
            select(tasks_table.c.id, tasks_table.c.task_name).order_by(tasks_table.c.id)
        ).mappings().all()
    return render_template_string(TEMPLATE, tasks=rows, database_url=database_url)

if __name__ == "__main__":
    app.run(debug=True, port=5001)
