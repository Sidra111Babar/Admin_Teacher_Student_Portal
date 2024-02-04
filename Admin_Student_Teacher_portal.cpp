#include <iostream>
#include <string>       
#include <fstream>       
#include <Windows.h>    
#include <MMsystem.h>
#include "MMsystem.h"     

using namespace std;
class Student{
	protected:
		string name;
		string id;
		string password;
		string contact_No;
		string gmail;
		string address;				
		string department;
		string degree_program;
		string course[5];
		double fee;
		double Intermarks; 
	public:
		// first four functions are for admin menu
		void add_student();
		void student_details();
		void student_search(string &searching_id);
		void delete_student(string &user_id);
		// view option of fee chalan is for student menu
		void generate_fee_challan(string &user_id,string &user_password);
		void student_login(string &user_id,string &user_password);
};
class Teacher : public Student{
    private:
        string t_name;
        string t_id;
        string t_password;
        string t_contact_No;
        string t_gmail;
        string t_address;
        string t_department;
        string t_degree_program;
        string t_course;
        double student_marks[5];
    public:
    	// first four functions are for admin Menu
        void add_teacher();
        void teacher_details();
        void teacher_search(string &searching_id);
        void delete_teacher(string &user_id);
        void teacher_login(string &user_id,string user_password);
        // For teacher menu
        void assign_marks(string &searching_id);
        // View_marks for student menu
        void view_marks(string &searching_id, string  &user_password);
};

void Teacher::view_marks(string &searching_id, string  &user_password)
{
    system("cls");
    fstream file;
    int found = 0;
    file.open("Added_Students_Details.txt", ios::in);

    if (!file)
    {
        cerr << "File is Empty " << endl;
    }
    else
    {
        
        cout << "Enter your ID : ";
        cin >> searching_id;
        cout << "Enter Your Password : ";
        cin >> user_password;

        while (getline(file, name) && getline(file, id) &&
               getline(file, password) && getline(file, contact_No) &&
               getline(file, gmail) && getline(file, address) && file >> Intermarks >> ws && file >> fee >> ws &&
               getline(file, department) && getline(file, degree_program) &&
               getline(file, course[0]) && getline(file, course[1]) &&
               getline(file, course[2]) && getline(file, course[3]) &&
               getline(file, course[4]))
        {
            if (searching_id == id && user_password == password)
            {
                cout << "Your marks and name for student ID " << id << " are " << name << endl;
                found++;
                break; 
            }
        }

        if (found == 0)
        {
            cout << "Student not found or incorrect password" << endl;
        }

        file.close();
    }
}


void Teacher::assign_marks(string &searching_id)
{
    system("cls");
    fstream file;
    int found = 0;
    file.open("Added_Students_Details.txt", ios::in);

    if (!file)
    {
        cerr << "File is Empty " << endl;
    }
    else
    {
        
        cout << "Enter ID of student you want to assign marks (start from student 1 and go in sequence) ";
        cin >> searching_id;

        ofstream tempFile("temp.txt"); 

        while (getline(file, name) && getline(file, id) &&
               getline(file, password) && getline(file, contact_No) &&
               getline(file, gmail) && getline(file, address) && file >> Intermarks >> ws && file >> fee >> ws &&
               getline(file, department) && getline(file, degree_program) &&
               getline(file, course[0]) && getline(file, course[1]) &&
               getline(file, course[2]) && getline(file, course[3]) &&
               getline(file, course[4]))
        {
            if (searching_id == id)
            {
                cout << "Enter marks of the student with id " << id << " and name " << name << endl;

                for (int i = 0; i < 5; i++)
                {
                    cout << "Enter marks in subject " << course[i] << " : ";
                    cin >> student_marks[i];
                    tempFile << student_marks[i] << " "; 
                }

                found++;
            }

            
            tempFile << name << "\n" << id << "\n" << password << "\n"
                     << contact_No << "\n" << gmail << "\n" << address << "\n"
                     << Intermarks << " " << fee << "\n" << department << "\n"
                     << degree_program << "\n" << course[0] << "\n"
                     << course[1] << "\n" << course[2] << "\n"
                     << course[3] << "\n" << course[4] << "\n";
        }

        if (found == 0)
        {
            cout << "Student not found!" << endl;
        }

        file.close();
        tempFile.close();

        remove("Added_Students_Details.txt");
        rename("temp.txt", "Added_Students_Details.txt");
    }
}




