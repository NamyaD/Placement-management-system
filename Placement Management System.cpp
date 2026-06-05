#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
using namespace std;

string toLowerCase(string text) {
    for (int i = 0; i < text.length(); i++) {
        text[i] = tolower(text[i]);
    }
    return text;
}

bool containsText(string mainText, string searchText) {
    mainText = toLowerCase(mainText);
    searchText = toLowerCase(searchText);

    return mainText.find(searchText) != string::npos;
}

class Student {
public:
    int rollNo;
    string name;
    string branch;
    float cgpa;
    vector<string> skills;
    bool placed;
    string companyPlacedIn;
    vector<string> applicationHistory;
    vector<string> interviewRounds;

    Student(int r, string n, string b, float c, vector<string> s) {
        rollNo = r;
        name = n;
        branch = b;
        cgpa = c;
        skills = s;
        placed = false;
        companyPlacedIn = "Not Placed";
    }

    void displayStudent() {
        cout << "\nRoll No: " << rollNo;
        cout << "\nName: " << name;
        cout << "\nBranch: " << branch;
        cout << "\nCGPA: " << cgpa;

        cout << "\nSkills: ";
        for (int i = 0; i < skills.size(); i++) {
            cout << skills[i];
            if (i != skills.size() - 1) cout << ", ";
        }

        cout << "\nStatus: " << (placed ? "Placed" : "Not Placed");
        cout << "\nCompany Placed In: " << companyPlacedIn << endl;
    }
};

class Company {
public:
    string name;
    float requiredCGPA;
    string eligibleBranch;
    string requiredSkill;
    float package;
    string jobRole;

    Company(string n, float cg, string branch, string skill, float pkg, string role) {
        name = n;
        requiredCGPA = cg;
        eligibleBranch = branch;
        requiredSkill = skill;
        package = pkg;
        jobRole = role;
    }

    void displayCompany() {
        cout << "\nCompany Name: " << name;
        cout << "\nRequired CGPA: " << requiredCGPA;
        cout << "\nEligible Branch: " << eligibleBranch;
        cout << "\nRequired Skill: " << requiredSkill;
        cout << "\nPackage: " << package << " LPA";
        cout << "\nJob Role: " << jobRole << endl;
    }
};

class PlacementSystem {
private:
    vector<Student> students;
    vector<Company> companies;

public:
    PlacementSystem() {
        addSampleData();
    }

    void addSampleData() {
        students.push_back(Student(101, "Namya Dutta", "CSE", 8.4, {"C++", "DSA", "SQL"}));
        students.push_back(Student(102, "Rahul Sharma", "ECE", 7.6, {"Python", "Excel"}));
        students.push_back(Student(103, "Simran Kaur", "CSE", 9.0, {"SQL", "PowerBI", "Python"}));

        companies.push_back(Company("TCS", 7.0, "CSE", "C++", 3.5, "Software Developer"));
        companies.push_back(Company("Infosys", 7.5, "CSE", "Python", 4.2, "System Engineer"));
        companies.push_back(Company("Axtria", 8.0, "CSE", "SQL", 5.5, "Data Analyst"));
    }

    bool hasSkill(Student &student, string skill) {
        for (int i = 0; i < student.skills.size(); i++) {
            if (toLowerCase(student.skills[i]) == toLowerCase(skill)) {
                return true;
            }
        }
        return false;
    }

    void addStudent() {
        int roll, skillCount;
        string name, branch, skill;
        float cgpa;
        vector<string> skills;

        cout << "Enter Roll Number: ";
        cin >> roll;
        cin.ignore();

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Branch: ";
        getline(cin, branch);

        cout << "Enter CGPA: ";
        cin >> cgpa;

        cout << "Enter number of skills: ";
        cin >> skillCount;
        cin.ignore();

        for (int i = 0; i < skillCount; i++) {
            cout << "Enter Skill " << i + 1 << ": ";
            getline(cin, skill);
            skills.push_back(skill);
        }

        students.push_back(Student(roll, name, branch, cgpa, skills));
        cout << "Student added successfully!\n";
    }

    void displayStudents() {
        if (students.empty()) {
            cout << "No students available.\n";
            return;
        }

        cout << "\n----- All Students -----\n";
        for (int i = 0; i < students.size(); i++) {
            students[i].displayStudent();
        }
    }

