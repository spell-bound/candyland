#ifndef STORE_H
#define STORE_H
#include "Board.h"

using namespace std;

class Store{
    private:
        string _store_name;
        string _candy_name;
        int _store_position;
        int _candy_amount;
        Candy _inventory[4];
        const static int _MAX_CANDY_AMOUNT = 4;
    public:
        Store();

        void setPosition(int);
        int getPosition() const;

        void printInventory();
        bool addCandy(Candy candy);
        //bool removeCandy(string candy_name);
        int findCheapest();
        bool findCandy(string);
};

#endif