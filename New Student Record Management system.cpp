#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
#include <limits>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cctype>
#include <regex>

using namespace std;

class Student {
private:
    int rollNumber;
    string fullName;
    string fatherName;
    string dateOfBirth;
    string gender;
    string nationality;
    string phoneNumber;
    string homeAddress;
    string standard;
    string emergencyContact;
    string feeRecords;

public:
    void introduction();
    bool login();
    void getData();
    void showData() const;
    void storeData() const;
    static void searchData(int studentID);
    static void viewAllData();
    static void deleteData(int studentID);
    void updateData(int studentID, const string& studentName = "");
    void clearScreen();
    static bool isUniqueRollNumber(int);
    static void removeRollNumber(int rollNumber);
    static bool isValidDate(const string& date);
    static bool isValidPhoneNumber(const string& phone);
    static void setColor(int color);
    static void resetColor();
    static void drawBox(const string& title);
};

vector<int> existingRollNumbers;

void Student::setColor(int color) {
    cout << "\033[" << color << "m";
}

void Student::resetColor() {
    cout << "\033[0m";
}

void Student::drawBox(const string& title) {
    setColor(36); // Cyan color
    cout << "=============================================\n";
    cout << "|";
    cout << setw(44) << left << title << "|\n";
    cout << "=============================================\n";
    resetColor();
}