void fee_calculator(double marks, double& fee) {
    if (marks >= 1050 && marks <= 1100) {
        fee = 50000;
    } else if (marks >= 1000 && marks <= 1049) {
        fee = 55000;
    } else if (marks >= 900 && marks <= 999) {
        fee = 60000;
    } else {
        fee = 65000;
    }
}
void Student::add_student() {
    
    system("cls");
    fstream file;
    cout << "--------------------------Enter Student Details----------------------" << endl;
    cout << "                          Enter ID : ";
    cin >> id;
    cin.ignore();
    cout << "                          Enter Name : ";
    getline(cin, name);
   
    cout << "                          Enter Password : ";
    cin >> password;
   
    cout << "                          Enter Contact No : ";
    cin >> contact_No;

    

    cout << "                          Enter Gmail : ";
    cin >> gmail;
    cin.ignore();
    cout << "                          Enter Address : ";
    getline(cin, address);

    cout << "                          Enter Inter-Marks : ";
    cin >> Intermarks;
    fee_calculator(Intermarks,this->fee);
    cin.ignore(); 

    cout << "                          Enter Department : ";
    getline(cin, department);

    cout << "                          Enter Degree Program : ";
    getline(cin, degree_program);

    for (int i = 0; i < 5; i++) {
        cout << "                          Enter Course " << i + 1 << ": ";
        getline(cin, course[i]);
    }


          file.open("Added_Students_Details.txt",ios::app | ios::out);
          if(!file)
		  {
          	cerr << "Error in file opening" << endl;
          	return;
		  }
		  file << name << endl << id << endl << password << endl << contact_No << endl << gmail << endl << address << endl << Intermarks << endl << fee << endl 
          << department << endl << degree_program << endl;
		  for (int i = 0; i < 5; i++)
		  {
		  	file << course[i] << endl;
		  }
		  file.close();
}
void Student::student_details(){
	    system("cls");
	    fstream file; 
	    int studentCount = 0;
	    cout << "               --------------------------Student Details---------------------" << endl;
	    file.open("Added_Students_Details.txt",ios::in);
	    if(!file)
		{
   	        cerr << "Error opening file for reading " << endl;
   	        return;
        }	
      
	    while(getline(file,name) && getline(file,id) && 
	    getline(file,password) && getline(file,contact_No) && 
	    getline(file,gmail) && getline(file,address) && file >> Intermarks >> ws && file >> fee >> ws &&
	    getline(file,department) && getline(file,degree_program) && getline(file, course[0]) &&
        getline(file, course[1]) && getline(file, course[2]) && getline(file, course[3]) && getline(file, course[4]))
	  
	  
	   {
        cout << "                                Student No. : " << studentCount++ << " Details " << endl;
        cout << "                                Student data : " << name                         << endl;
        cout << "                                Student ID : " << id                             << endl;
        cout << "                                Student Password. : " << password                << endl;
        cout << "                                Student Contact No : " << contact_No             << endl;
        cout << "                                Student Gmail : " << gmail                       << endl;
        cout << "                                Student Address : " << address                   << endl;
        cout << "                                Student  Inter_Marks : " << Intermarks           << endl;
        cout << "                                Student Fee : " << fee                           << endl;
        cout << "                                Student Department : " << department             << endl;
        cout << "                                Student Degree Program : " << degree_program     << endl;

      
      for(int i = 0; i < 5; i++)
	  {
        cout << "                                Student Course : " << i+1 << " : " << course[i] << endl;
      }
       studentCount++;
	}
	
	if(studentCount == 0)
	    {
	    	cout << "                                 File is Empty" << endl;
	    }
    	file.close();
  }	  
