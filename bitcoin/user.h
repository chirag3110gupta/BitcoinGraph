#pragma once
#include "transaction.h"
#include <vector>
class User {
    public:
    User(int ID):_userID(ID), _transFromUser(0), _transToUser(0), _avgRating(0) {};
    int getUserID() { return _userID; }
    int transactionsToUser() { return _transToUser; }
    int transactionsFromUser() { return _transFromUser; }
    double averageRating() { return _avgRating; }
    int numTransactions();
    void newTransaction(Transaction& trans);

   private:
    int _userID;
    int _transFromUser, _transToUser;
    double _avgRating;

};