void Student::introduction() {
    clearScreen();
    drawBox("    NEW STUDENT RECORD MANAGEMENT SYSTEM");
    setColor(33); // Yellow color
    cout << "|          CREATED BY: SHEIKH SAHAB         |\n";
    resetColor();
    drawBox("Your data,our priority!");
    cout << "Press enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

bool Student::login() {
    clearScreen();
    drawBox("LOGIN MENU");
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (username == "admin" && password == "admin123") {
        setColor(32); // Green color
        cout << "\nLogin successful!\n";
        resetColor();
        cout << "Press enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return true;
    } else {
        setColor(31); // Red color
        cout << "\nIncorrect username or password!\n";
        resetColor();
        cout << "Press enter to exit...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        exit(0);
        return false;
    }
}

void Student::getData() {
    clearScreen();
    drawBox("ENTER STUDENT DETAILS");
    cout << "Roll Number / Student ID: ";
    cin >> rollNumber;
    while (!isUniqueRollNumber(rollNumber)) {
        setColor(31); // Red color
        cout << "Roll Number / Student ID already exists. Enter a unique one: ";
        resetColor();
        cin >> rollNumber;
    }
    existingRollNumbers.push_back(rollNumber);
    cout << "Full Name: ";
    cin.ignore();
    getline(cin, fullName);
    cout << "Father's Name: ";
    getline(cin, fatherName);
    cout << "Date of Birth (DD/MM/YYYY): ";
    getline(cin, dateOfBirth);
    while (!isValidDate(dateOfBirth)) {
        setColor(31); // Red color
        cout << "Invalid date format. Please enter again (DD/MM/YYYY): ";
        resetColor();
        getline(cin, dateOfBirth);
    }
    cout << "Gender: ";
    getline(cin, gender);
    cout << "Nationality: ";
    getline(cin, nationality);
   cout << "Phone Number (+92-xxxxxxxxxx): ";
    getline(cin, phoneNumber);
    while (!isValidPhoneNumber(phoneNumber)) {
        setColor(31); // Red color
        cout << "Invalid phone number. Please enter again: ";
        resetColor();
        getline(cin, phoneNumber);
    }
    cout << "Home Address: ";
    getline(cin, homeAddress);
    cout << "Class/Standard: ";
    getline(cin, standard);
    cout << "Emergency Contact Details (+92-xxxxxxxxxx): ";
    getline(cin, emergencyContact);
    while (!isValidPhoneNumber(emergencyContact)) {
        setColor(31); // Red color
        cout << "Invalid emergency contact number. Please enter again: ";
        resetColor();
        getline(cin, emergencyContact);
    }

    cout << "Fee Records (fees paid, pending payments): ";
    getline(cin, feeRecords);
}

void Student::showData() const {
    system("cls");
    drawBox("STUDENT DETAILS");
    setColor(34); // Blue color
    cout << "Roll Number / Student ID: " << rollNumber << endl;
    cout << "Full Name: " << fullName << endl;
    cout << "Father's Name: " << fatherName << endl;
    cout << "Date of Birth: " << dateOfBirth << endl;
    cout << "Gender: " << gender << endl;
    cout << "Nationality: " << nationality << endl;
    cout << "Phone Number: " << phoneNumber << endl;
    cout << "Home Address: " << homeAddress << endl;
    cout << "Class/Standard: " << standard << endl;
    cout << "Emergency Contact Details: " << emergencyContact << endl;
    cout << "Fee Records: " << feeRecords << endl;
    resetColor();
}

void Student::storeData() const {
    ofstream outFile("students.txt", ios::app);
    if (outFile) {
        outFile << rollNumber << "," << fullName << "," << fatherName << "," << dateOfBirth << "," << gender << "," << nationality << "," << phoneNumber << "," << homeAddress << "," << standard << "," << emergencyContact << "," << feeRecords << endl;
        outFile.close();
        setColor(32); // Green color
        cout << "Data Stored Successfully!" << endl;
        resetColor();
    } else {
        setColor(31); // Red color
        cerr << "Error: Unable to open file!" << endl;
        resetColor();
    }
}

void Student::viewAllData() {
    system("cls");
    drawBox("VIEW ALL STUDENT RECORDS");
    ifstream inFile("students.txt");
    if (inFile) {
        string line;
        while (getline(inFile, line)) {
            setColor(34); // Blue color
            cout << line << endl;
            resetColor();
        }
        inFile.close();
    } else {
        setColor(31); // Red color
        cerr << "Error: Unable to open file!" << endl;
        resetColor();
    }

    cout << "Press enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void Student::searchData(int studentID) {
    system("cls");
    drawBox("SEARCH STUDENT RECORD");
    ifstream inFile("students.txt");
    if (inFile) {
        string line;
        bool found = false;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string temp;
            int currentID;
            getline(ss, temp, ',');
            currentID = stoi(temp);
            if (currentID == studentID) {
                setColor(34); // Blue color
                cout << line << endl;
                resetColor();
                found = true;
                break;
            }
        }
        if (!found) {
            setColor(31); // Red color
            cout << "Record not found!" << endl;
            resetColor();
        }
        inFile.close();
    } else {
        setColor(31); // Red color
        cerr << "Error: Unable to open file!" << endl;
        resetColor();
    }

    cout << "Press enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void Student::deleteData(int studentID) {
    system("cls");
    drawBox("DELETE STUDENT RECORD");
    ifstream inFile("students.txt");
    if (inFile) {
        vector<string> lines;
        string line;
        bool found = false;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string temp;
            int currentID;
            getline(ss, temp, ',');
            currentID = stoi(temp);
            if (currentID != studentID) {
                lines.push_back(line);
            } else {
                found = true;
            }
        }
        inFile.close();

        if (found) {
            removeRollNumber(studentID);
            ofstream outFile("students.txt", ios::trunc);
            if (outFile) {
                for (const auto& l : lines) {
                    outFile << l << endl;
                }
                outFile.close();
                setColor(32); // Green color
                cout << "Record Deleted Successfully!" << endl;
                resetColor();
            } else {
                setColor(31); // Red color
                cerr << "Error: Unable to open file!" << endl;
                resetColor();
            }
        } else {
            setColor(31); // Red color
            cout << "Record not found!" << endl;
            resetColor();
        }
    } else {
        setColor(31); // Red color
        cerr << "Error: Unable to open file!" << endl;
        resetColor();
    }

    cout << "Press enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void Student::updateData(int studentID, const string& studentName) {
    clearScreen();
    drawBox("UPDATE STUDENT RECORD");
    ifstream inFile("students.txt");
    if (inFile) {
        vector<string> lines;
        string line;
        bool found = false;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string temp;
            int currentID;
            string currentName;
            getline(ss, temp, ',');
            currentID = stoi(temp);
            getline(ss, currentName, ',');
            if (currentID != studentID || (!studentName.empty() && currentName != studentName)) {
                lines.push_back(line);
            } else {
                found = true;
                getData(); // Get new data from the user
                stringstream updatedData;
                updatedData << rollNumber << "," << fullName << "," << fatherName << "," << dateOfBirth << "," << gender << "," << nationality << "," << phoneNumber << "," << homeAddress << "," << standard << "," << emergencyContact << "," << feeRecords;
                lines.push_back(updatedData.str());
            }
        }
        inFile.close();

        if (found) {
            ofstream outFile("students.txt", ios::trunc);
            if (outFile) {
                for (const auto& l : lines) {
                    outFile << l << endl;
                }
                outFile.close();
                setColor(32); // Green color
                cout << "Record Updated Successfully!" << endl;
                resetColor();
            } else {
                setColor(31); // Red color
                cerr << "Error: Unable to open file!" << endl;
                resetColor();
            }
        } else {
            setColor(31); // Red color
            cout << "Record not found!" << endl;
            resetColor();
        }
    } else {
        setColor(31); // Red color
        cerr << "Error: Unable to open file!" << endl;
        resetColor();
    }

    cout << "Press enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

