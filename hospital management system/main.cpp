#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>

using namespace std;

void startScreen();
void Title();
void MainMenu();
void LoginScreen();
void Add_rec();
void func_list();
void Search_rec();
void Edit_rec();
void Delete_rec();
void Exit_hospital();
bool do_authorization(string, string, string, string);

struct patient
{
    int age;
    char gender;
    char first_name[20];
    char last_name[20];
    char contact_no[20];
    char address[100];
    char email[50];
    char doctor[20];
    char problem[50];
};

struct patient p, temp_patient;

void gotoxy(short x, short y) {
    cout << "\x1b[" << y << ";" << x << "H";
}

int main() {
    startScreen();
    Title();
    LoginScreen();
}

void startScreen() {
    cout << "\n\n\n\n\n\t\t\t --------------------------------------";
    cout << "\n\t\t\tWELCOME TO HOSPITAL MANAGEMENT SYSTEM";
    cout << "\n\t\t\t ---------------------------------------\n";
    cout << "\n\nPress any key to continue...\n";
    cin.get();
    system("cls");
}

void Title() {
    cout << "\n\n\n\n\n\t\t\t --------------------------------";
    cout << "\n\t\t\t     HOSPITAL MANAGEMENT SYSTEM";
    cout << "\n\t\t\t --------------------------------\n";
}

void LoginScreen() {
    bool authorized = false;
    int attempts = 3;
    string username;
    string password;
    string authorized_username = "aryanagarwal";
    string authorized_password = "aryan123";
    do
    {
        cout << "\n\n\n\n\t\t\t\tEnter Username and Password: ";
        cout << "\n\n\t\t\tUsername: ";
        cin >> username;
        cout << "\n\n\t\t\tPassword: ";
        cin >> password;
        authorized = do_authorization(username, password, authorized_username, authorized_password);
        if (authorized) {
            cout << "\n\n\t\t\tLOGIN SUCCESSFUL\n";
            cout << "\n\n\t\t\tWELCOME INSIDE THE HOSPITAL MANAGEMENT SYSTEM\n";
            MainMenu();
            break;
        }
        else {
            attempts--;
            if (attempts == 0) {
                cout << "\n\n\t\t\tACCESS DENIED!!EXIT\n";
                exit(0);
            }
            cout << "\n\n\t\t\tWRONG CREDENTIALS!! LOGIN AGAIN: " << attempts << " ATTEMPTS LEFT\n";
        }
    } while (!authorized);
    system("cls");
}

bool do_authorization(string username, string password, string correct_username, string correct_password) {
    return (username == correct_username) && (password == correct_password);
}

void MainMenu() {
    system("cls");
    int choice;
    Title();
    cout << "\n\n\n\t\t\t1. Add Patient Record\n";
    cout << "\n\t\t\t2. List Patient Records\n";
    cout << "\n\t\t\t3. Search Patient Records\n";
    cout << "\n\t\t\t4. Edit Patient Records\n";
    cout << "\n\t\t\t5. Delete Patient Records\n";
    cout << "\n\t\t\t6. Exit\n";
    cout << "\n\n\n\n\t\t\tChoose from 1-6: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
        Add_rec();
        break;

    case 2:
        func_list();
        break;

    case 3:
        Search_rec();
        break;

    case 4:
        Edit_rec();
        break;

    case 5:
        Delete_rec();
        break;

    case 6:
        Exit_hospital();
        exit(0);

    default:
        cout << "\n\t\t\tENTER CORRECT CHOICE\n";
        MainMenu();
    }
    MainMenu();
}

