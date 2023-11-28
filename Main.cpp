#include "User.h"
#include "Account.h"
#include "Menu.h"
#include"DBConnection.h"

#include <conio.h>//_getch()
#include <iomanip>//setw()
#include <ctime>//get time
#include <sstream>//set precision

#include <iostream>
using namespace std;

//getline(cin, keyWord);
void registerAccount();
void loginMenu();
void UserPage(User user);
User profile(User user);	

string formatAmount(double amount);//to correct into 2 d.p.

void AccountPage(Account account, User user);
//vector<Account> findAccount(string UserID, string account_name, double budget_amount, double balance, string start_date, string end_date);
void newAccount(User user);//Add account
//Account modifyAccount(Account account); //modify account

int main()
{

	Menu LoginPage;
	LoginPage.header = "Welcome to money world !!!";
	LoginPage.addOption("Register");
	LoginPage.addOption("Login");
	LoginPage.addOption("Exit");

	while (1) {
		switch (LoginPage.prompt())
		{
		case 1:
			registerAccount();
			break;
		case 2:
			loginMenu();
			break;
		case 3:
			return 0;
		default:
			break;
		}
	}
}

//LOGIN PAGE
//1)Register
void registerAccount() {
	User newacc;

	Menu cnMenu;
	cnMenu.header = "Registration";
	cout << endl;
	cnMenu.addOption("UserId");
	cnMenu.addOption("First Name");
	cnMenu.addOption("Last Name");
	cnMenu.addOption("Password");
	cnMenu.addOption("Email");
	cnMenu.addOption("Phone Number (01X-XXXXXXX)");
	cnMenu.addOption("Confirm");
	cnMenu.addOption("Back");

	string tmpinput;
	while (1) {

		switch (cnMenu.prompt()) {
		case 1:
			cout << "Insert UserId:";
			cin >> newacc.UserId;
			cnMenu.setValue(0, newacc.UserId);
			break;
		case 2:
			cout << "Insert First Name:";
			cin >> newacc.first_name;
			cnMenu.setValue(1, newacc.first_name);
			break;
		case 3:
			cout << "Insert Last Name:";
			cin >> newacc.last_name;
			cnMenu.setValue(2, newacc.last_name);
			break;
		case 4:
			cout << "Insert password:";
			cin >> tmpinput;
			if (tmpinput.length() < 6) {
				cout << "Password must be at least 6 character long";
				_getch();
			}
			else {
				newacc.password = tmpinput;
				cnMenu.setValue(3, newacc.password);
			}
			break;
		case 5:
			cout << "Insert email:";
			cin >> newacc.email;
			cnMenu.setValue(4, newacc.email);
			break;
		case 6:
			cout << "Insert Phone Number:";
			cin >> tmpinput;
			if (tmpinput.length() < 9)
			{
				cout << "Invalid ! ";
				_getch();
			}
			else
			{
				newacc.phone_number = tmpinput;
				cnMenu.setValue(5, newacc.phone_number);
			}
			break;
		case 7:
			newacc.insert();
			cout << "Register sucessfull !\n\n";
			return;
		case 8:
			return;
			break;
		default:
			break;
		}
	}

}

//2)Login
void loginMenu()
{
	Menu loginMenu;
	loginMenu.header = "LOGIN";
	loginMenu.addOption("UserId");
	loginMenu.addOption("Password");
	loginMenu.addOption("Confirm");
	loginMenu.addOption("Back");

	User user;

	while (1) {
		switch (loginMenu.prompt())
		{
		case 1:
			cout << "Insert UserId:";
			cin >> user.UserId;
			loginMenu.setValue(0, user.UserId);
			break;
		case 2:
			cout << "Insert Password:";
			cin >> user.password;
			loginMenu.setValue(1, user.password);
			break;
		case 3:
			if (user.login()) {
				UserPage(user);
			}
			else {
				cout << "Invalid Login";
				_getch();
			}
			break;
		case 4:
			return;
			break;
		default:
			break;
		}
	}
}

//USER PAGE
void UserPage(User user) 
{
	Account account;
	Menu homeMenu;
	homeMenu.addOption("Profile");
	homeMenu.addOption("Account");
	homeMenu.addOption("Transaction");
	homeMenu.addOption("Analysis and Report");
	homeMenu.addOption("Logout");
	while (1)
	{
		homeMenu.header = "Welcome " + user.UserId;
		switch (homeMenu.prompt())
		{
		case 1:
			user = profile(user);
			break;
		case 2:
			AccountPage(account,user);
		case 3:
		case 4:
		case 5:


			return;
			break;
		default:
			break;
		}
	}
}