bool Student::isValidDate(const string& date) {
    if (date.length() != 10 || date[2] != '/' || date[5] != '/') {
        return false;
    }
    int day, month, year;
    try {
        day = stoi(date.substr(0, 2));
        month = stoi(date.substr(3, 2));
        year = stoi(date.substr(6, 4));
    } catch (...) {
        return false;
    }
    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1900 || year > 2100) {
        return false;
    }
    return true;
}

bool Student::isValidPhoneNumber(const string& phone) {
    return phone.length() == 14 && phone.substr(0, 4) == "+92-" && all_of(phone.begin() + 4, phone.end(), ::isdigit);
}

void Student::clearScreen() {
   
    system("cls"); 
}

bool Student::isUniqueRollNumber(int rollNumber) {
    return find(existingRollNumbers.begin(), existingRollNumbers.end(), rollNumber) == existingRollNumbers.end();
}

void Student::removeRollNumber(int rollNumber) {
    existingRollNumbers.erase(remove(existingRollNumbers.begin(), existingRollNumbers.end(), rollNumber), existingRollNumbers.end());
}

int main() {
    Student s;
    s.introduction();
    if (!s.login()) {
        return 0;
    }

    int choice;
    do {
        s.clearScreen();
        s.drawBox("MAIN MENU");
        cout << "| 1. Add Student Record                     |\n";
        cout << "| 2. View All Student Records               |\n";
        cout << "| 3. Search Student Record                  |\n";
        cout << "| 4. Delete Student Record                  |\n";
        cout << "| 5. Update Student Record                  |\n";
        cout << "| 6. Exit                                   |\n";
        s.drawBox("Your data,our priority.........");
        cout << "Enter your choice: ";
        cin >> choice;

        int studentID;
        string studentName;
        switch (choice) {
            case 1:
                s.getData();
                s.storeData();
                break;
            case 2:
                s.viewAllData();
                break;
            case 3:
                cout << "Enter Student ID to search: ";
                cin >> studentID;
                s.searchData(studentID);
                break;
            case 4:
                cout << "Enter Student ID to delete: ";
                cin >> studentID;
                s.deleteData(studentID);
                break;
            case 5:
                cout << "Enter Student ID to update: ";
                cin >> studentID;
                cout << "Enter Student Name to update (leave empty to skip): ";
                cin.ignore();
                getline(cin, studentName);
                s.updateData(studentID, studentName);
                break;
            case 6:
                Student::setColor(32); // Green color
                cout << "Exiting..." << endl;
                Student::resetColor();
                break;
            default:
                Student::setColor(31); // Red color
                cout << "Invalid choice! Please enter a valid option." << endl;
                Student::resetColor();
                break;
        }
    } while (choice != 6);

    return 0;
}
