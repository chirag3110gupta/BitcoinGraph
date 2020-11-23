#pragma once
#include "user.h"
class Transaction {
   public:
    Transaction(User *sourceID, User *targetID, int rating);
    Transaction(User *sourceID, User *targetID);
    User *getSource() { return _sourceID; }
    User *getTarget() { return _targetID; }
    double getRating() { return _rating; }

   private:
    User *_sourceID, *_targetID;
    double _rating;
};