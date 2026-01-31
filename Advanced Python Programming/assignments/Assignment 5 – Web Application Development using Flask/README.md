# Assignment 5: Flask Web Application Setup Guide

## Prerequisites

- Python 3.x with virtual environment
- PostgreSQL installed and running
- Flask and psycopg2 installed

## Quick Start

### 1. Activate Virtual Environment

```bash
source /home/amitdevx/jupyter-env/bin/activate
```

### 2. Database Setup

Run the SQL setup file to create all databases and tables:

```bash
psql -U postgres -f setup.sql
```

Or manually create each database:

```sql
-- Connect to PostgreSQL
psql -U postgres

-- Create databases
CREATE DATABASE taskdb;
CREATE DATABASE contactdb;
CREATE DATABASE studentdb;
CREATE DATABASE userdb;
CREATE DATABASE productdb;
CREATE DATABASE attendancedb;
```

Then create tables (see setup.sql for full SQL).

### 3. Update Database Password

If your PostgreSQL password is different from `postgres`, update it in each `app.py`:

```python
def get_db_connection():
    conn = psycopg2.connect(
        host="localhost",
        database="dbname",
        user="postgres",
        password="YOUR_PASSWORD"  # Change this
    )
    return conn
```

---

## Running the Apps

### Set A

| Q# | App | Port | Command |
|----|-----|------|---------|
| Q1 | College Page | 5001 | `cd Set_A/Q1 && python app.py` |
| Q2 | Task Manager | 5002 | `cd Set_A/Q2 && python app.py` |
| Q3 | Contact Manager | 5003 | `cd Set_A/Q3 && python app.py` |
| Q4 | Student Registration | 5004 | `cd Set_A/Q4 && python app.py` |

### Set B

| Q# | App | Port | Command |
|----|-----|------|---------|
| Q1 | Login System | 5005 | `cd Set_B/Q1 && python app.py` |
| Q2 | Product Manager | 5006 | `cd Set_B/Q2 && python app.py` |
| Q3 | Attendance Tracker | 5007 | `cd Set_B/Q3 && python app.py` |

---

## App Details

### Set_A/Q1 - College Information Page
- **Port:** 5001
- **Database:** None (static page)
- **URL:** http://localhost:5001
- **Note:** Add `college.jpg` to `Set_A/Q1/static/` folder

### Set_A/Q2 - Task Manager
- **Port:** 5002
- **Database:** taskdb
- **Table:** tasks (id, task_name)
- **URL:** http://localhost:5002

### Set_A/Q3 - Contact Manager
- **Port:** 5003
- **Database:** contactdb
- **Table:** contacts (id, name, phone)
- **URLs:** 
  - http://localhost:5003 (form)
  - http://localhost:5003/contacts (list)

### Set_A/Q4 - Student Registration
- **Port:** 5004
- **Database:** studentdb
- **Table:** students (id, name, roll, dept)
- **URLs:**
  - http://localhost:5004 (form)
  - http://localhost:5004/students (list)

### Set_B/Q1 - Login System
- **Port:** 5005
- **Database:** userdb
- **Table:** users (id, username, password)
- **URLs:**
  - http://localhost:5005/register
  - http://localhost:5005/login
  - http://localhost:5005/logout

### Set_B/Q2 - Product Manager
- **Port:** 5006
- **Database:** productdb
- **Table:** products (id, name, price, qty)
- **URL:** http://localhost:5006

### Set_B/Q3 - Attendance Tracker
- **Port:** 5007
- **Database:** attendancedb
- **Table:** attendance (id, name, status)
- **URL:** http://localhost:5007

---

## Troubleshooting

### Database Connection Error
```
psycopg2.OperationalError: FATAL: password authentication failed
```
**Solution:** Update the password in `app.py` to match your PostgreSQL password.

### Port Already in Use
```
OSError: [Errno 98] Address already in use
```
**Solution:** Kill the process using the port or change the port in `app.py`:
```bash
# Find process using port
lsof -i :5001
# Kill it
kill <PID>
```

### Database Does Not Exist
```
psycopg2.OperationalError: FATAL: database "taskdb" does not exist
```
**Solution:** Run `setup.sql` or create the database manually:
```bash
psql -U postgres -c "CREATE DATABASE taskdb;"
```

---

## File Structure

```
Assignment 5 – Web Application Development using Flask/
├── README.md
├── setup.sql
├── Set_A/
│   ├── Q1/
│   │   ├── app.py
│   │   ├── static/
│   │   └── templates/
│   │       └── index.html
│   ├── Q2/
│   │   ├── app.py
│   │   └── templates/
│   │       └── index.html
│   ├── Q3/
│   │   ├── app.py
│   │   └── templates/
│   │       ├── form.html
│   │       └── contacts.html
│   └── Q4/
│       ├── app.py
│       └── templates/
│           ├── register.html
│           └── students.html
└── Set_B/
    ├── Q1/
    │   ├── app.py
    │   └── templates/
    │       ├── login.html
    │       └── register.html
    ├── Q2/
    │   ├── app.py
    │   └── templates/
    │       └── index.html
    └── Q3/
        ├── app.py
        └── templates/
            └── index.html
```