    void addCompany() {
        string name, branch, skill, role;
        float cgpa, package;

        cin.ignore();

        cout << "Enter Company Name: ";
        getline(cin, name);

        cout << "Enter Required CGPA: ";
        cin >> cgpa;
        cin.ignore();

        cout << "Enter Eligible Branch: ";
        getline(cin, branch);

        cout << "Enter Required Skill: ";
        getline(cin, skill);

        cout << "Enter Package Offered: ";
        cin >> package;
        cin.ignore();

        cout << "Enter Job Role: ";
        getline(cin, role);

        companies.push_back(Company(name, cgpa, branch, skill, package, role));
        cout << "Company added successfully!\n";
    }

    void displayCompanies() {
        if (companies.empty()) {
            cout << "No companies available.\n";
            return;
        }

        cout << "\n----- All Companies -----\n";
        for (int i = 0; i < companies.size(); i++) {
            companies[i].displayCompany();
        }
    }

    void checkEligibility() {
        int roll;
        string companyName;

        cout << "Enter Student Roll Number: ";
        cin >> roll;
        cin.ignore();

        cout << "Enter Company Name: ";
        getline(cin, companyName);

        for (int i = 0; i < students.size(); i++) {
            if (students[i].rollNo == roll) {
                for (int j = 0; j < companies.size(); j++) {
                    if (companies[j].name == companyName) {
                        if (students[i].cgpa >= companies[j].requiredCGPA &&
                            students[i].branch == companies[j].eligibleBranch &&
                            hasSkill(students[i], companies[j].requiredSkill)) {
                            cout << "Student is eligible for " << companies[j].name << ".\n";
                        } else {
                            cout << "Student is not eligible for " << companies[j].name << ".\n";
                        }
                        return;
                    }
                }
            }
        }

        cout << "Student or company not found.\n";
    }

    void applyToCompany() {
        int roll;
        string companyName;

        cout << "Enter Student Roll Number: ";
        cin >> roll;
        cin.ignore();

        cout << "Enter Company Name: ";
        getline(cin, companyName);

        for (int i = 0; i < students.size(); i++) {
            if (students[i].rollNo == roll) {
                for (int j = 0; j < companies.size(); j++) {
                    if (companies[j].name == companyName) {
                        students[i].applicationHistory.push_back(companyName);

                        if (students[i].cgpa >= companies[j].requiredCGPA &&
                            students[i].branch == companies[j].eligibleBranch &&
                            hasSkill(students[i], companies[j].requiredSkill)) {
                            cout << students[i].name << " applied successfully to " << companyName << ".\n";
                        } else {
                            cout << "Application saved, but student is not eligible.\n";
                        }
                        return;
                    }
                }
            }
        }

        cout << "Student or company not found.\n";
    }

    void shortlistStudents() {
        string companyName;
        cin.ignore();

        cout << "Enter Company Name: ";
        getline(cin, companyName);

        for (int j = 0; j < companies.size(); j++) {
            if (companies[j].name == companyName) {
                cout << "\nShortlisted Students for " << companyName << ":\n";
                bool found = false;

                for (int i = 0; i < students.size(); i++) {
                    if (!students[i].placed &&
                        students[i].cgpa >= companies[j].requiredCGPA &&
                        students[i].branch == companies[j].eligibleBranch &&
                        hasSkill(students[i], companies[j].requiredSkill)) {
                        cout << students[i].rollNo << " - " << students[i].name << endl;
                        found = true;
                    }
                }

                if (!found) {
                    cout << "No eligible students found.\n";
                }
                return;
            }
        }

        cout << "Company not found.\n";
    }

    void updatePlacementStatus() {
        int roll;
        string companyName;

        cout << "Enter Student Roll Number: ";
        cin >> roll;
        cin.ignore();

        cout << "Enter Company Name where student is placed: ";
        getline(cin, companyName);

        for (int i = 0; i < students.size(); i++) {
            if (students[i].rollNo == roll) {
                students[i].placed = true;
                students[i].companyPlacedIn = companyName;
                cout << "Placement status updated successfully!\n";
                return;
            }
        }

        cout << "Student not found.\n";
    }

    void addInterviewRound() {
        int roll;
        string round;

        cout << "Enter Student Roll Number: ";
        cin >> roll;
        cin.ignore();

        cout << "Enter Interview Round Status: ";
        getline(cin, round);

        for (int i = 0; i < students.size(); i++) {
            if (students[i].rollNo == roll) {
                students[i].interviewRounds.push_back(round);
                cout << "Interview round added successfully!\n";
                return;
            }
        }

        cout << "Student not found.\n";
    }