//1)Profile
User profile(User user) {

	User temp = user; // copy the object

	Menu profileMenu;
	profileMenu.header = "Your profile";
	profileMenu.addOption("Fisrt Name");
	profileMenu.addOption("Last Name");
	profileMenu.addOption("Password");;
	profileMenu.addOption("Phone Number (01X-XXXXXXX)");
	profileMenu.addOption("Reset");
	profileMenu.addOption("Save");
	profileMenu.addOption("Back");
	profileMenu.addOption("Delete Account");

	string tmpInput;
	while (1) {
		profileMenu.setValue(0, temp.first_name);
		profileMenu.setValue(1, temp.last_name);
		profileMenu.setValue(2, temp.password);
		profileMenu.setValue(3, temp.phone_number);
		

		switch (profileMenu.prompt())
		{
		case 1:
			cout << "Insert First Name:";
			cin >> temp.first_name;
			break;
		case 2:
			cout << "Insert Last Name:";
			cin >> temp.last_name;
			break;
		case 3:
			cout << "Insert password:";
			cin >> temp.password;
			break;
		case 4:
			cout << "Insert Phone Number:";
			cin >> tmpInput;
			if (tmpInput.length() < 9)
			{
				cout << "Invalid ! ";
				_getch();
			}
			else
			{
				temp.phone_number = tmpInput;
			}
			break;
		case 5:
			temp = user;
			break;
		case 6:
			user = temp;
			user.update();
			cout << "Updated";
			_getch();
		case 7:
			return user;
			break;
		case 8:
			cout << "Delete your account? [Y/N]";
			char confirm;
			confirm = _getch();
			if (confirm == 'Y' || confirm == 'y') {
				user = temp;
				user.remove();
				main();
			}
			break;
		default:
			break;
		}
	}
}

