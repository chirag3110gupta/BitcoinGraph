#include "transaction.h"

#include "user.h"

Transaction::Transaction(User *sourceID, User *targetID, int rating)
    : _sourceID(sourceID), _targetID(targetID), _rating(rating){};

Transaction::Transaction(User *sourceID, User *targetID)
    : _sourceID(sourceID), _targetID(targetID), _rating(100){};

User *Transaction::source() { return _sourceID; }
User *Transaction::target() { return _targetID; }
int Transaction::rating() { return _rating; }

Transaction::~Transaction() {
    if (_sourceID != NULL) delete _sourceID;
    if (_targetID != NULL) delete _targetID;

    _sourceID = NULL;
    _targetID = NULL;
}