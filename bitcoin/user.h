#pragma once
#include <vector>

// #include "transaction.h"

class User {
   public:
    User(int ID);
    int getUserID();
    int transactionsToUser();
    int transactionsFromUser();
    double averageRating();
    int numTransactions();
    // std::size_t operator()(const User& k) const {
    //     using std::hash;
    //     using std::size_t;
    //     using std::string;

    //     return ((hash<int>()(k._userID)));
    // }

    // bool operator==(const User& other) const {
    //     return (_userID == other._userID);
    // }

    // void newTransaction(Transaction* trans);

   private:
    int _userID;
    int _transFromUser, _transToUser;
    double _avgRating;
};