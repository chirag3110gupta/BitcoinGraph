#include "user.h"

int User::numTransactions() {
    return _transToUser + _transFromUser;
}
void User::newTransaction(Transaction& trans) {
    if (trans.source()->getUserID() == _userID)  
        _transFromUser++;

    else if (trans.target()->getUserID() == _userID) {
        _transToUser++;
        _avgRating = (_avgRating * (_transToUser - 1) + trans.rating()) / _transToUser;
    }
}