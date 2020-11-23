#pragma once
#include "transaction.h"
#include <vector>
class User {
    public:
    User(int ID):_userID(ID), _fromuser(0), _touser(0), _avgrating(0) {};
    int getUserID() { return _userID; }
    int getNumTransactionsToUser() { return _touser; }
    int getNumTransactionsFromUser() { return _fromuser; }
    double getAverageRating() { return _avgrating; }
    int getNumTransactions();
    void newTransaction(Transaction& trans);

   private:
    int _userID;
    int _fromuser, _touser;
    double _avgrating;

};