-- Assignment 5: Flask Web Application Database Setup
-- Run this file with: psql -U postgres -f setup.sql

-- Create databases
CREATE DATABASE taskdb;
CREATE DATABASE contactdb;
CREATE DATABASE studentdb;
CREATE DATABASE userdb;
CREATE DATABASE productdb;
CREATE DATABASE attendancedb;

-- Set_A Q2: Task Manager
\c taskdb
CREATE TABLE tasks (
    id SERIAL PRIMARY KEY,
    task_name VARCHAR(200)
);

-- Set_A Q3: Contact Manager
\c contactdb
CREATE TABLE contacts (
    id SERIAL PRIMARY KEY,
    name VARCHAR(100),
    phone VARCHAR(15)
);

-- Set_A Q4: Student Registration
\c studentdb
CREATE TABLE students (
    id SERIAL PRIMARY KEY,
    name VARCHAR(100),
    roll VARCHAR(20),
    dept VARCHAR(50)
);

-- Set_B Q1: Login System
\c userdb
CREATE TABLE users (
    id SERIAL PRIMARY KEY,
    username VARCHAR(50),
    password VARCHAR(50)
);

-- Set_B Q2: Product Manager
\c productdb
CREATE TABLE products (
    id SERIAL PRIMARY KEY,
    name VARCHAR(100),
    price DECIMAL,
    qty INT
);

-- Set_B Q3: Attendance Tracker
\c attendancedb
CREATE TABLE attendance (
    id SERIAL PRIMARY KEY,
    name VARCHAR(100),
    status VARCHAR(10)
);