void Student::student_search(string &searching_id) {
    system("cls");
    fstream file;
    int found = 0;
    file.open("Added_Students_Details.txt", ios::in);
    if (!file) 
	{
        cerr << "File is Empty " << endl;
    } 
	else 
	{
        
        cout << "Enter ID of student you want to search: ";
        cin >> searching_id;

        while(getline(file, name) && getline(file, id) &&
        getline(file, password) && getline(file, contact_No) &&
        getline(file, gmail) && getline(file, address) && file >> Intermarks >> ws && file >> fee >> ws &&
        getline(file, department) && getline(file, degree_program) &&
        getline(file, course[0]) && getline(file, course[1]) 
		&& getline(file, course[2])&& getline(file, course[3])
		&& getline(file, course[4])){
		

            if (searching_id == id) {
                cout << "Student Found!" << endl;
                cout << "Student Name: " << name << endl;
                cout << "Student ID: " << id << endl;
                cout << "Student Password: " << password << endl;
                cout << "Student Contact No: " << contact_No << endl;
                cout << "Student Gmail: " << gmail << endl;
                cout << "Student Address: " << address << endl;
                cout << "Student Inter_Marks: " << Intermarks << endl;
                cout << "Student  Fee : " << fee << endl;
                
                cout << "Student Department: " << department << endl;
                cout << "Student Degree Program: " << degree_program << endl;
                for (int i = 0; i < 5; i++) {
                    cout << "Student Course " << i + 1 << " : " << course[i] << endl;
                    
                }
                found++;
                break; 
            }
        }
    }
        if (found == 0) {
            cout << "Student not found!" << endl;
        }
        file.close();
}
void Student::delete_student(string &user_id) {
    system("cls");
    fstream file, file1;
    
    int found = 0;
    
    cout << "-----------------------Deleted Student-----------------" << endl;
    
    file.open("Added_Students_Details.txt", ios::in);
    
    if (!file) {
        cout << "-----------------File is empty" << endl;
    } else {
        cout << " Enter ID of the Student which you want to delete: ";
        cin >> user_id;
        
        file1.open("student_detail.txt", ios::app | ios::out);

        while (!file.eof()) {
            getline(file, name);
            getline(file, id);
            getline(file, password);
            getline(file, contact_No);
            getline(file, gmail);
            getline(file, address);
            file >> Intermarks;
            file >> fee;
            file.ignore();
            getline(file, department);
            getline(file, degree_program);
            
            for (int i = 0; i < 5; i++) 
			{
                getline(file, course[i]);
            }

            if (id != user_id) 
			{
                file1 << name << endl << id << endl << password << endl << contact_No << endl << gmail << endl
                << address << endl << Intermarks << endl << fee << endl << department << endl << degree_program << endl;
                for (int i = 0; i < 5; i++) {
                    file1 << course[i] << endl;
                }
            } 
			else 
		     	{
                  found = 1;
                }
        }

        if (found == 0) {
            cout << "Student not found";
        }

        file1.close();
        file.close();
        remove("Added_Students_Details.txt");
        rename("student_detail.txt", "Added_Students_Details.txt");
    }
}
void Student::student_login(string &user_id,string &user_password) {
    
    
    fstream file;
    file.open("Added_Students_Details.txt", ios::in);

    if (file.peek() == ifstream::traits_type::eof()) {
        cout << "-----------------File is empty" << endl;
    } else {
        cout << "               Enter ID : ";
        cin >> user_id;
        cout << "               Enter password : ";
        cin >> user_password;

        bool found = false;

        while (getline(file, name) && getline(file, id) &&
               getline(file, password) && getline(file, contact_No) &&
               getline(file, gmail) && getline(file, address) && file >> Intermarks >> ws && file >> fee >> ws &&
               getline(file, department) && getline(file, degree_program) &&
               getline(file, course[0]) && getline(file, course[1]) &&
			   getline(file, course[2]) && getline(file, course[3]) && getline(file, course[4])) {
            if ((user_id == id) && (user_password == password))
			{
                found = true;
                break; 
            }
        }

        file.close();

        if (found) {
            cout << "Successfully Login!" << endl;
        } else {
            cout << "Invalid ID or Password" << endl;
            exit(1);
        }
    }
}