    void viewApplicationHistory() {
        int roll;

        cout << "Enter Student Roll Number: ";
        cin >> roll;

        for (int i = 0; i < students.size(); i++) {
            if (students[i].rollNo == roll) {
                cout << "\nApplication History of " << students[i].name << ":\n";

                if (students[i].applicationHistory.empty()) {
                    cout << "No applications yet.\n";
                } else {
                    for (int j = 0; j < students[i].applicationHistory.size(); j++) {
                        cout << j + 1 << ". " << students[i].applicationHistory[j] << endl;
                    }
                }

                cout << "\nInterview Rounds:\n";

                if (students[i].interviewRounds.empty()) {
                    cout << "No interview rounds added yet.\n";
                } else {
                    for (int j = 0; j < students[i].interviewRounds.size(); j++) {
                        cout << j + 1 << ". " << students[i].interviewRounds[j] << endl;
                    }
                }

                return;
            }
        }

        cout << "Student not found.\n";
    }

    void partialSearchStudent() {
        string keyword;
        cin.ignore();

        cout << "Enter student name keyword: ";
        getline(cin, keyword);

        bool found = false;

        for (int i = 0; i < students.size(); i++) {
            if (containsText(students[i].name, keyword)) {
                students[i].displayStudent();
                found = true;
            }
        }

        if (!found) {
            cout << "No matching student found.\n";
        }
    }

    void partialSearchCompany() {
        string keyword;
        cin.ignore();

        cout << "Enter company name keyword: ";
        getline(cin, keyword);

        bool found = false;

        for (int i = 0; i < companies.size(); i++) {
            if (containsText(companies[i].name, keyword)) {
                companies[i].displayCompany();
                found = true;
            }
        }

        if (!found) {
            cout << "No matching company found.\n";
        }
    }

    void sortStudentsByCGPA() {
        sort(students.begin(), students.end(), compareCGPA);
        cout << "Students sorted by CGPA successfully!\n";
        displayStudents();
    }

    static bool compareCGPA(Student a, Student b) {
        return a.cgpa > b.cgpa;
    }

    void sortCompaniesByPackage() {
        sort(companies.begin(), companies.end(), comparePackage);
        cout << "Companies sorted by package successfully!\n";
        displayCompanies();
    }

    static bool comparePackage(Company a, Company b) {
        return a.package > b.package;
    }

    void displayPlacedUnplaced() {
        cout << "\n----- Placed Students -----\n";
        for (int i = 0; i < students.size(); i++) {
            if (students[i].placed) {
                cout << students[i].rollNo << " - " << students[i].name
                     << " - " << students[i].companyPlacedIn << endl;
            }
        }

        cout << "\n----- Unplaced Students -----\n";
        for (int i = 0; i < students.size(); i++) {
            if (!students[i].placed) {
                cout << students[i].rollNo << " - " << students[i].name << endl;
            }
        }
    }

    void dashboard() {
        int placedCount = 0;
        float highestPackage = 0;
        float totalPackage = 0;

        for (int i = 0; i < students.size(); i++) {
            if (students[i].placed) {
                placedCount++;
            }
        }

        for (int i = 0; i < companies.size(); i++) {
            totalPackage += companies[i].package;

            if (companies[i].package > highestPackage) {
                highestPackage = companies[i].package;
            }
        }

        cout << "\n----- Placement Dashboard -----\n";
        cout << "Total Students: " << students.size() << endl;
        cout << "Total Companies: " << companies.size() << endl;
        cout << "Placed Students: " << placedCount << endl;
        cout << "Unplaced Students: " << students.size() - placedCount << endl;
        cout << "Highest Package: " << highestPackage << " LPA" << endl;

        if (!companies.empty()) {
            cout << "Average Package: " << totalPackage / companies.size() << " LPA" << endl;
        } else {
            cout << "Average Package: 0 LPA\n";
        }
    }