//ACCOUNT PAGE
void AccountPage(Account account,User user)
{
	vector<Account> accounts;
	string displayString = "";
	string keyWord = "";
	string sortColumn = "Account name";
	string userid="";
	bool ascending = true;

	Menu homeAccount;
	homeAccount.header = "Search Option";
	homeAccount.addOption("Keyword for search account name");
	homeAccount.addOption("Order By");
	homeAccount.addOption("Odering");
	homeAccount.addOption("Search Account / Wallet");
	homeAccount.addOption("Add account");
	homeAccount.addOption("Edit");
	homeAccount.addOption("Back to User Page");

	
	Menu sortingSubMenu;
	sortingSubMenu.header = "Select Sort category";
	sortingSubMenu.addOption("Account name");
	sortingSubMenu.addOption("Balance");
	sortingSubMenu.addOption("Budget Amount");
	

	while (1)
	{
		
		homeAccount.setValue(1, sortColumn);
		if (ascending) {
			homeAccount.setValue(2, "Ascending");
		}
		else {
			homeAccount.setValue(2, "Descending");
		}
		

		if (displayString == "") {
			displayString = "\nSearch Result:\n";
			stringstream tmpString;
			tmpString << fixed << setprecision(2) << setw(5) <<"UserID"<< "Account Name" << "|" << setw(20) << "Budget amount"
				<< "|" << setw(10) << "Balance" << "|" << setw(20) << "Start date" << "|" << setw(20) << "End date" <<  "|"<< endl;

			for (int i = 0; i < accounts.size(); i++) {
				tmpString << setw(5) <<accounts[i].UserID<< accounts[i].account_name << "|" << setw(20) << accounts[i].budget_amount
					<< "|" << setw(10) << accounts[i].balance << "|" << setw(20) << accounts[i].start_date 
					<< "|" << setw(20) << accounts[i].end_date<<"|" << endl;
			}
			displayString += tmpString.str();
		}

		homeAccount.header = "Accounts";
		switch (homeAccount.prompt())
		{
		case 1:
			cout << "Please enter the keyword: ";
			getline(cin, keyWord);
			homeAccount.setValue(0, keyWord);
			break;
			
		case 2:
			
			switch (sortingSubMenu.prompt())
			{
			case 1:
				sortColumn = "Account name";
				break;
			case 2:
				sortColumn = "Balance";
				break;
			case 3:
				sortColumn = "Budget amount";
				break;

			}
			break;
			
		case 3:
			ascending = !ascending;
		case 4:
			accounts = Account::findAccount(userid,keyWord, sortColumn, ascending);
			displayString = "";
			break;
		case 5:
			newAccount(user);
		case 6:
			return;
			break;
		default:
			break;
		}
	}
}
/*
void doctorlist(Accounts adl, Patients pdl) {
	vector<Doctors> Doctors;
	string displayString = "", keyWord = "", sortColumn = "DoctorID";
	int DepartmentID = -1;  //?

	bool ascending = true;

	//Show the list at first encounter
	Doctors = Doctors::getdlist(keyWord, sortColumn, ascending);

	//Doctor List Menu
	Menu DLM;
	DLM.header = "Search Option";
	DLM.addOption("->> Keyword");
	DLM.addOption("->> Sort By");
	DLM.addOption("->> Ordering");
	DLM.addOption("->> Search/Refresh");
	DLM.addOption("->> Select");
	DLM.addOption("->> Back");

	//DoctorSortingSubMenu
	Menu DSSM;
	DSSM.header = "Choose the column that will be used to sort the list: \n";
	DSSM.addOption("->> Name");
	DSSM.addOption("->> Specialization");
	DSSM.addOption("->> DepartmentID");
	DSSM.addOption("->> DoctorID");

	while (1)
	{
		//Timer::getInstance().startTimer(60, std::bind(patientnotificationchecker, adl, pdl));
		//Timer::getInstance().startTimer(60, [adl, pdl]() { patientnotificationchecker(adl, pdl); });
		//patientnotificationchecker(adl, pdl);
		DLM.setValue(1, sortColumn);
		if (ascending) {
			DLM.setValue(2, "Ascending");
		}
		else {
			DLM.setValue(2, "Descending");
		}

		if (displayString == "") {
			displayString = "\nSearch Result: \n\n";
			stringstream tmpString;
			tmpString << fixed << setprecision(2) << setw(5) << "DoctorID" << "|" << setw(10) << "Name"
				<< "|" << setw(15) << "TelephoneNo" << "|" << setw(20) << "Specialization" << "|" << setw(20) << "DepartmentID" << "|" << endl;

			for (int i = 0; i < Doctors.size(); i++) {
				tmpString << setw(8) << Doctors[i].DoctorID << "|" << setw(10) << Doctors[i].DName
					<< "|" << setw(15) << Doctors[i].DTelephoneNo << "|" << setw(20) << Doctors[i].Specialization << "|" << setw(20)
					<< Doctors[i].DepartmentID << "|" << endl;
			}
			displayString += tmpString.str();
		}
		DLM.footer = displayString;

		switch (DLM.prompt()) {

			/// the case will modify the variable used as parameter to call the search method
		case 1:
			cout << "Please enter the keyword: ";
			getline(cin, keyWord);
			DLM.setValue(0, keyWord);
			break;

		case 2:
			switch (DSSM.prompt())
			{
			case 1:
				sortColumn = "DName";
				break;
			case 2:
				sortColumn = "Specialization";
				break;
			case 3:
				sortColumn = "DepartmentID";
				break;
			case 4:
				sortColumn = "DoctorID";
				break;
			}
			break;

		case 3:
			ascending = !ascending;
			break;

		case 4:
			Doctors = Doctors::getdlist(keyWord, sortColumn, ascending);
			displayString = "";
			break;

		case 5:
			cout << "Please enter the DoctorID you would like to schedule an appointment/ make a feedback with: ";
			cin >> doctorselected;
			return;
			break;

		case 6:
			return;
			break;
		default:
			break;
		}
	};
}*/

//convert amount to 2 decimal places
string formatAmount(double amount) {
	std::ostringstream formattedStream;
	formattedStream << "RM " << std::fixed << std::setprecision(2) << amount; // Format with 2 decimal places
	return formattedStream.str(); // Return the formatted string
}

