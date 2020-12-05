#include "user.h"

User::User(int ID) : _userID(ID), _transFromUser(0), _transToUser(0), _avgRating(0) {}

int User::getUserID() { return _userID; }

int User::transactionsToUser() { return _transToUser; }

int User::transactionsFromUser() { return _transFromUser; }

double User::averageRating() { return _avgRating; }

int User::numTransactions() {
    return _transToUser + _transFromUser;
}
// void User::newTransaction(Transaction* trans) {
//     if (trans->source()->getUserID() == _userID)
//         _transFromUser++;

//     else if (trans->target()->getUserID() == _userID) {
//         _transToUser++;
//         _avgRating = (_avgRating * (_transToUser - 1) + trans->rating()) / _transToUser;
//     }
// }