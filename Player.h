#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

struct Candy
{
    string name;
    string description;
    string effect;
    int effect_value;
    string candy_type;
    double price;
};

class Player{
    private:
        const static int _MAX_CANDY_AMOUNT = 9;
        string _name;
        int _stamina;
        double _gold;
        string _effect;
        Candy _inventory[9];
        int _candy_amount;
        string _user_name;
        //bool x;
        int _immunity;
        int _lost_turns;
    public:
        Player();
        Player(string, string, int, double, string, Candy[], const int, int, int);

        int getCandyAmount() const;

        void setName(string);
        string getName() const;

        void setUserName(string);
        string getUserName() const;
        
        void setStamina(int);
        int getStamina() const;

        void setGold(double);
        double getGold() const;

        void setEffect(string effect);
        string getEffect() const;

        void setLostTurns(int);
        void lostTurn();
        int getLostTurns() const;

        void setImmunity(int);
        int getImmunity() const;

        void printInventory();
        void outfileInventory(ofstream&);

        Candy findCandy(string);
        bool addCandy(Candy);
        bool removeCandy(string);
        void printBag();

        bool playRockPaperScissors();
        void calamityCheck();
        
        bool validChar(char&);
};

#endif