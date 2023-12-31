#include "Transaction.h"
#include<string>
using namespace std;

Transaction::Transaction()
{
	AccountID = 0;
	TransactionID = 0;
	description = "";
	category = "";
	transaction_type = "";
	transaction_amount = 0;
	transaction_date = "";
	newbalance = 0;
}

//Get data from database
Transaction::Transaction(sql::ResultSet* data)
{
	description = data->getString("description");
	category = data->getString("category");
	transaction_type = data->getString("transaction_type");
	newbalance = data->getDouble("transaction_amount");
	transaction_date = data->getString("transaction_date");
	newbalance = data->getDouble("newbalance");
}

//Add transaction
void Transaction::addTrans()
{
	DBConnection db;
	db.prepareStatement("INSERT INTO transaction (TransactionID,description,category,transaction_type,transaction_amount,transaction_date,newbalance) VALUES (?,?,?,?,?,?,?)");
	db.stmt->setInt(1, TransactionID);
	db.stmt->setString(2, description);
	db.stmt->setString(3, category);
	db.stmt->setString(4, transaction_type);
	db.stmt->setDouble(5, transaction_amount);
	db.stmt->setString(6, transaction_date);
	db.stmt->setDouble(7, newbalance);
	db.QueryStatement();
	AccountID = db.getGeneratedId();

}

