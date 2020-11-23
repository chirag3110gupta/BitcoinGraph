#include "transaction.h"

#include "user.h"

Transaction::Transaction(User *sourceID, User *targetID, int rating)
    : _sourceID(sourceID), _targetID(targetID), _rating(rating){};

Transaction::Transaction(User *sourceID, User *targetID)
    : _sourceID(sourceID), _targetID(targetID), _rating(100){};