void Add_rec() {
    system("cls");
    Title();

    ofstream fp("patients.dat", ios::binary | ios::app);
    cout << "\n\n\n\t\t\t!!!!!! ADD PATIENT DETAILS !!!!!!\n";

    cout << "\n\t\t\tFirst Name: ";
    cin >> p.first_name;
    p.first_name[0] = toupper(p.first_name[0]);

    cout << "\n\t\t\tLast Name: ";
    cin >> p.last_name;
    p.last_name[0] = toupper(p.last_name[0]);

    cin.ignore();
    do {
        cout << "\n\t\t\tGender(M/F): ";
        cin >> p.gender;
        p.gender = toupper(p.gender);
        if (p.gender != 'M' && p.gender != 'F') {
            cout << "\n\t\t\tENTER CORRECT GENDER\n";
        }
    } while (p.gender != 'M' && p.gender != 'F');


    cout << "\n\t\t\tAGE: ";
    cin >> p.age;

    cin.ignore();
    cout << "\n\t\t\tAddress: ";
    cin.getline(p.address, 100);
    p.address[0] = toupper(p.address[0]);

    cout << "\n\t\t\tContact No.: ";
    cin >> p.contact_no;

    cin.ignore();
    cout << "\n\t\t\tEmail Address: ";
    cin.getline(p.email, 50);

    cout << "\n\t\t\tDoctor: ";
    cin.getline(p.doctor, 20);

    cout << "\n\t\t\tHealth Issue Details: ";
    cin.getline(p.problem, 50);

    fp.write(reinterpret_cast<char*>(&p), sizeof(struct patient));
    cout << "\n\t\t\tDATA WRITTEN SUCCESSFULLY\n";

    fp.close();
    cin.ignore();
    cout << "\n\n\n\t\t\tDO YOU WANT TO ADD MORE DATA[Y/N]\n";
    char choice;

    cin >> choice;
    choice = toupper(choice);
    if (choice == 'Y') {
        Add_rec();
    }
    cout << "\n\t\t\tTHANK YOU\n";
}

void func_list() {
    system("cls");
    Title();

    ifstream fp("patients.dat", ios::binary);
    cout << "\n\n\t\t\tListing Patients Records\n";
    gotoxy(1, 15);
    cout << "Full Name";
    gotoxy(25, 15);
    cout << "Gender";
    gotoxy(32, 15);
    cout << "Age";
    gotoxy(45, 15);
    cout << "Address";
    gotoxy(59, 15);
    cout << "Contact No.";
    gotoxy(74, 15);
    cout << "Email";
    gotoxy(88, 15);
    cout << "Issue";
    gotoxy(108, 15);
    cout << "Doctor\n";
    cout << "-----------------------------------------------------------------------------------------------------------------------";

    int row = 17;

    struct patient* pat = new struct patient;
    while (fp.read(reinterpret_cast<char*>(pat), sizeof(struct patient))) {
        gotoxy(1, row);
        cout << pat->first_name << " " << pat->last_name;

        gotoxy(25, row);
        cout << pat->gender;

        gotoxy(32, row);
        cout << pat->age;

        gotoxy(45, row);
        cout << pat->address;

        gotoxy(59, row);
        cout << pat->contact_no;

        gotoxy(74, row);
        cout << pat->email;

        gotoxy(98, row);
        cout << pat->problem;

        gotoxy(110, row);
        cout << pat->doctor;

        row++;
    }
    fp.close();
    cin.ignore();
    cout << "\nPress Enter to go back to the Main Menu.";
    cin.get();
    MainMenu();
}

void Search_rec() {
    system("cls");
    Title();

    ifstream fp("patients.dat", ios::binary);
    cout << "\n\n\t\t\tEnter the contact number of the record to be searched\n";

    string number;
    cin >> number;

    struct patient* pat = new struct patient;
    bool found = false;
    while (fp.read(reinterpret_cast<char*>(pat), sizeof(struct patient))) {
        if (strcmp(pat->contact_no, number.c_str()) == 0) {
            cout << "\n\n\t\t\tRECORD FOUND\n";
            found = true;
            cout << "\n\t\t\tNAME: " << pat->first_name << " " << pat->last_name << "\n";
            cout << "\n\t\t\tAGE: " << pat->age << "\n";
            cout << "\n\t\t\tGENDER: " << pat->gender << "\n";
            cout << "\n\t\t\tCONTACT NUMBER: " << pat->contact_no << "\n";
            cout << "\n\t\t\tEMAIL: " << pat->email << "\n";
            cout << "\n\t\t\tPROBLEM: " << pat->problem << "\n";
            cout << "\n\t\t\tDOCTOR: " << pat->doctor << "\n";
            break;
        }
    }
    if (!found) {
        cout << "\n\n\t\t\tSORRY!! NO RECORD FOUND\n";
    }
    fp.close();
    cin.ignore();
    cout << "\nPress Enter to go back to the Main Menu.";
    cin.get();
    MainMenu();
}

