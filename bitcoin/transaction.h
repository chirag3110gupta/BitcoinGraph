#pragma once
#include "user.h"

class Transaction {
   public:
    Transaction(User *sourceID, User *targetID, int rating);
    Transaction(User *sourceID, User *targetID);
    ~Transaction();

    User *source() { return _sourceID; }
    User *target() { return _targetID; }
    int rating() { return _rating; }

   private:
    User *_sourceID, *_targetID;
    int _rating;
};