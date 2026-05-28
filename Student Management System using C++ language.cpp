/*Student Management System using C++

The objective of this project is to develop a console-based Student Management System using C++ programming language that can efficiently store, manage, and organize student information.

The system is designed to help educational institutions perform basic student record management operations such as:

~Adding new students
~Viewing student information
~Searching student records
~Updating existing data
~Deleting student records
~Sorting students by CGPA
~Generating academic statistics
~Saving data permanently using file handling

This project also aims to apply important Object-Oriented Programming (OOP) concepts including:

~Classes and Objects
~Encapsulation
~Constructors
~Setters and Getters
~File Handling
~STL Vector
~Functions and Modular Programming

The system provides a simple and user-friendly menu-driven interface where administrators can manage student data securely through a login system.
*/


#include<iostream>
#include<fstream>
#include<vector>
#include<iomanip>
#include<algorithm>
using namespace std;


class Student{
    string name;
    string id;
    string department;
    string phone;
    string email;
    int semester;
    float cgpa;

public:

    Student(){
    cout<<"Empty student"<<endl;
    }

    Student(string name, string id, string department, string phone, string email, int semester, float cgpa){

    cout<<"Parameterized student."<<endl;

    setName(name);
    setId(id);
    setDepartment(department);
    setPhone(phone);
    setEmail(email);
    setSemester(semester);
    setCgpa(cgpa);
    }

    //================
    //-----Setter-----
    //================

    void setName(string name){
    this-> name=name;
    }
    void setId(string id){
    this-> id=id;
    }
    void setDepartment(string department){
    this-> department=department;
    }
    void setPhone(string phone){
    this-> phone=phone;
    }
    void setEmail(string email){
    this-> email=email;
    }
    void setSemester(int semester){
    this-> semester=semester;
    }
    void setCgpa(float cgpa){

        while(cgpa<0 || cgpa>4){
                cout << "Invalid CGPA."<<endl;
                cout << "Enter Again: ";
                cin>>cgpa;
                }

        this-> cgpa=cgpa;
        }

    //================
    //-----Getter-----
    //================

    string getName(){
    return name;
    }
    string getId(){
    return id;
    }
    string getDepartment(){
    return department;
    }
    string getPhone(){
    return phone;
    }
    string getEmail(){
    return email;
    }
    int getSemester(){
    return semester;
    }
    float getCgpa(){
    return cgpa;
    }
    //================
    //Input
    //================

    void inputInfo(){

    cin.ignore();

    cout<<"Enter Name: "<<endl;
    getline(cin,name);

    cout<<"Enter ID: "<<endl;
    getline(cin,id);

    cout<<"Enter Department: "<<endl;
    getline(cin,department);

    cout<<"Enter Phone Number: "<<endl;
    getline(cin,phone);

    cout<<"Enter E-mail: "<<endl;
    getline(cin,email);

    cout<<"Enter Semester: "<<endl;
    cin>>semester;

    cout<<"Enter CGPA: "<<endl;
    cin>>cgpa;

setCgpa(cgpa);
    }
//=============================
//Display Function
//=============================

     void displayInfo(){

     cout<< left
         << setw(15)<< id
         << setw(25)<< name
         << setw(15)<< department
         << setw(10)<< semester
         << setw(10)<< fixed << setprecision(2) << cgpa
         << endl;
     }

//======================
//Detailed display
//======================

      void showDetails(){

      cout<<"\n================================================="<<endl;
      cout<<"                   Student Details                 "<<endl;
      cout<<"==================================================="<<endl;

      cout<<"ID: "<< id <<endl;
      cout<<"Name: "<< name <<endl;
      cout<<"Department: "<< department <<endl;
      cout<<"Phone: "<< phone <<endl;
      cout<<"E-mail: "<< email <<endl;
      cout<<"Semester: "<< semester <<endl;
      cout<<"CGPA: "<< cgpa <<endl;

      }

      //===================
      //File convertion
      //===================

      string toFile(){
      return id + "|" +
             name + "|" +
             department + "|" +
             phone + "|" +
             email + "|" +
             to_string(semester) + "|" +
             to_string(cgpa);
      }

      void fromFile(string line){

        vector<string> data;
        string temp = "";

        for(char c : line){

            if(c == '|'){
                data.push_back(temp);
                temp = "";
            }
            else{
                temp += c;
            }
        }

        data.push_back(temp);

        if(data.size() == 7){

            id = data[0];
            name = data[1];
            department = data[2];
            phone = data[3];
            email = data[4];
            semester = stoi(data[5]);
            cgpa = stof(data[6]);
        }
    }
};

//===================
//Global Vector
//===================

vector<Student>students;

//==========================
//Save file
//==========================

void saveFile(){
    ofstream file("students.text");
    for(auto &student: students){
        file<< student.toFile()<<endl;
    }
    file.close();
}

//===============
//Load File
//===============

void loadFile(){
    ifstream file("student.text");
    string line;
    while(getline(file,line)){
        Student s;
        s.fromFile(line);
        students.push_back(s);
    }
    file.close();
}

//========================
//Unique ID Check
//========================

bool uniqueId(string id){
    for(auto &student: students){
        if(student.getId() == id){
            return false;
        }
    }
    return true;
}

//======================
//Add Student
//======================

void addStudent(){

    Student s;

    s.inputInfo();

    if(!uniqueId(s.getId())){

        cout << "\nID Already Exists.\n";
        return;
    }

    students.push_back(s);

    saveFile();

    cout << "\nStudent Added Successfully.\n";
}