void Student::generate_fee_challan(string &user_id,string &user_password)
  {
  	  system("cls");
      fstream file;
      int found = 0;
      file.open("Added_Students_Details.txt", ios::in);
      if (!file) 
	  {
        cerr << "File is Empty " << endl;
      }
	 else {
        
        
        cout << "                          Enter your ID : ";
        cin >> user_id;
        cout << "                          Enter your Password : ";
        cin >> user_password;
        string vouchercode = "11483";
        while (getline(file, name) && getline(file, id) &&
        getline(file, password) && getline(file, contact_No) &&
        getline(file, gmail) && getline(file, address) && file >> Intermarks >> ws && file >> fee >> ws &&
        getline(file, department) && getline(file, degree_program) &&
        getline(file, course[0]) && getline(file, course[1]) &&
		getline(file, course[2])&& getline(file, course[3])&& getline(file, course[4])){
		

            if (user_id == id && user_password == password) {
            
            	
  	    cout << "******************************** FEE CHALAN **************************************************" << endl;
  	    cout << endl << endl << endl << endl; 
  	    cout << "          _____________________________________________________________________"<< endl;
        cout << "          |                   Bank Copy                                        |"<< endl;
	    cout << "          |                                                                    |" << endl;
	    cout << "          |         Uiversity of Management and Technology                     |"<<endl;
	    cout << "          |       C-11, Johar Town Lahore U.A.N: +92 42 111 300 200            |"<< endl;
	    cout << "          |                   Student Fee Voucher                              |"<< endl;
    	cout << "          |                                                                    |" << endl; 
	    cout << "          |                     Meezan Bank                                    |"<< endl;
	    cout << "          |                     A/c Code: UNIMT                                |"<< endl;
	    cout << "          |                     Allied Bank Limited                            |"<< endl;
	    cout << "          |                    Due:Date:   5-Dec-2023                          |"<< endl;
	    cout << "          ---------------------------------------------------------------------" << endl;
	    cout << "          |____________________________________________________________________|" << endl;
	    cout << "          |  Student ID: " << id << "    Voucher code : " << vouchercode << "               |" << endl;
	    cout << "          |                                                                    |"<< endl;
	    cout << "          | Name:    " << name << "                                            |" << endl;
	    cout << "          |                                                                    |" << endl;
	    cout << "          | Program: " << degree_program <<"                                                 |" << endl;
	    cout << "          |                                                                    |" << endl;
	    cout << "          ----------------------------------------------------------------------" << endl;
	    cout << "          |_____________________________________________________________________|" << endl;
	    cout << "          |    |Particulars                    |               Amount           |" << endl;
	    cout << "          -----------------------------------------------------------------------" << endl;
	    cout << "          | 1  |Tutition Fee:                  |               " << fee << "    |" << endl;
	    cout << "          |---------------------------------------------------------------------|" << endl;
	    cout << "          |             Total                  |               " << fee << "    |" <<endl;
	    cout << "          -----------------------------------------------------------------------"  << endl;
	    cout << "          |______________________________________________________________________|" << endl;
	    cout << "          | Issued By: Portal Service                        Bank Stamp Sign     |" << endl;
	    cout << "          |                                                                      |" << endl;
	    cout << "          |Note:                                                                 |" << endl;
	    cout << "          |           *  Contribution for ILM Fund Scholarship of PKR 3,000      |" << endl;
	    cout << "          |          + PKR 100 per day will be applicable after the due date     |" << endl;
	    cout << "          |            as per original voucher                                   |" << endl;
	    cout << "          |                                                                      |" << endl;
	    cout << "          |           * Voucher can be paid in any Meezan Bank\Allied Bank        |" << endl;
	    cout << "          |______________________________________________________________________|" << endl;
	  	    found++;
            break; 
     } 
   }
}
     if (found == 0) {
            cout << "Student not found!" << endl;
        }
        file.close();
	 
   
}
void Teacher::add_teacher() {
    system("cls");
    fstream file;
    cout << "--------------------------Enter Teacher Details----------------------" << endl;
    cout << "                          Enter ID : ";
    cin >> t_id;
    cin.ignore();
    cout << "                          Enter Name : ";
    getline(cin, t_name);
    cout << "                          Enter Password : ";
    cin >> t_password;
    cout << "                          Enter Contact No : ";
    cin >> t_contact_No;
    cout << "                          Enter Gmail : ";
    cin >> t_gmail;
    cin.ignore();
    cout << "                          Enter Address : ";
    getline(cin, t_address); 
    cout << "                          Enter Department : ";
    getline(cin, t_department);
    cout << "                          Enter Degree Program : ";
    getline(cin, t_degree_program);
        cout << "                      Enter Section : ";
        getline(cin, t_course);
            file.open("Teacher_check.txt",ios::app | ios::out);
            if(!file)
		       {
          	        cerr << "Error in file opening" << endl;
          	        return;
		       }
		    file << t_name << endl << t_id << endl << t_password << endl
		    << t_contact_No << endl << t_gmail << endl << t_address << endl 
            << t_department << endl << t_degree_program << endl << t_course << endl;
		    file.close();
}