void newAccount(User user) 
{
	Account addAccount;
	Menu accountMenu;
	accountMenu.header = "Add Account";
	accountMenu.addOption("Account Name");
	accountMenu.addOption("Budget Amount");
	accountMenu.addOption("Balance ");;
	accountMenu.addOption("Start Date");
	accountMenu.addOption("End Date");
	accountMenu.addOption("Confirm");
	accountMenu.addOption("Back");

	string month;
	string tmpinput;
	string formattedBudget;
	string formattedBalance;

	time_t current = time(0); // get time in epoch seconds (since 1900)
	tm now; // create a struct/object of tm to hold data
	localtime_s(&now, &current); //populate the now object with data from current

	

	while (1) {
		
		switch (accountMenu.prompt())
		{
		case 1:
			cout << "Eneter account name (Example: RHB Bank): ";
			cin >> addAccount.account_name;
			accountMenu.setValue(0, addAccount.account_name);
			break;
		case 2:
			cout << "Enter budget amount: RM ";
			cin >> addAccount.budget_amount;

			// Format the budget amount using formatAmount function
			formattedBudget = formatAmount(addAccount.budget_amount);

			// Set the formatted string to the menu value
			accountMenu.setValue(1, formattedBudget);
			break;
		case 3:
			cout << "Enter account balance: RM ";
			cin >> addAccount.balance;
			
			// Format the balance amount using formatAmount function
			formattedBalance = formatAmount(addAccount.balance);

			// Set the formatted string to the menu value
			accountMenu.setValue(2, formattedBalance);
			break;
		case 4:
			cout << "Enter fisrt 3 letter abbreviation of month for set budget amount (Example: Jan,Feb): ";
			cin >> month;
			if (month == "Jan" || month == "Mar" || month == "May" || month == "Jul" || month == "Aug" || month == "Oct" || month == "Dec")
			{
				addAccount.start_date = "01-" + month + "-" + to_string(now.tm_year + 1900);
				accountMenu.setValue(3,addAccount.start_date);
				addAccount.end_date = "31-" + month + "-" + to_string(now.tm_year + 1900);
				accountMenu.setValue(4, addAccount.end_date);
			}
			else if (month == "Apr" || month == "Jun" || month == "Sep" || month == "Nov")
			{
				addAccount.start_date = "01-" + month + "-" + to_string(now.tm_year + 1900);
				accountMenu.setValue(3, addAccount.start_date);
				addAccount.end_date = "30-" + month + "-" + to_string(now.tm_year + 1900);
				accountMenu.setValue(4, addAccount.end_date);
			}
			else if (month == "Feb")
			{
				// leap year if perfectly divisible by 400
				if ((now.tm_year + 1900) % 400 == 0)
				{
					addAccount.start_date = "01-" + month + "-" + to_string(now.tm_year + 1900);
					accountMenu.setValue(3, addAccount.start_date);
					addAccount.end_date = "29-" + month + "-" + to_string(now.tm_year + 1900);
					accountMenu.setValue(4, addAccount.end_date);
				}
				// not a leap year if divisible by 100
				// but not divisible by 400
				else if ((now.tm_year + 1900) % 100 == 0)
				{
					addAccount.start_date = "01-" + month + "-" + to_string(now.tm_year + 1900);
					accountMenu.setValue(3, addAccount.start_date);
					addAccount.end_date = "28-" + month + "-" + to_string(now.tm_year + 1900);
					accountMenu.setValue(4, addAccount.end_date);
				}
				// leap year if not divisible by 100
				// but divisible by 4
				else if ((now.tm_year + 1900) % 4 == 0)
				{
					addAccount.start_date = "01-" + month + "-" + to_string(now.tm_year + 1900);
					accountMenu.setValue(3, addAccount.start_date);
					addAccount.end_date = "29-" + month + "-" + to_string(now.tm_year + 1900);
					accountMenu.setValue(4, addAccount.end_date);
				}
				// all other years are not leap years
				else 
				{
					addAccount.start_date = "01-" + month + "-" + to_string(now.tm_year + 1900);
					accountMenu.setValue(3, addAccount.start_date);
					addAccount.end_date = "28-" + month + "-" + to_string(now.tm_year + 1900);
					accountMenu.setValue(4, addAccount.end_date);
				}
			}
			else
			{
				cout<<"Invlaid input";
			}
			break;
		case 5:
			break;
		case 6:
			addAccount.UserID = user.UserId;
			addAccount.addAccount();
			cout << "Add sucessful !";
			break;
		case 7:
			//return account;//create account page
			return;
			break;
		default:
			break;
		}
		
	}
}


