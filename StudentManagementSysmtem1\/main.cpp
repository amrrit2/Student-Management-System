
#include <iostream>
#include <string>
#include <sqlite3.h>
using namespace std;

// Function to add a student
void addStudent(sqlite3* DB) {

    int roll, age;
    string name, course;

    cout << "\nEnter Roll Number: ";
    cin >> roll;
    cin.ignore();

    cout << "Enter Student Name: ";
    getline(cin, name);

    cout << "Enter Age: ";
    cin >> age;
    cin.ignore();

    cout << "Enter Course: ";
    getline(cin, course);

    string sql = "INSERT INTO Students "
                 "(RollNo, Name, Age, Course) VALUES (?, ?, ?, ?);";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL) != SQLITE_OK) {
        cout << "Error preparing query!\n";
        return;
    }

    sqlite3_bind_int(stmt, 1, roll);
    sqlite3_bind_text(stmt, 2, name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, age);
    sqlite3_bind_text(stmt, 4, course.c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) == SQLITE_DONE) {
        cout << "\nStudent added successfully!\n";
    }
    else {
        cout << "\nError! Roll number may already exist.\n";
    }

    sqlite3_finalize(stmt);
}

// Function to display all students
void displayStudents(sqlite3* DB) {

    string sql = "SELECT * FROM Students ORDER BY RollNo;";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL) != SQLITE_OK) {
        cout << "Error retrieving records!\n";
        return;
    }

    cout << "\n========== STUDENT RECORDS ==========\n\n";

    cout << "Roll No.\tName\t\tAge\tCourse\n";
    cout << "-----------------------------------------------\n";

    bool found = false;

    while (sqlite3_step(stmt) == SQLITE_ROW) {

        found = true;

        cout << sqlite3_column_int(stmt, 0) << "\t\t"
             << sqlite3_column_text(stmt, 1) << "\t"
             << sqlite3_column_int(stmt, 2) << "\t"
             << sqlite3_column_text(stmt, 3) << endl;
    }

    if (!found) {
        cout << "No student records found!\n";
    }

    sqlite3_finalize(stmt);
}

// Function to search for a student
void searchStudent(sqlite3* DB) {

    int roll;

    cout << "\nEnter Roll Number to Search: ";
    cin >> roll;

    string sql = "SELECT * FROM Students WHERE RollNo = ?;";

    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);

    sqlite3_bind_int(stmt, 1, roll);

    if (sqlite3_step(stmt) == SQLITE_ROW) {

        cout << "\nStudent Found!\n";

        cout << "Roll Number: " << sqlite3_column_int(stmt, 0) << endl;
        cout << "Name: " << sqlite3_column_text(stmt, 1) << endl;
        cout << "Age: " << sqlite3_column_int(stmt, 2) << endl;
        cout << "Course: " << sqlite3_column_text(stmt, 3) << endl;
    }
    else {
        cout << "\nStudent not found!\n";
    }

    sqlite3_finalize(stmt);
}

// Function to update student details
void updateStudent(sqlite3* DB) {

    int roll, age;
    string name, course;

    cout << "\nEnter Roll Number to Update: ";
    cin >> roll;

    // Check whether student exists
    string checkSQL = "SELECT * FROM Students WHERE RollNo = ?;";
    sqlite3_stmt* checkStmt;

    sqlite3_prepare_v2(DB, checkSQL.c_str(), -1, &checkStmt, NULL);
    sqlite3_bind_int(checkStmt, 1, roll);

    if (sqlite3_step(checkStmt) != SQLITE_ROW) {
        cout << "\nStudent not found!\n";
        sqlite3_finalize(checkStmt);
        return;
    }

    sqlite3_finalize(checkStmt);

    cout << "Enter New Name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter New Age: ";
    cin >> age;
    cin.ignore();

    cout << "Enter New Course: ";
    getline(cin, course);

    string sql = "UPDATE Students SET Name = ?, Age = ?, Course = ? "
                 "WHERE RollNo = ?;";

    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);

    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, age);
    sqlite3_bind_text(stmt, 3, course.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 4, roll);

    if (sqlite3_step(stmt) == SQLITE_DONE) {
        cout << "\nStudent updated successfully!\n";
    }
    else {
        cout << "\nError updating student!\n";
    }

    sqlite3_finalize(stmt);
}

// Function to delete a student
void deleteStudent(sqlite3* DB) {

    int roll;

    cout << "\nEnter Roll Number to Delete: ";
    cin >> roll;

    string sql = "DELETE FROM Students WHERE RollNo = ?;";

    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL);

    sqlite3_bind_int(stmt, 1, roll);

    if (sqlite3_step(stmt) == SQLITE_DONE) {

        if (sqlite3_changes(DB) > 0) {
            cout << "\nStudent deleted successfully!\n";
        }
        else {
            cout << "\nStudent not found!\n";
        }
    }
    else {
        cout << "\nError deleting student!\n";
    }

    sqlite3_finalize(stmt);
}

// Main function
int main() {

    sqlite3* DB;

    if (sqlite3_open("students.db", &DB) != SQLITE_OK) {
        cout << "Database connection failed!\n";
        return 1;
    }

    cout << "Database connected successfully!\n";

    // Create table if it does not exist
    string sql = "CREATE TABLE IF NOT EXISTS Students ("
                 "RollNo INTEGER PRIMARY KEY, "
                 "Name TEXT NOT NULL, "
                 "Age INTEGER, "
                 "Course TEXT);";

    if (sqlite3_exec(DB, sql.c_str(), NULL, NULL, NULL) != SQLITE_OK) {
        cout << "Table creation failed!\n";
        sqlite3_close(DB);
        return 1;
    }

    int choice;

    do {

        cout << "\n\n====================================";
        cout << "\n       STUDENT MANAGEMENT SYSTEM";
        cout << "\n====================================";
        cout << "\n1. Add Student";
        cout << "\n2. Display All Students";
        cout << "\n3. Search Student";
        cout << "\n4. Update Student";
        cout << "\n5. Delete Student";
        cout << "\n6. Exit";

        cout << "\n====================================";
        cout << "\nEnter Your Choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                addStudent(DB);
                break;

            case 2:
                displayStudents(DB);
                break;

            case 3:
                searchStudent(DB);
                break;

            case 4:
                updateStudent(DB);
                break;

            case 5:
                deleteStudent(DB);
                break;

            case 6:
                cout << "\nThank you for using Student Management System!\n";
                break;

            default:
                cout << "\nInvalid choice! Please try again.\n";
        }

    } while (choice != 6);

    sqlite3_close(DB);

    return 0;
}
