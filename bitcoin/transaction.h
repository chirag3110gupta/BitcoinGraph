#pragma once
#include "user.h"
class Transaction {
   public:
    Transaction(User *sourceID, User *targetID, int rating);
    Transaction(User *sourceID, User *targetID);
    User *getSource() { return _sourceID; }
    User *getTarget() { return _targetID; }
    int getRating() { return _rating; }

   private:
    User *_sourceID, *_targetID;
    int _rating;
};