void Teacher::teacher_details() {
    system("cls");
	  fstream file;
	  int teacherCount = 0;
	  cout << "               --------------------------Teacher Details---------------------" << endl;
	  file.open("Teacher_check.txt",ios::in);
	  if(!file)
	    {
   	     cerr << "Error opening file for reading " << endl;
   	     return;
        }	
      
	  while(getline(file,t_name) && getline(file,t_id) && 
	  getline(file,t_password) && getline(file,t_contact_No) && 
	  getline(file,t_gmail) && getline(file,t_address) &&
	  getline(file,t_department) && getline(file,t_degree_program)
	  && getline(file, t_course))
	  
	    {
            cout << "                                Teacher No. : " << teacherCount++ << " Details " << endl;
            cout << "                                Teacher Name : " << t_name                         << endl;
            cout << "                                Teacher ID : " << t_id                             << endl;
            cout << "                                Teacher Password. : " << t_password                << endl;
            cout << "                                Teacher Contact No : " << t_contact_No             << endl;
            cout << "                                Teacher Gmail : " << t_gmail                       << endl;
            cout << "                                Teacher Address : " << t_address                   << endl;
            cout << "                                Teacher Department : " << t_department             << endl;
            cout << "                                Teacher Degree Program : " << t_degree_program     << endl;
            cout << "                                Teacher Course : " << t_course << endl;
        teacherCount++;
	  }
	
	if(teacherCount == 0)
	    {
		   cout << "                                 File is Empty" << endl;
	    }
    	file.close();
}
void Teacher::teacher_search(string &searching_id) {
      system("cls");
    fstream file;
    int found = 0;
    file.open("Teacher_check.txt", ios::in);
    if (!file)
	   {
          cerr << "File is Empty " << endl;
       } 
	    else
		{
            
            cout << "Enter ID of teacher you want to search: ";
            cin >> searching_id;

        while (getline(file, t_name) && getline(file, t_id) &&
        getline(file, t_password) && getline(file, t_contact_No) &&
        getline(file, t_gmail) && getline(file, t_address) &&
        getline(file, t_department) && getline(file, t_degree_program) &&
        getline(file, t_course))
		{
            if (searching_id == t_id) {
                cout << "Teacher Found!" << endl;
                cout << "Teacher Name: " << t_name << endl;
                cout << "Teacher ID: " << t_id << endl;
                cout << "Teacher Password: " << t_password << endl;
                cout << "Teacher Contact No: " << t_contact_No << endl;
                cout << "Teacher Gmail: " << t_gmail << endl;
                cout << "Teacher Address: " << t_address << endl;
                cout << "Teacher Department: " << t_department << endl;
                cout << "Teacher Degree Program: " << t_degree_program << endl;
                cout << "Teacher Course : " << t_course << endl;
                found++;
                break;  
            }
        }
    }
        if (found == 0) {
            cout << "Teacher not found!" << endl;
        }
        file.close();    
}

void Teacher::delete_teacher(string &user_id){
	
	system("cls");
    fstream file, file1;
    
    int found = 0;
    
    cout << "-----------------------Deleted Teacher-----------------" << endl;
    
    file.open("Teacher_check.txt", ios::in);
    
    if (!file) 
    	{
          cout << "-----------------File is empty" << endl;
        } 
	else 
	   {
        cout << " Enter ID of the Teacher which you want to delete: ";
        cin >> user_id;
        
        file1.open("teacher_detail.txt", ios::app | ios::out);

        while (!file.eof()) {
            getline(file, t_name);
            getline(file, t_id);
            getline(file, t_password);
            getline(file, t_contact_No);
            getline(file, t_gmail);
            getline(file, t_address);
            getline(file, t_department);
            getline(file, t_degree_program);
            getline(file, t_course);
            if (t_id != user_id) 
		     	{
                    file1 << t_name << endl << t_id << endl << t_password << endl << t_contact_No << endl << t_gmail << endl
                    << t_address << endl << t_department << endl << t_degree_program << endl << t_course << endl;
                
                }
			 else 
			   {
                 found = 1;
               }
        }

        if (found == 0) 
		{
            cout << "Teacher not found";
        }

        file1.close();
        file.close();
        remove("Teacher_check.txt");
        rename("teacher_detail.txt", "Teacher_check.txt");
    }
}