    void studentPortal() {
        int roll;
        cout << "Enter your Roll Number: ";
        cin >> roll;

        for (int i = 0; i < students.size(); i++) {
            if (students[i].rollNo == roll) {
                int choice = 0;

                while (choice != 5) {
                    cout << "\n===== STUDENT PORTAL =====\n";
                    cout << "1. View My Profile\n";
                    cout << "2. View Companies\n";
                    cout << "3. Apply to Company\n";
                    cout << "4. View My Application History\n";
                    cout << "5. Logout\n";
                    cout << "Enter choice: ";
                    cin >> choice;

                    if (choice == 1) {
                        students[i].displayStudent();
                    } else if (choice == 2) {
                        displayCompanies();
                    } else if (choice == 3) {
                        string companyName;
                        cin.ignore();

                        cout << "Enter Company Name: ";
                        getline(cin, companyName);

                        bool found = false;

                        for (int j = 0; j < companies.size(); j++) {
                            if (companies[j].name == companyName) {
                                students[i].applicationHistory.push_back(companyName);
                                cout << "Applied successfully to " << companyName << ".\n";
                                found = true;
                                break;
                            }
                        }

                        if (!found) {
                            cout << "Company not found.\n";
                        }
                    } else if (choice == 4) {
                        cout << "\nApplication History:\n";

                        if (students[i].applicationHistory.empty()) {
                            cout << "No applications yet.\n";
                        } else {
                            for (int j = 0; j < students[i].applicationHistory.size(); j++) {
                                cout << j + 1 << ". " << students[i].applicationHistory[j] << endl;
                            }
                        }

                        cout << "\nInterview Rounds:\n";

                        if (students[i].interviewRounds.empty()) {
                            cout << "No interview rounds yet.\n";
                        } else {
                            for (int j = 0; j < students[i].interviewRounds.size(); j++) {
                                cout << j + 1 << ". " << students[i].interviewRounds[j] << endl;
                            }
                        }
                    } else if (choice == 5) {
                        cout << "Logged out from Student Portal.\n";
                    } else {
                        cout << "Invalid choice.\n";
                    }
                }
                return;
            }
        }

        cout << "Student not found.\n";
    }
};

bool adminLogin() {
    string password;

    cout << "Enter Admin Password: ";
    cin >> password;

    if (password == "admin123") {
        cout << "Admin Login Successful!\n";
        return true;
    }

    cout << "Wrong Password.\n";
    return false;
}

void adminMenu(PlacementSystem &system) {
    int choice = 0;

    while (choice != 17) {
        cout << "\n========== ADMIN MENU ==========\n";
        cout << "1. Add Student Profile\n";
        cout << "2. Display All Students\n";
        cout << "3. Add Company Details\n";
        cout << "4. Display All Companies\n";
        cout << "5. Check Student Eligibility\n";
        cout << "6. Apply Student to Company\n";
        cout << "7. Shortlist Eligible Students\n";
        cout << "8. Update Placement Status\n";
        cout << "9. Add Interview Round\n";
        cout << "10. View Application History\n";
        cout << "11. Search Student by Name\n";
        cout << "12. Search Company by Name\n";
        cout << "13. Sort Students by CGPA\n";
        cout << "14. Sort Companies by Package\n";
        cout << "15. Display Placed and Unplaced Students\n";
        cout << "16. Placement Statistics Dashboard\n";
        cout << "17. Logout\n";
        cout << "Enter choice: ";

        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input.\n";
            continue;
        }

        switch (choice) {
            case 1: system.addStudent(); break;
            case 2: system.displayStudents(); break;
            case 3: system.addCompany(); break;
            case 4: system.displayCompanies(); break;
            case 5: system.checkEligibility(); break;
            case 6: system.applyToCompany(); break;
            case 7: system.shortlistStudents(); break;
            case 8: system.updatePlacementStatus(); break;
            case 9: system.addInterviewRound(); break;
            case 10: system.viewApplicationHistory(); break;
            case 11: system.partialSearchStudent(); break;
            case 12: system.partialSearchCompany(); break;
            case 13: system.sortStudentsByCGPA(); break;
            case 14: system.sortCompaniesByPackage(); break;
            case 15: system.displayPlacedUnplaced(); break;
            case 16: system.dashboard(); break;
            case 17: cout << "Admin logged out.\n"; break;
            default: cout << "Invalid choice.\n";
        }
    }
}

int main() {
    PlacementSystem system;
    int choice = 0;

    while (choice != 3) {
        cout << "\n=====================================\n";
        cout << "     PLACEMENT MANAGEMENT SYSTEM     \n";
        cout << "=====================================\n";
        cout << "1. Admin Login\n";
        cout << "2. Student Login\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";

        cin >> choice;

        if (choice == 1) {
            if (adminLogin()) {
                adminMenu(system);
            }
        } else if (choice == 2) {
            system.studentPortal();
        } else if (choice == 3) {
            cout << "Exiting Placement Management System.\n";
        } else {
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}