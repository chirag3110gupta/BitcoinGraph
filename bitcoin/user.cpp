#include "user.h"

int User::getNumTransactions() {
    return _touser + _fromuser;
}
void User::newTransaction(Transaction& trans) {
    if (trans.getSource()->getUserID() == _userID) {
        _fromuser++;
    }
    else if (trans.getTarget()->getUserID() == _userID) {
        _touser++;
        _avgrating = (_avgrating * (_touser - 1) + trans.getRating()) / _touser;
    }
}