void Edit_rec() {
    system("cls");
    Title();

    ifstream fpr("patients.dat", ios::binary);
    ofstream fpw("temp.dat", ios::binary);
    cout << "\n\n\t\t\tEnter the contact number of the record to be edited\n";

    string number;
    cin >> number;

    struct patient* pat = new struct patient;
    bool found = false;
    while (fpr.read(reinterpret_cast<char*>(pat), sizeof(struct patient))) {
        if (strcmp(pat->contact_no, number.c_str()) == 0) {
            cout << "\n\n\t\t\tRECORD FOUND! ENTER NEW DETAILS\n";
            found = true;
            cout << "\n\t\t\tFIRST NAME: ";
            cin >> pat->first_name;
            cout << "\n\t\t\tLAST NAME: ";
            cin >> pat->last_name;
            cout << "\n\t\t\tAGE: ";
            cin >> pat->age;
            cout << "\n\t\t\tGENDER: ";
            cin >> pat->gender;
            cout << "\n\t\t\tCONTACT NUMBER: ";
            cin >> pat->contact_no;
            cout << "\n\t\t\tEMAIL: ";
            cin.ignore();
            cin.getline(pat->email, 50);
            cout << "\n\t\t\tPROBLEM: ";
            cin.getline(pat->problem, 50);
            cout << "\n\t\t\tDOCTOR: ";
            cin.getline(pat->doctor, 20);
        }
        fpw.write(reinterpret_cast<char*>(pat), sizeof(struct patient));
    }
    if (!found) {
        cout << "\n\n\t\t\tSORRY!! NO RECORD FOUND\n";
    }
    else {
        cout << "\n\n\t\t\tDATA SUCCESSFULLY EDITED\n";
    }
    fpr.close();
    fpw.close();
    remove("patients.dat");
    rename("temp.dat", "patients.dat");
    cin.ignore();
    cout << "\nPress Enter to go back to the Main Menu.";
    cin.get();
    MainMenu();
}

void Delete_rec() {
    system("cls");
    Title();

    ifstream fpr("patients.dat", ios::binary);
    ofstream fpw("temp.dat", ios::binary);
    cout << "\n\n\t\t\tEnter the contact number of the record to be deleted\n";

    string number;
    cin >> number;

    struct patient* pat = new struct patient;
    bool found = false;
    while (fpr.read(reinterpret_cast<char*>(pat), sizeof(struct patient))) {
        if (strcmp(pat->contact_no, number.c_str()) == 0) {
            found = true;
            continue;
        }
        fpw.write(reinterpret_cast<char*>(pat), sizeof(struct patient));
    }
    if (!found) {
        cout << "\n\n\t\t\tSORRY!! NO RECORD FOUND\n";
    }
    else {
        cout << "\n\n\t\t\tRECORD DELETED SUCCESSFULLY\n";
    }
    fpr.close();
    fpw.close();

    remove("patients.dat");
    rename("temp.dat", "patients.dat");
    cin.ignore();
    cout << "\nPress Enter to go back to the Main Menu.";
    cin.get();
    MainMenu();
}

void Exit_hospital() {
    system("cls");
    Title();
    cout << "\n\n\t\t\tTHANK YOU FOR USING THE HOSPITAL MANAGEMENT SYSTEM\n ";
    cout << "\n\n\t\t\tHAVE A GOOD DAY\n";
}