//===========================
//Display All Students
//===========================

void showAllStudents(){

    if(students.empty()){
        cout<<"\nNo Student Found.\n";
        return;
    }

    cout<<"\n========================================================\n";

    cout<<left
        <<setw(15)<< "ID"
        <<setw(25)<< "Name"
        <<setw(15)<< "Department"
        <<setw(10)<< "Semester"
        <<setw(10)<< "CGPA"
        <<endl;


    cout<<"========================================================\n";

    for(auto &student: students){
        student.displayInfo();
    }
}

//================================
//Search Students
//================================

void searchStudent(){
    string id;

    cout<<"Enter Student ID: ";
    cin>>id;

    for(auto &student: students){
        if(student.getId() == id){
            student.showDetails();
            return;
        }
    }
    cout<< "\nStudent Not Found.\n";
}

//===============================
//Update Student
//===============================

void updateStudent(){
    string id;

    cout<< "Enter Student ID: ";
    cin>> id;

    for(auto &student: students){
        if(student.getId() == id){
             string name;
             string id;
             string department;
             string phone;
             string email;
             int semester;
             float cgpa;


    cin.ignore();

    cout<<"New Enter Name: "<<endl;
    getline(cin,name);

    cout<<"New Enter ID: "<<endl;
    getline(cin,id);

    cout<<"New Enter Department: "<<endl;
    getline(cin,department);

    cout<<"Enter Phone Number: "<<endl;
    getline(cin,phone);

    cout<<"New Enter E-mail: "<<endl;
    getline(cin,email);

    cout<<"New Enter Semester: "<<endl;
    cin>>semester;

    cout<<"New Enter CGPA: "<<endl;
    cin>>cgpa;

    student.setName(name);
    student.setId(id);
    student.setDepartment(department);
    student.setPhone(phone);
    student.setEmail(email);
    student.setSemester(semester);
    student.setCgpa(cgpa);

    saveFile();

    cout<<"\nStudent Updated Successfully.\n"<<endl;

    return;
      }
    }
  cout<<"\nStudent Not Found.\n";
}

//======================
//Delete Student
//======================

void deleteStudent(){

    string id;

    cout << "Enter Student ID: ";
    cin >> id;

    for(auto it = students.begin(); it != students.end(); it++){

        if(it->getId() == id){

            char choice;

            cout << "Are You Sure? (Y/N): ";
            cin >> choice;

            if(choice == 'Y' || choice == 'y'){

                students.erase(it);

                saveFile();

                cout << "\nStudent Deleted Successfully.\n";
            }
            else{
                cout << "\nDeletion Cancelled.\n";
            }

            return;
        }
    }

    cout << "\nStudent Not Found.\n";
}


//=====================
//Sort By CGPA
//=====================

void sortByCgpa(){

    sort(students.begin(), students.end(),

         [](Student a, Student b){

            return a.getCgpa() > b.getCgpa();
         });

    cout << "\nStudents Sorted By CGPA.\n";
}


//=========================
//Statistics
//=========================

void statistics(){

      if(students.empty()){

        cout << "\nNo Student Data Found.\n";
        return;
    }

    float highest = students[0].getCgpa();
    float lowest = students[0].getCgpa();
    float total = 0;

    for(auto &student : students){

        float cg = student.getCgpa();

        if(cg > highest){
            highest = cg;
        }

        if(cg < lowest){
            lowest = cg;
        }

        total += cg;
    }

    cout << "\n========== Statistics ==========\n";

    cout << "Highest CGPA : " << highest << endl;
    cout << "Lowest CGPA  : " << lowest << endl;
    cout << "Average CGPA : "
         << total / students.size() << endl;
}

// =========================
// Login System
// =========================

bool login(){

    string username;
    string password;

    for(int i=1; i<=3; i++){

        cout << "\n========== LOGIN ==========\n";

        cout << "Username: ";
        cin >> username;

        cout << "Password: ";
        cin >> password;

        if(username == "admin" &&
           password == "1234"){

            cout << "\nLogin Successful.\n";
            return true;
        }

        cout << "\nInvalid Username or Password.\n";
    }

    return false;
}

// =========================
// Menu
// =========================

void menu(){

    int choice;

    do{

        cout << "\n====================================\n";
        cout << "     STUDENT MANAGEMENT SYSTEM\n";
        cout << "====================================\n";

        cout << "1. Add Student\n";
        cout << "2. Show All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Sort By CGPA\n";
        cout << "7. Statistics\n";
        cout << "0. Exit\n";

        cout << "====================================\n";

        cout << "Enter Choice: ";
        cin >> choice;

        switch(choice){

        case 1:
            addStudent();
            break;

        case 2:
            showAllStudents();
            break;

        case 3:
            searchStudent();
            break;

        case 4:
            updateStudent();
            break;

        case 5:
            deleteStudent();
            break;

        case 6:
            sortByCgpa();
            break;

        case 7:
            statistics();
            break;

        case 0:
            cout << "\nProgram Ended.\n";
            break;

        default:
            cout << "\nInvalid Choice.\n";
        }

    }while(choice != 0);
}

// =========================
// Main Function
// =========================

int main(){

    loadFile();

    if(login()){

        menu();
    }
    else{

        cout << "\nToo Many Failed Attempts.\n";
    }

    return 0;
}









