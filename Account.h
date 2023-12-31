#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector> 
#include "DBConnection.h" 

using namespace std;
class Account
{
public:
	int AccountID;
	double budget_amount, balance;
	std::string UserID,account_name,start_date,end_date;
	

	Account(); // constructor method
	Account(sql::ResultSet* data);

	static vector<Account> findAccount(string userid, string keyword, string sortColumn,bool ascending);
	static vector<Account> selectAccount(string userid);
	bool confirmtoEdit();
	void addAccount();
	void update();
	void removeAccount();

	~Account();

	static Account ownAccount(int AccountID);


};

#endif




