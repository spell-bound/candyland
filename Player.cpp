#include <iostream>
#include "Player.h"
#include "Board.h"
// using namespace std;

Player::Player()
{
    _stamina = 0;
    _name = "";
    _gold = 0;
    _candy_amount = 0;
    _effect = "";
    _user_name = "";
    for (int i = 0; i < 9; i++)
    {
        _inventory[i] = {};
    }
    _lost_turns = 0;
    _immunity = 0;
}

Player::Player(string name, string user_name, int stamina, double gold, string effect, Candy candy_array[], const int CANDY_ARR_SIZE, int lost_turns, int immunity)
{
    _name = name;
    _user_name = user_name;
    _stamina = stamina;
    _gold = gold;
    _effect = effect;
    _lost_turns = lost_turns;
    _immunity = immunity;
    int candy_count = 0;
    for (int i = 0; i < CANDY_ARR_SIZE && _candy_amount < _MAX_CANDY_AMOUNT; i++)
    {
        _inventory[i] = candy_array[i];
        if (_inventory[i].name != "")
        {
            candy_count++;
        }
    }

    // if (CANDY_ARR_SIZE < _MAX_CANDY_AMOUNT)
    // {
    //     for (int i = 0; i < CANDY_ARR_SIZE; i++)
    //     {
    //         _inventory[i] = candy_array[i];
    //         if (_inventory[i].name != "")
    //         {
    //             candy_count++;
    //         }
    //     }
    // }
    // else
    // {
    //     for (int i = 0; i < _MAX_CANDY_AMOUNT; i++)
    //     {
    //         _inventory[i] = candy_array[i];
    //         if (_inventory[i].name != "")
    //         {
    //             candy_count++;
    //         }
    //     }
    // }
    _candy_amount = candy_count;
}
int Player::getCandyAmount() const
{
    return _candy_amount;
}
void Player::setName(string name)
{
    _name = name;
}
string Player::getName() const
{
    return _name;
}
void Player::setUserName(string user_name)
{
    _user_name = user_name;
}
string Player::getUserName() const
{
    return _user_name;
}
void Player::setStamina(int stamina)
{
    _stamina = stamina;
}
int Player::getStamina() const
{
    return _stamina;
}
void Player::setGold(double gold)
{
    _gold = gold;
}
double Player::getGold() const
{
    return _gold;
}
void Player::setEffect(string effect)
{
    _effect = effect;
}
string Player::getEffect() const
{
    return _effect;
}
void Player::setLostTurns(int lost_turns)
{
    _lost_turns = lost_turns;
}
void Player::lostTurn()
{
    _lost_turns--;
}
int Player::getLostTurns() const
{
    return _lost_turns;
}
void Player::setImmunity(int val)
{
    if (val >= 1)
    {
        // if val= 1: 10 poison immunity;
        // val= 2: 15 immunity
        // val=3: 20 immunity
        _immunity = -((val + 1) * 5);
    }
    else
    {
        //_immunity = 0;
        _immunity = -((val) * 5);
    }
}
int Player::getImmunity() const
{
    return _immunity;
}
void Player::printInventory()
{
    for (int i = 0; i < _MAX_CANDY_AMOUNT; i++)
    {

        if (_inventory[i].name != "")
        {
            cout << "[" << _inventory[i].name << "] ";
        }
        else
        {
            cout << "[Empty] ";
        }
        // cout<<"|";
        if (i % 3 == 2)
        {
            cout << endl;
        }
    }
}
void Player::outfileInventory(ofstream& out_file)
{
    // ofstream out_file("results.txt");
    // for(int i=0; i)
    // out_file << getUserName() << "'s final stats" << endl;
    // out_file << "their character was: " << getName() << endl;
    // out_file << "with stamina: " << getStamina() << endl;
    // out_file << "with gold: " << getGold() << endl;
    for (int i = 0; i < _MAX_CANDY_AMOUNT; i++)
    {

        if (_inventory[i].name != "")
        {
            out_file << "[" << _inventory[i].name << "] ";
        }
        else
        {
            out_file << "[Empty] ";
        }
        // cout<<"|";
        if (i % 3 == 2)
        {
            out_file << endl;
        }
    }
}
Candy Player::findCandy(string candy_name)
{
    Candy temp = Candy();
    int length = candy_name.length();
    bool check = true;
    if (length == 0)
    {
        return temp;
    }
    for (int i = 0; i < _MAX_CANDY_AMOUNT; i++)
    {
        check = true;
        if (_inventory[i].name.length() != length)
        {
            check = false;
        }
        else
        {
            for (int j = 0; j < length; j++)
            {
                if (toupper(candy_name[j]) != toupper(_inventory[i].name[j]))
                {
                    check = false;
                }
            }
        }
        if (check == true)
        {
            // cout<<"candy found!"<<endl;
            return _inventory[i];
        }
    }
    return temp;
}
bool Player::addCandy(Candy candy)
{
    for (int i = 0; i < _MAX_CANDY_AMOUNT; i++)
    {
        if (_inventory[i].name == "")
        {
            _inventory[i] = candy;
            _candy_amount++;
            return true;
        }
    }
    return false;
}
bool Player::removeCandy(string candy_name)
{
    Candy temp = Candy();
    int length = candy_name.length();
    bool check = true;
    for (int i = 0; i < _MAX_CANDY_AMOUNT; i++)
    {
        check = true;
        for (int j = 0; j < length; j++)
        {
            if (toupper(candy_name[j]) != toupper(_inventory[i].name[j]))
            {
                check = false;
            }
        }
        if (check == true)
        {
            // cout<<"candy found!"<<endl;
            for (int j = i; j < _MAX_CANDY_AMOUNT - 1; j++)
            {
                _inventory[j] = _inventory[j + 1];
            }
            _candy_amount--;
            _inventory[_MAX_CANDY_AMOUNT - 1] = temp;
            return true;
        }
    }
    return false;
}
void Player::printBag()
{
    for (int i = 0; i < 4; i++)
    {
        cout << "Name: " << _inventory[i].name << ". Description: " << _inventory[i].description << ". Price: " << _inventory[i].price << ". Type: " << _inventory[i].candy_type << endl;
    }
}

