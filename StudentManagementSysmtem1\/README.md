# Student Management System

## 1. Project Overview

The Student Management System is a simple database-based application developed using C++ and SQLite.

It helps users manage student records efficiently. Users can add, view, search, update and delete student information through a menu-driven interface.

## 2. Objectives

- To manage student records digitally.
- To store student information permanently in a database.
- To perform basic database operations using SQL.
- To understand database connectivity with C++.
- To implement CRUD operations.

## 3. Technologies Used

- **Programming Language:** C++
- **Database:** SQLite
- **Database Language:** SQL
- **Code Editor:** Visual Studio Code

## 4. Features

1. **Add Student:** Add new student records.
2. **Display Students:** View all stored student records.
3. **Search Student:** Search for a student using roll number.
4. **Update Student:** Modify existing student details.
5. **Delete Student:** Remove a particular student's record.
6. **Exit:** Close the application.

## 5. Database Structure

Database Name: `students.db`

Table Name: `Students`

| Column | Data Type | Description |
|---|---|---|
| RollNo | INTEGER | Student roll number (Primary Key) |
| Name | TEXT | Student name |
| Age | INTEGER | Student age |
| Course | TEXT | Student course |

## 6. Project Structure

```text
StudentManagementSystem/
│
├── main.cpp
├── students.db
└── README.md
```

## 7. How to Compile and Run

### Step 1: Open the project folder in VS Code.

### Step 2: Open the terminal.

### Step 3: Compile the program.

```bash
clang++ main.cpp -o main -lsqlite3
```

### Step 4: Run the application.

```bash
./main
```

## 8. CRUD Operations

The project implements four basic database operations:

- **Create:** Insert new student records.
- **Read:** Retrieve and display student records.
- **Update:** Modify existing student information.
- **Delete:** Remove student records from the database.

## 9. Conclusion

The Student Management System demonstrates how C++ can be connected with an SQLite database to manage student information.

Through this project, we learned about C++ functions, SQL queries, database connectivity, prepared statements and CRUD operations.

The project provides a simple and effective way to manage student records.