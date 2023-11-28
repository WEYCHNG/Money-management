#include "Account.h"

using namespace std;

Account::Account()
{
	account_name = "";
	budget_amount = 0;
	balance = 0;
	start_date="";
	end_date="";
}

//done
void Account::addAccount() {
	
	DBConnection db;
	
	db.prepareStatement("Insert into account (UserID,account_name,budget_amount,balance,start_date,end_date) VALUES (?,?,?,?,?,?)");
	db.stmt->setString(1, UserID);//if your insert 
	db.stmt->setString(2, account_name);
	db.stmt->setDouble(3, budget_amount);
	db.stmt->setDouble(4, balance);
	db.stmt->setString(5, start_date);
	db.stmt->setString(6, end_date);
	db.QueryStatement();
	db.~DBConnection();

}

void Account::update() {

	DBConnection db;
	db.prepareStatement("UPDATE account SETaccount_name=?, budget_amount=?,balance=?, start_date=?, end_date=? WHERE AccountID=?");
	db.stmt->setString(1, account_name);
	db.stmt->setDouble(2, budget_amount);
	db.stmt->setDouble(3, balance);
	db.stmt->setString(4, start_date);
	db.stmt->setString(5, end_date);
	db.QueryStatement();
	db.~DBConnection();

}

void Account::removeAccount() {
	DBConnection db;
	db.prepareStatement("DELETE FROM account WHERE account_name=?");
	db.stmt->setString(1, account_name);
	db.QueryStatement();
	db.~DBConnection();
}

Account::Account(sql::ResultSet* data)
{

	UserID = data->getString("UserID");
	account_name = data->getString("account_name");
	budget_amount = data->getDouble("budget_amount");
	balance = data->getDouble("balance");
	start_date = data->getString("start_date");
	end_date = data->getString("end_date");
}


vector<Account> Account::findAccount(string userid, string keyword, string sortColumn, bool ascending) {

	
	string query = "SELECT account_name,budget_amount,balance,start_date,end_date FROM `account` WHERE "
		" (account_name LIKE ?) AND UserID=?"
		" ORDER BY "+sortColumn;
	

	if (ascending) {
		query += " ASC";
	}
	else {
		query += " DESC";
	}
	
	
	DBConnection db;
	db.prepareStatement(query);
	db.stmt->setString(1, "%" + keyword + "%");
	db.stmt->setString(2, userid);
	

	/*
	string query = "SELECT account_name,budget_amount,balance,start_date,end_date FROM `account` WHERE  UserID = ? ";
		
	DBConnection db;
	db.prepareStatement(query);
	db.stmt->setString(1, userid);
	*/
	vector<Account> accounts;

	db.QueryResult();

	if (db.res->rowsCount() > 0) {

		while (db.res->next()) {
			Account tmpProduct(db.res);
			accounts.push_back(tmpProduct);
		}
	}

	db.~DBConnection();
	return accounts;
}

/*
Account Account::ownAccount(int AccountID) {
	DBConnection db;
	db.prepareStatement("SELECT * FROM account WHERE AccountID=?");
	db.stmt->setInt(1,AccountID);
	db.QueryResult();

	Account result;
	if (db.res->rowsCount() == 1) {
		while (db.res->next()) {
			Account found(db.res);
			result = found;
		}
	}
	db.~DBConnection();
	return result;
}
*/


Account::~Account() {}
