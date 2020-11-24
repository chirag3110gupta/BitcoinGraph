#include "user.h"

int User::numTransactions() {
    return _transToUser + _transFromUser;
}
void User::newTransaction(Transaction& trans) {
    if (trans.getSource()->getUserID() == _userID)  
        _transFromUser++;

    else if (trans.getTarget()->getUserID() == _userID) {
        _transToUser++;
        _avgRating = (_avgRating * (_transToUser - 1) + trans.getRating()) / _transToUser;
    }
}