void Teacher::teacher_login(string &user_id,string user_password){
    	
        
        fstream file;
        file.open("Teacher_check.txt", ios::in);
        if (file.peek() == ifstream::traits_type::eof())
		 {
            cout << "-----------------File is empty" << endl;
         } 
	else 
	{
        cout << "                  Enter ID : ";
        cin >> user_id;
        cout << "                  Enter password : ";
        cin >> user_password;

        bool found = false;

        while (getline(file, t_name) && getline(file, t_id) &&
               getline(file, t_password) && getline(file, t_contact_No) &&
               getline(file, t_gmail) && getline(file, t_address) &&
               getline(file, t_department) && getline(file, t_degree_program) &&
               getline(file, t_course))
			    {
                  if ((user_id == t_id) && (user_password == t_password)) 
				  {
                    found = true;
                    break; // Exit the loop once a match is found
                  }    
                }

        file.close();

        if (found) {
            cout << "Successfully Login!" << endl;
        } else {
            cout << "Invalid ID or Password" << endl;
            exit(1);
        }
    }
	
}
void adminstrator_authentication() {
    string id;
    string password;  
    cout << "                 Enter ID : ";
    cin >> id;
    cout << "                 Enter Password : ";
    cin >> password;

    if (id == "S2023105007" && password == "Babar") {
        cout << "                     Login successfully!" << endl;
    } else {
        cout << "                     Invalid ID or Password. Try Again!   " << endl;
        exit(1);
    }
}

void welcome_Message(){
     // Sleep due to windows.h library
     
    Sleep(400);
    cout << "               ***************************************************************" << endl;
    Sleep(400);
    cout << "               |                     Welcome                                  |"<< endl;
    Sleep(400);
    cout << "               *                                                              *"<<endl;
    Sleep(400);
    cout << "               |                       To                                     |"<< endl;
    Sleep(400);
    cout << "               |                                                              |"<< endl;
    Sleep(400);
    cout << "               *                Student Teacher  Admin                        *"<< endl;
    Sleep(400);
    cout << "               |                                                              |"<< endl;
    Sleep(400);
    cout << "               *                     Portal                                   *"<< endl;
    Sleep(400);
    cout << "               ***************************************************************" << endl;
 } 


void welcome_menu(string &user_menu){
	cout << "                       *********************************************" << endl;
	Sleep(400);
	cout << "                       |                                           |" << endl;
	Sleep(400);
	cout << "                       *             Welcome      To               *" << endl;
	Sleep(400);
	cout << "                       |               " << user_menu << "                |" << endl;
	Sleep(400);
	cout << "                       *                                           *" << endl;
	Sleep(400);
	cout << "                       *********************************************" << endl;
}
void login_message(){
	cout << "               ***************************************" << endl;
    Sleep(400);
    cout << "               |                                     |" << endl;
    Sleep(400);
    cout << "                   |          Please Login        |"    << endl;
    Sleep(400);
    cout << "               |                                     |" << endl;
    Sleep(400);
    cout << "               ***************************************" << endl;
    Sleep(400);
}



