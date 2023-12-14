#include "Store.h"
#include "Board.h"

Store::Store()
{
    _store_name = "";
    _candy_name = "";
    _candy_amount = 0;
    _store_position = 0;
    for (int i = 0; i < 4; i++)
    {
        _inventory[i] = {};
    }
}
void Store::setPosition(int position)
{
    _store_position = position;
}
int Store::getPosition() const
{
    return _store_position;
}
void Store::printInventory()
{
    for (int i = 0; i < _MAX_CANDY_AMOUNT - 1; i++)
    {
        cout << "|";
        if (_inventory[i].name != "")
        {
            cout << "[" << _inventory[rand() % 4].name << "]";
        }
        else
        {
            cout << "[Empty]";
        }
        // cout<<"|";
        if (i % 2 == 1)
        {
            cout << "|" << endl;
        }
        if(i == 2){
            cout<< endl;
        }
    }
}
bool Store::addCandy(Candy candy)
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
// bool Store::removeCandy(string candy_name)
// {
//     Candy temp = Candy();
//     int length = candy_name.length();
//     bool check = true;
//     for (int i = 0; i < _MAX_CANDY_AMOUNT; i++)
//     {
//         check = true;
//         for (int j = 0; j < length; j++)
//         {
//             if (toupper(candy_name[j]) != toupper(_inventory[i].name[j]))
//             {
//                 check = false;
//             }
//         }
//         if (check == true)
//         {
//             // cout<<"candy found!"<<endl;
//             for (int j = i; j < _MAX_CANDY_AMOUNT - 1; j++)
//             {
//                 _inventory[j] = _inventory[j + 1];
//             }
//             _candy_amount--;
//             _inventory[_MAX_CANDY_AMOUNT - 1] = temp;
//             return true;
//         }
//     }
//     return false;
// }
int Store::findCheapest(){
    int cheapest = _inventory[0].price;
    for(int i=0; i<_MAX_CANDY_AMOUNT - 1; i++){
        if(cheapest > _inventory[i+1].price){
            cheapest = _inventory[i+1].price;
        }
    }
    return cheapest;
}
bool Store::findCandy(string candy_name){
    for(int i=0; i<_MAX_CANDY_AMOUNT; i++){
        if(candy_name == _inventory[i].name){
            return true;
        }
    }
    return false;
}