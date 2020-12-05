#pragma once
#include "user.h"

class Transaction {
   public:
    Transaction(User *sourceID, User *targetID, int rating);
    Transaction(User *sourceID, User *targetID);
    ~Transaction();

    User *source();
    User *target();
    int rating();

   private:
    User *_sourceID, *_targetID;
    int _rating;
};