void changeColor(WORD color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
int main() {
   	    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	   	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "                        |******************************************************|" << endl;
	Sleep(400);
	cout << "                        |                                                      |" << endl;
	Sleep(400);
	cout << "                        *                  Instructions                        |" << endl;
	Sleep(400);
	cout << "                        |                                                      |" << endl;
	Sleep(400);
	cout << "                        |                      To                              |" << endl;
	Sleep(400);
	cout << "                        *                                                      *" << endl;
	Sleep(400);
	cout << "                        |                  Run Program                         |" << endl;
	Sleep(400);
	cout << "                        |                                                      |" << endl;
	Sleep(400);
	cout << "                        |******************************************************|" << endl; 
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	Sleep(400);
	cout << "                              Ist Use Admin menu" << endl;
	cout << endl;
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
	Sleep(400);
	cout << "                             2ndly Use Student Menu to Generate fee chalan of student" << endl;
	cout << "                              (fee is scholarship based and depend upon intermarks)" << endl;
	cout << endl;
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
	Sleep(400);
	cout << "                             3rdly Use Teacher Menu to assign marks to student" << endl;
	cout << endl;
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN); 
	Sleep(400);  
	cout << "                             fourthly Use Student menu to view student marks" << endl;
	   Sleep(10000);
	   system("cls");
	   system("color cf");
	   PlaySound(TEXT("Welcome_msg"), NULL, SND_ASYNC);
	   welcome_Message();
       int choice;
       char a,b;
       int input;
       Teacher teacher;
       Student student;
       string admin_menu = "ADMIN MENU";
       string teacher_menu = "TEACHER MENU";
       string student_menu = "STUDENT MENU";
       string id;
       string password;

    do {
    	

        cout << "                                 Press 1 if you are Administrator" << endl;
        cout << "                                 Press 2 if you are Teacher"       << endl;
        cout << "                                 Press 3 if you are Student"       << endl;
        cin >> choice;

        switch (choice) {
        case 1:
        	 
             system("cls");
             system("color f0");
             login_message();
             adminstrator_authentication();
             
             system("cls");
             PlaySound(TEXT("Admin_Menu"), NULL, SND_ASYNC);
             welcome_menu(admin_menu);
            do {
                cout << "                         Press 1 to add Teacher"        << endl;
                cout << "                         Press 2 to View Teachers"      << endl;
                cout << "                         Press 3 to Search Teacher"     << endl;
                cout << "                         Press 4 to Delete Teacher"     << endl;
                cout << "                         Press 5 to add Student"        << endl;
                cout << "                         Press 6 to search Student"     << endl;
                cout << "                         Press 7 to View Students"      << endl;
                cout << "                         Press 8 to Delete Student"     << endl;
                cout << "                         Press 9 to go to main page"    << endl;
                cin >> input;

                switch (input) {
                case 1:
                	do
					{
                    teacher.add_teacher();
                    cout << "Do You want to add another record?(Y/N) : ";
                    cin >> b;
                    system("cls");
                    }while(b== 'Y' || b == 'y');
                    break;
                case 2:
                    teacher.teacher_details();
                    break;
                case 3:
                    teacher.teacher_search(id);
                    break;
                case 4:
                	teacher.delete_teacher(id);
                	break;
                case 5:
                    do 
					{
                        student.add_student();
                        cout << "Do You want to add another record? (Y/N) : ";
                        cin >> a;
                        system("cls");
                    }while (a == 'y' || a == 'Y');
                    break;
                case 6:
                     student.student_search(id);
                    break;
                case 7:
                    student.student_details();
                    break;
                case 8:
                	student.delete_student(id);
                	break;
                case 9:
                	break;
                	
                default:
                    cout << "Invalid input.Try Again!\n";
                    break;
                }
             } while(input !=9 );
        system("cls");
        break;
        case 2:
            system("cls");
            system("color B0");
            login_message();
            teacher.teacher_login(id,password);
            
            system("cls");
            PlaySound(TEXT("Teacher_Menu"), NULL, SND_ASYNC);
            welcome_menu(teacher_menu);
            do{
            	cout << "                     Press 1 if you want to assign marks to student" << endl;
            	cout << "                     Press 3 to go to main menu" << endl;
            	cin >> input;
            	switch(input)
				{
            	  case 1:
            	  	do
					  {	
					    system("cls");		  
            	  	    teacher.assign_marks(id);
            	  	    cout << "Do you want to assign again(y/n)";
            	  	    cin >> a;
            	        }while(a == 'y' || a == 'Y');
            	  	    break;
            	  	    case 2:
            	  		break;
            		
				}
			 }while(input != 3);
            
            
            break;
        case 3:
              system("cls");
              system("color E0");
              login_message();
              student.student_login(id,password);
              
              system("cls");
              PlaySound(TEXT("Student_Menu"), NULL, SND_ASYNC);
              welcome_menu(student_menu);
              do {
                   cout << "                      Press 1 if you want to generate Fee Challan" << endl;
                   cout << "                      Press 2 if you want to view your marks"      << endl;
                   cout << "                      Press 4 to go to the main menu"              << endl;
                   cout << "                      ";
                   cin >> input;

                   switch (input) 
				   {
                    case 1:
                    student.generate_fee_challan(id,password);
                    break;
                    case 2:
                    teacher.view_marks(id,password);
                    break;
                    case 4:
                    break;
                    default:
                    cout << "Invalid Input. Try Again!" << endl;
                    break;
                    }
                } while (input != 4);
                    break;
        default:
            cout << "Invalid Entry\n";
        }
    } while (choice != 4);

    return 0;
}