bool Player::playRockPaperScissors()
{
    char choice, comp_move;
    int x = 0; // -1: p1 wins, 1: p2 wins;
    while (x == 0)
    {
        cout << "Enter r, p, or s" << endl;
        cin >> choice;

        while (cin.fail() || (choice != 'r' && choice != 'p' && choice != 's'))
        {
            cout << "Invalid selection!" << endl;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(10000, '\n');
            }
            cin >> choice;
        }
        cin.ignore(10000, '\n');

        int comp = rand() % 3;
        switch (comp)
        {
        case 0:
            comp_move = 'r';
            break;
        case 1:
            comp_move = 'p';
            break;
        case 2:
            comp_move = 's';
            break;
        default:
            cout << "rock paper scissors error!" << endl;
        }

        if (choice == 'r')
        { // p1 chooses rock
            if (comp_move == 'r')
            {
                cout << "Tie! Play again" << endl;
            }
            else if (comp_move == 's')
            {
                // cout << "Player 1 has won " << endl;
                x = -1;
            }
            else
            { // p2 chooses paper
                // cout << "Player 2 has won "<< endl;
                x = 1;
            }
        }
        else if (choice == 's')
        { // p1 chooses scissors
            if (comp_move == 'r')
            {
                // cout << "Player 2 has won "<< endl;
                x = 1;
            }
            else if (comp_move == 's')
            {
                cout << "Tie! Play again" << endl;
            }
            else
            {
                // cout << "Player 1 has won "<< endl;
                x = -1;
            }
        }
        else
        { // p1 chooses paper
            if (comp_move == 'r')
            {
                // cout << "Player 1 has won " << endl;
                x = -1;
            }
            else if (comp_move == 's')
            {
                // cout << "Player 2 has won " << endl;
                x = 1;
            }
            else
            {
                cout << "Tie! Play again" << endl;
            }
        }
        if (x == -1)
        { // player wins!
            return true;
        }
        else if (x == 1)
        { // computer wins
            return false;
        }
        else
        {
            choice = ' ';
            comp_move = ' ';
        }
    }
    cout << "rps bug" << endl;
    return false;
}

void Player::calamityCheck()
{
    int calamity = rand() % 10;
    // 40% chance of calamity
    int calamity_rng = rand() % 100;
    if (calamity >= 0 && calamity < 4)
    { // calamity happens
        if (calamity_rng >= 0 && calamity_rng < 30)
        { // candy bandits!
            cout << "Oh no, " << getUserName() << "! Candy Bandits have swiped your gold coins!" << endl;
            int gold_lost = (rand() % 10) + 1;
            setGold(getGold() - gold_lost);
        }
        else if (calamity_rng >= 30 && calamity_rng < 65)
        { // lost in a lollipop
            cout << "Oh dear! You got lost in the lollipop labyrinth!" << endl;
            // rock paper scissors option
            // if win return lost stuff
            if (playRockPaperScissors())
            {
                cout << "You win rock paper scissors and dont lose a turn!" << endl;
            }
            else
            {
                // lose a turn
                setLostTurns(1);
                cout << "You lose rock paper scissors and lose a turn!" << endl;
            }
        }
        else if (calamity_rng >= 65 && calamity_rng < 80)
        { // candy avalance
            cout << "Watch out! A candy avalanche has struck!" << endl;
            if (playRockPaperScissors())
            {
                cout << "You win rock paper scissors and make it out safely!" << endl;
            }
            else
            {
                // lose 5-10 stamina and lose one turn
                int xyz = rand() % 6 + 5;
                setStamina(getStamina() - xyz);
                setLostTurns(1);
                cout << "You lose rock paper scissors and lose " << xyz << " stamina and one turn!" << endl;
            }
            // rock paper scissors
            // if win return lost stuff
        }
        else
        { // sticky taffy trap
            cout << "Oops! You are stuck in a sticky taffy trap!" << endl;
            if (removeCandy("Frosty Fizz"))
            { // if user has magic candy, no penalty
                cout << "You use a Frosty Fizz candy to save yourself!" << endl;
            }
            else if (removeCandy("Crimson Crystal"))
            {
                cout << "You use a Crimson Crystal candy to save yourself!" << endl;
            }
            else if (removeCandy("Mystic Marshmallow"))
            {
                cout << "You use a Mystic Marshmallow candy to save yourself!" << endl;
            }
            else
            {
                // NO MAGIC CANDY -> LOSE TURN
                cout << "You don't have any magic candy to save yourself and lose a turn!" << endl;
                setLostTurns(1);
            }
        }
    }
    else
    { // no calamity
        return;
    }
}

bool Player::validChar(char &sub)
{
    while (cin.fail() || (sub != 'Y' && sub != 'N'))
    {
        cout << "Invalid selection!" << endl;
        cout << sub << endl;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cin >> sub;
        cout << sub << endl;
    }
    cin.ignore(10000, '\n');
    return true;
}
