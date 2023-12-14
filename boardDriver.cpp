// #include <iostream>
// #include "Board.h"
#include "Store.h"
// #include "Player.h"

using namespace std;

int main()
{
    Store store0, store1, store2, store3;
    Board board;

    // board.displayBoard(0);
    string in_file, line, name, desc, price, type, stam, money, candy, effect, effect_value, use_candy, victim;
    int stamina, winner_num, eff_val, turn_choice = 0;

    char sub; // candy store
    string candy_choice, candy_remove;
    bool substitution = true; // candy store substitution

    // int user_move;
    double gold, price_temp;
    Candy temp, blank_candy;
    Player inter;
    Candy c_arr[11];            // all available candies
    vector<Player> users;       // game users
    vector<bool> robbers_repel; // whether each player has repel or not
    int character_count = 0;
    bool winner = false;
    bool invalid_character;

    srand(time(0));

    ifstream candy_file("candies.txt"); // load all candies
    if (!candy_file.is_open())
    {
        cout << "candy file missing" << endl;
    }
    else
    {
        int m = 0;
        while (getline(candy_file, line))
        {
            stringstream ss(line);
            getline(ss, name, '|');
            getline(ss, desc, '|');
            getline(ss, effect, '|');
            getline(ss, effect_value, '|');
            getline(ss, type, '|');
            getline(ss, price);
            eff_val = stoi(effect_value);
            price_temp = stod(price);
            c_arr[m].name = name;
            c_arr[m].description = desc;
            c_arr[m].effect = effect;
            c_arr[m].effect_value = eff_val;
            c_arr[m].price = price_temp;
            c_arr[m].candy_type = type;
            m++;
        }
        candy_file.close();
    }

    ifstream file("candy_menu.txt"); // load candy store inventories
    if (!file.is_open())
    {
        cout << "Cannot add candy! Read a candy file first" << endl;
    }
    else
    {
        while (getline(file, line))
        {
            stringstream ss(line);
            getline(ss, name, '|');
            getline(ss, desc, '|');
            getline(ss, price, '|');
            price_temp = stod(price);
            getline(ss, type);
            temp.name = name;
            temp.description = desc;
            temp.price = price_temp;
            temp.candy_type = type;
            store0.addCandy(temp);
            store1.addCandy(temp);
            store2.addCandy(temp);
            store3.addCandy(temp);
        }
        file.close();
    }

    ifstream char_file("characters.txt"); // LOAD CHARACTERS
    if (!char_file.is_open())
    {
        cout << "char file not open!" << endl;
    }
    else
    {
        while (getline(char_file, line))
        {
            stringstream ss(line);
            getline(ss, name, '|');
            getline(ss, stam, '|');
            stamina = stoi(stam);
            getline(ss, money, '|');
            gold = stod(money);
            while (getline(ss, candy, ','))
            {
                temp.name = candy;
                // inter.addCandy(temp);
                for (int i = 0; i < 11; i++)
                {
                    if (temp.name == c_arr[i].name)
                    {
                        inter.addCandy(c_arr[i]);
                    }
                }
            }
            inter.setName(name);
            inter.setStamina(stamina);
            inter.setGold(gold);
            // players.push_back(inter); // ADD PLAYABLE CHAR
            board.setCharacter(inter, character_count);
            ++character_count;
            inter = Player();
        }
        char_file.close();
    }

    string player_name, char_choice;
    int number_of_players;
    cout << "Welcome to the game of candyland. Please enter the number of participants:" << endl;
    cin >> number_of_players; // ENTER # OF PLAYERS

    while (cin.fail() || number_of_players < 2 || number_of_players > 4)
    {
        cout << "Invalid selection!" << endl;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cin >> number_of_players;
    }
    cin.ignore(10000, '\n');
    for (int i = 0; i < number_of_players; i++)
    {
        robbers_repel.push_back(false);
    }

    board.setPlayerCount(number_of_players);
    for (int j = 0; j < number_of_players; j++) // SET PLAYER
    {
        cout << "Enter player name:" << endl;
        getline(cin, player_name);

        cout << "Awesome! Here is a list of characters a player can select from:" << endl;
        for (int i = 0; i < character_count; i++)
        {
            cout << "Name: " << board.getCharacter(i).getName() << endl;
            cout << "Stamina: " << board.getCharacter(i).getStamina() << endl;
            cout << "Gold: " << board.getCharacter(i).getGold() << endl;
            cout << "Candies: " << endl;
            board.getCharacter(i).printInventory();
            cout << endl;
        }
        invalid_character = true;
        while (invalid_character == true || char_choice == "")
        {
            getline(cin, char_choice);
            for (int i = 0; i < character_count; i++)
            {
                if (char_choice == board.getCharacter(i).getName())
                { // add character to users
                    users.push_back(board.getCharacter(i));
                    invalid_character = false;
                    for (int k = i; k < character_count - 1; k++)
                    { // shift remove taken character
                        board.setCharacter(board.getCharacter(k + 1), k);
                    } // available characters decrements by 1
                    --character_count;
                    break;
                }
            }
            if (invalid_character == true)
            {
                cout << "invalid character name!" << endl;
                char_choice = "";
            }
        }
        users.at(j).setUserName(player_name);
        cout << "Would you like to go to the candy store? (Y/N)" << endl;
        cin >> sub;
        if (inter.validChar(sub))
        {
            if (sub == 'Y')
            { // go to candy store 0
                if (users.at(j).getGold() < store0.findCheapest())
                { // not enough gold
                    cout << "You broke buddy keep it moving" << endl;
                }
                else // can afford a candy
                {
                    store0.printInventory();
                    cout << "store 0: Which candy would you like to buy?" << endl;
                    getline(cin, candy_choice);
                    while (!store0.findCandy(candy_choice))
                    { // store doesnt have candy
                        cout << "candy not in stock! enter the name of a different candy" << endl;
                        getline(cin, candy_choice);
                    }
                    while (users.at(j).getCandyAmount() == 9 && substitution == true)
                    {
                        // substitution
                        cout << "Your inventory is full! Want to substitute out something in your bag? (Y/N)" << endl;
                        cin >> sub;
                        if (inter.validChar(sub))
                        {
                            if (sub == 'Y')
                            {
                                users.at(j).printInventory();
                                cout << "Enter the name of the candy to get rid of!" << endl;
                                getline(cin, candy_remove);
                                if (users.at(j).findCandy(candy_remove).name == candy_remove)
                                {
                                    cout << "candy to remove is found!" << endl;
                                    users.at(j).removeCandy(candy_remove);
                                    cout << "candy removed!" << endl;
                                    break;
                                }
                            }
                            else
                            {
                                cout << "no substitution!" << endl;
                                substitution = false;
                            }
                        }
                    }
                    if (substitution == true)
                    {
                        for (int i = 0; i < 11; i++)
                        {
                            if (c_arr[i].name == candy_choice)
                            { // check array for candy
                                if (c_arr[i].price <= users.at(j).getGold())
                                {                                   // check player can afford candy
                                    users.at(j).addCandy(c_arr[i]); // add candy
                                    users.at(j).setGold(users.at(j).getGold() - c_arr[i].price);
                                    // subtract candy price from player's gold
                                    break;
                                }
                                else
                                {
                                    cout << "Cant afford candy!" << endl;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    board.resetBoard();
    board.addCandyStore(0);
    board.addCandyStore(15);
    board.addCandyStore(43);
    board.addCandyStore(68);
    store0.setPosition(0);
    store1.setPosition(15);
    store2.setPosition(43);
    store3.setPosition(68);
    board.gummyInitialize();

    while (winner == false)
    { // or 82
        for (int player_num = 0; player_num < number_of_players; player_num++)
        {
            int player_position = board.getPlayerPosition(player_num);

            if (users.at(player_num).getStamina() <= 0 || users.at(player_num).getLostTurns() > 0)
            { // LOST TURNS
                // cout<<users.at(player_num).getUserName()<<"lost turn1: "<<users.at(player_num).getLostTurns()<<endl;
                users.at(player_num).lostTurn();
                // cout<<users.at(player_num).getUserName()<<"lost turn2: "<<users.at(player_num).getLostTurns()<<endl;
                if (users.at(player_num).getStamina() <= 0 && users.at(player_num).getLostTurns() == 0)
                {
                    // cout<<users.at(player_num).getUserName()<<"lost turn3: "<<users.at(player_num).getLostTurns()<<endl;
                    // if lost turns are over and user has no stamina -> gain 50 stamina
                    users.at(player_num).setStamina(50);
                }
                continue;
            }
            if (board.checkGummy(player_position, player_num) > 0)
            {
                // if player lands on gummy tile & they didnt place the gummy barrier
                //  checkGummy returns # of turns lost, otherwise returns 0
                cout << player_position << endl;
                cout << users.at(player_num).getUserName() << "lost turn gummy: " << users.at(player_num).getLostTurns() << endl;
                cout << "Gummy barrier!" << users.at(player_num).getUserName() << "is trapped for " << board.checkGummy(player_position, player_num) << " turns.." << endl;
                users.at(player_num).setLostTurns(board.checkGummy(player_position, player_num));
                cout << users.at(player_num).getUserName() << "lost turn gumm2: " << users.at(player_num).getLostTurns() << endl;
            }
            // user input for turn
            cout << "It's " << users.at(player_num).getUserName() << "'s turn" << endl;
            turn_choice = 0;
            while ((turn_choice != 1 && turn_choice != 2) || turn_choice == 0)
            {
                cout << "Please select a menu option:" << endl;
                cout << "1. Draw a card" << endl;
                cout << "2. Use candy" << endl;
                cout << "3. Show player stats" << endl;
                cin >> turn_choice;
                while (cin.fail() || turn_choice < 1 || turn_choice > 3)
                {
                    cout << "Invalid selection!" << endl;
                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore(10000, '\n');
                    }
                    cin >> turn_choice;
                }
                cin.ignore(10000, '\n');

                if (turn_choice == 1) // r works as well
                {                     // draw card
                    // cout << "To draw a card press D" << endl;
                    board.drawCard(player_num);
                    // cout << board.getMove() << endl;
                    // cout<<"player position before:"<<board.getPlayerPosition(player_num)<<endl;
                    board.movePlayer(board.getMove(), player_num);
                    board.setLastMove(board.getMove(), player_num);
                    // cout<<"player position after:"<< board.getPlayerPosition(player_num)<<endl;
                    //  board.displayBoard(0);
                }
                else if (turn_choice == 2)
                { // use candy
                    cout << "Here is a list of your candies:" << endl;
                    users.at(player_num).printInventory();
                    if (users.at(player_num).getCandyAmount() < 1)
                    {
                        cout << "You have no candy!" << endl;
                        turn_choice = 0;
                    }
                    else
                    { // user has candy to use
                        cout << "Which candy would you like to use?" << endl;
                        getline(cin, use_candy);
                        Candy consume = users.at(player_num).findCandy(use_candy);
                        while (consume.name == blank_candy.name)
                        {
                            cout << "Candy not found!" << endl;
                            getline(cin, use_candy);
                            consume = users.at(player_num).findCandy(use_candy);
                        }
                        for (int i = 0; i < 11; i++)
                        {
                            if (c_arr[i].name == consume.name)
                            {
                                consume = c_arr[i];
                                users.at(player_num).removeCandy(consume.name);
                                cout << "candy found!" << endl;
                                break;
                            }
                        }
                        if (consume.effect_value > 0)
                        { // self buff
                            if (consume.effect == "stamina")
                            {
                                cout << "stamina before: " << users.at(player_num).getStamina() << endl;
                                users.at(player_num).setStamina(users.at(player_num).getStamina() + consume.effect_value);
                                cout << "stamina after: " << users.at(player_num).getStamina() << endl;
                            }
                            else
                            { // other
                                cout << "Poison immunity gained!" << endl;
                                users.at(player_num).setImmunity(consume.effect_value);
                            }
                        }
                        else if (consume.effect_value < 0)
                        { // nerf opponent
                            if (consume.effect == "stamina")
                            {
                                cout << "Who's stamina do you want to drain?" << endl;
                                getline(cin, victim);
                                int xx = 0;
                                while (xx < number_of_players)
                                {
                                    if (victim == users.at(xx).getUserName())
                                    {
                                        if (consume.effect_value >= users.at(xx).getImmunity())
                                        { // if immunity bigger than poison (negative values)
                                            cout << users.at(xx).getUserName() << " has used their immunity!" << endl;
                                            users.at(xx).setImmunity(0);
                                        }
                                        else
                                        { // player xx loses stamina because not enough immunity
                                            cout << users.at(xx).getUserName() << "'s stamina before:" << users.at(xx).getStamina() << endl;
                                            users.at(xx).setStamina(users.at(xx).getStamina() + consume.effect_value);
                                            cout << users.at(xx).getUserName() << "'s stamina after:" << users.at(xx).getStamina() << endl;
                                        }
                                        break;
                                    }
                                    xx++;
                                    if (xx == number_of_players)
                                    {
                                        cout << "Enemy not found! Enter an enemy name" << endl;
                                        getline(cin, victim);
                                        xx = 0;
                                    }
                                }
                            }
                            else
                            { // turns via gummybear
                                if (player_position <= 0)
                                {
                                    cout << "Cant place gummy barrier on starting tile!" << endl;
                                    users.at(player_num).addCandy(consume);
                                    turn_choice = 0;
                                }
                                else
                                { // add gummy
                                    int gummy_turns = consume.effect_value;
                                    board.setGummy(player_position, player_num, gummy_turns);
                                }
                            }
                        }
                        else
                        {
                            cout << "candy error" << endl;
                        }
                    }
                }
                else
                { // show player stats
                    cout << "Here are your stats:" << endl;
                    cout << "Player name: " << users.at(player_num).getUserName() << endl;
                    cout << "Character: " << users.at(player_num).getName() << endl;
                    cout << "Stamina: " << users.at(player_num).getStamina() << endl;
                    cout << "Gold: " << users.at(player_num).getGold() << endl;
                    users.at(player_num).printInventory();
                    cout << endl;
                }
            }

            if (board.isPositionCandyStore(player_position) && player_position != 0) // if candy store
            {
                board.displayBoard(player_num);
                cout << users.at(player_num).getUserName() << " found a candy store!! tactical nuke incoming!!" << endl;
                // char want_candy;

                if (player_position == store1.getPosition())
                {
                    if (users.at(player_num).getGold() < store1.findCheapest())
                    { // not enough gold
                        cout << "You broke buddy keep it moving" << endl;
                    }
                    else // can afford a candy
                    {
                        store1.printInventory();
                        cout << "Store 1: Would you like to buy a candy? (Y/N)" << endl;
                        cin >> sub;
                        if (users.at(player_num).validChar(sub))
                        { // valid character
                            if (sub == 'Y')
                            {
                                cout << "Which candy would you like to buy?" << endl;
                                getline(cin, candy_choice);
                                while (!store1.findCandy(candy_choice))
                                { // store doesnt have candy
                                    cout << "candy not in stock! enter the name of a different candy" << endl;
                                    getline(cin, candy_choice);
                                }
                                while (users.at(player_num).getCandyAmount() == 9 && substitution == true)
                                {
                                    // substitution
                                    cout << "Your inventory is full! Want to substitute out something in your bag? (Y/N)" << endl;
                                    cin >> sub;
                                    if (inter.validChar(sub))
                                    {
                                        if (sub == 'Y')
                                        {
                                            users.at(player_num).printInventory();
                                            cout << "Enter the name of the candy to get rid of!" << endl;
                                            getline(cin, candy_remove);
                                            if (users.at(player_num).findCandy(candy_remove).name == candy_remove)
                                            {
                                                cout << "candy to remove is found!" << endl;
                                                users.at(player_num).removeCandy(candy_remove);
                                                cout << "candy removed!" << endl;
                                                break;
                                            }
                                        }
                                        else
                                        {
                                            cout << "no substitution!" << endl;
                                            substitution = false;
                                        }
                                    }
                                }
                                if (substitution == true)
                                {
                                    for (int i = 0; i < 11; i++)
                                    {
                                        if (c_arr[i].name == candy_choice)
                                        { // check array for candy
                                            if (c_arr[i].price <= users.at(player_num).getGold())
                                            {                                            // check player can afford candy
                                                users.at(player_num).addCandy(c_arr[i]); // add candy
                                                users.at(player_num).setGold(users.at(player_num).getGold() - c_arr[i].price);
                                                // subtract candy price from player's gold
                                                break;
                                            }
                                            else
                                            {
                                                cout << "Cant afford candy!" << endl;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                else if (player_position == store2.getPosition())
                {
                    if (users.at(player_num).getGold() < store2.findCheapest())
                    { // not enough gold
                        cout << "You broke buddy keep it moving" << endl;
                    }
                    else // can afford a candy
                    {
                        store2.printInventory();
                        cout << "Store 2: Would you like to buy a candy? (Y/N)" << endl;
                        cin >> sub;
                        if (users.at(player_num).validChar(sub))
                        {
                            if (sub == 'Y')
                            {
                                cout << "store 2: Which candy would you like to buy?" << endl;
                                getline(cin, candy_choice);
                                while (!store2.findCandy(candy_choice))
                                { // store doesnt have candy
                                    cout << "candy not in stock! enter the name of a different candy" << endl;
                                    getline(cin, candy_choice);
                                }
                                while (users.at(player_num).getCandyAmount() == 9 && substitution == true)
                                {
                                    // substitution
                                    cout << "Your inventory is full! Want to substitute out something in your bag? (Y/N)" << endl;
                                    cin >> sub;
                                    if (inter.validChar(sub))
                                    {
                                        if (sub == 'Y')
                                        {
                                            users.at(player_num).printInventory();
                                            cout << "Enter the name of the candy to get rid of!" << endl;
                                            getline(cin, candy_remove);
                                            if (users.at(player_num).findCandy(candy_remove).name == candy_remove)
                                            {
                                                cout << "candy to remove is found!" << endl;
                                                users.at(player_num).removeCandy(candy_remove);
                                                cout << "candy removed!" << endl;
                                                break;
                                            }
                                        }
                                        else
                                        {
                                            cout << "no substitution!" << endl;
                                            substitution = false;
                                        }
                                    }
                                }
                                if (substitution == true)
                                {
                                    for (int i = 0; i < 11; i++)
                                    {
                                        if (c_arr[i].name == candy_choice)
                                        { // check array for candy
                                            if (c_arr[i].price <= users.at(player_num).getGold())
                                            {                                            // check player can afford candy
                                                users.at(player_num).addCandy(c_arr[i]); // add candy
                                                users.at(player_num).setGold(users.at(player_num).getGold() - c_arr[i].price);
                                                // subtract candy price from player's gold
                                                break;
                                            }
                                            else
                                            {
                                                cout << "Cant afford candy!" << endl;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                else if (player_position == store3.getPosition())
                {
                    if (users.at(player_num).getGold() < store3.findCheapest())
                    { // not enough gold
                        cout << "You broke buddy keep it moving" << endl;
                    }
                    else // can afford a candy
                    {
                        store3.printInventory();
                        cout << "Store 3: Would you like to buy a candy? (Y/N)" << endl;
                        cin >> sub;
                        if (users.at(player_num).validChar(sub))
                        {
                            if (sub == 'Y')
                            {
                                cout << "store 3: Which candy would you like to buy?" << endl;
                                getline(cin, candy_choice);
                                while (!store3.findCandy(candy_choice))
                                { // store doesnt have candy
                                    cout << "candy not in stock! enter the name of a different candy" << endl;
                                    getline(cin, candy_choice);
                                }
                                while (users.at(player_num).getCandyAmount() == 9 && substitution == true)
                                {
                                    // substitution
                                    cout << "Your inventory is full! Want to substitute out something in your bag? (Y/N)" << endl;
                                    cin >> sub;
                                    if (inter.validChar(sub))
                                    {
                                        if (sub == 'Y')
                                        {
                                            users.at(player_num).printInventory();
                                            cout << "Enter the name of the candy to get rid of!" << endl;
                                            getline(cin, candy_remove);
                                            if (users.at(player_num).findCandy(candy_remove).name == candy_remove)
                                            {
                                                cout << "candy to remove is found!" << endl;
                                                users.at(player_num).removeCandy(candy_remove);
                                                cout << "candy removed!" << endl;
                                                break;
                                            }
                                        }
                                        else
                                        {
                                            cout << "no substitution!" << endl;
                                            substitution = false;
                                        }
                                    }
                                }
                                if (substitution == true)
                                {
                                    for (int i = 0; i < 11; i++)
                                    {
                                        if (c_arr[i].name == candy_choice)
                                        { // check array for candy
                                            if (c_arr[i].price <= users.at(player_num).getGold())
                                            {                                            // check player can afford candy
                                                users.at(player_num).addCandy(c_arr[i]); // add candy
                                                users.at(player_num).setGold(users.at(player_num).getGold() - c_arr[i].price);
                                                // subtract candy price from player's gold
                                                break;
                                            }
                                            else
                                            {
                                                cout << "Cant afford candy!" << endl;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                else
                {
                    cout << "no candy store here!" << endl;
                }
            }

            if (board.isPositionSpecialTile(player_position))
            {
                int spec = rand() % 4;
                cout << users.at(player_num).getUserName() << " found a special tile!" << endl;
                switch (spec)
                {
                case 0:
                {
                    cout << "Shortcut Tile: Your spirits soar as you're propelled four tiles ahead, closing in on the Candy Castle." << endl;
                    board.movePlayer(4, player_num);
                    board.setLastMove(4, player_num);
                    break;
                } // shortcut 4 tile
                case 1:
                { // ice cream shop, draw card
                    cout << "Ice Cream Stop Tile: Congrats! You get a chance to draw a card again." << endl;
                    board.drawCard(player_num);
                    // cout << board.getMove() << endl;
                    board.movePlayer(board.getMove(), player_num);
                    board.setLastMove(board.getMove(), player_num);
                    break;
                }
                case 2:
                { // gumdrop - move back 4 tiles, lose 5 - 10 gold
                    double gold_lost = rand() % 6 + 5;
                    board.movePlayer(-4, player_num);
                    users.at(player_num).setGold(users.at(player_num).getGold() - gold_lost);
                    cout << "Gumdrop Forest Tile: Oops, You head back 4 tiles and lose " << gold_lost << " gold." << endl;
                    break;
                }
                case 3:
                { // gingerbread - move player back to previous position, lose immunity candy
                    cout << "Gingerbread House Tile: It's a bittersweet return to your previous location, accompanied by the forfeiture of one immunity candy." << endl;
                    int lastly = board.getLastMove(player_num);
                    cout << "YOU GOTTA MOVE BACK " << lastly << " TILES! THAT'S WHAT YOU GET FOR MESSING WITH THE GUMDROP BUTTONS" << endl;
                    board.movePlayer(-lastly, player_num);
                    if (users.at(player_num).removeCandy("Bubblegum Blast") || users.at(player_num).removeCandy("Breezy Butterscotch") || users.at(player_num).removeCandy("Caramel Comet"))
                    {
                        cout << "Lost an immunity candy!" << endl;
                    }
                    break;
                }
                default:
                    cout << "special tile default case" << endl;
                }
                cout << endl;
            }
            if (board.isPositionHiddenTreasure(player_position))
            {
                cout << users.at(player_num).getUserName() << " found hidden treasure!" << endl;
                if (board.isRiddleSolved())
                {
                    int treasurenum = rand() % 10;
                    if (treasurenum >= 0 && treasurenum < 3)
                    { // 30%
                        // stamina refill
                        int stamina_regen = rand() % 21 + 1;
                        cout << "stamina refill! stamina before: " << users.at(player_num).getStamina() << endl;
                        users.at(player_num).setStamina(users.at(player_num).getStamina() + stamina_regen);
                        cout << "stamina after: " << users.at(player_num).getStamina() << endl;
                    }
                    else if (treasurenum == 3)
                    { // 10% rand 20 - 40 gold, player can have max 100 gold
                        // gold windfall
                        cout << "Gold windfall! gold before: " << users.at(player_num).getGold() << endl;
                        int gold_gain = rand() % 21 + 20;
                        if ((users.at(player_num).getGold() + gold_gain) > 100)
                        { // gold over 100
                            users.at(player_num).setGold(100);
                        }
                        else
                        {
                            users.at(player_num).setGold(gold_gain + users.at(player_num).getGold());
                        }
                        cout << "gold after: " << users.at(player_num).getGold() << endl;
                    }
                    else if (treasurenum > 3 && treasurenum < 7)
                    { // 30%
                        // robber's repel
                        cout << "You got a robber's repel candy!" << endl;
                        robbers_repel[player_num] = true;
                    }
                    else
                    { // 30%
                        // candy acquisition
                        if (users.at(player_num).getCandyAmount() < 9)
                        {
                            // if player has inventory space: acquire candy
                            int acq = rand() % 10;
                            if (acq >= 0 && acq < 7)
                            { // 70% chance
                                // jellybean of vigor increase stamina by 50
                                cout << "Jellybean of vigor increases your stamina by 50!" << endl;
                                users.at(player_num).setStamina(users.at(player_num).getStamina() + 50);
                            }
                            else
                            { // 30% chance
                                // find treasure hunter's truffle
                                cout << "You discover a treasure hunter's truffle! Can you solve the riddle to obtain it?" << endl;
                                if (board.isRiddleSolved())
                                {
                                    cout << "Treasure hunter's truffle increases your gold by 777!" << endl;
                                    users.at(player_num).setGold(users.at(player_num).getGold() + 777);
                                }
                            }
                        }
                    }
                }
                cout << endl;
            }

            users.at(player_num).calamityCheck();

            if (board.getPlayerPosition(player_num) > 82)
            { // overflow check
                board.setPlayerPosition(82, player_num);
            }
            if (users.at(player_num).getGold() < 0)
            {
                users.at(player_num).setGold(0); // negative gold
            }

            for (int y = 0; y < number_of_players; y++)
            {
                if (board.getPlayerPosition(player_num) == board.getPlayerPosition(y) && player_num != y && board.getPlayerPosition(player_num) != 0)
                {
                    // same tile conflict
                    // conflict = true;
                    cout << "conflict! " << users.at(y).getUserName() << " is moved back 1 space!" << endl;
                    if (robbers_repel.at(player_num))
                    {
                        // player is saved by candy
                        cout << users.at(player_num).getUserName() << " uses their robber's repel candy to save their gold!" << endl;
                        robbers_repel.at(player_num) = false;
                    }
                    else
                    { // player loses gold
                        int gold_steal = rand() % 26 + 5;
                        cout << users.at(y).getUserName() << " has stolen " << gold_steal << " gold from " << users.at(player_num).getUserName() << endl;
                        cout << users.at(player_num).getUserName() << "'s gold before: " << users.at(player_num).getGold() << endl;
                        cout << users.at(y).getUserName() << "'s gold before: " << users.at(y).getGold() << endl;
                        users.at(player_num).setGold(users.at(player_num).getGold() - gold_steal);
                        users.at(y).setGold(users.at(y).getGold() + gold_steal);
                        cout << users.at(player_num).getUserName() << "'s gold after: " << users.at(player_num).getGold() << endl;
                        cout << users.at(y).getUserName() << "'s gold after: " << users.at(y).getGold() << endl;
                    }
                    board.movePlayer(-1, y);
                    cout << endl;
                    break;
                }
            }
            // cout<<board.getPlayerPosition(player_num)<<endl;
            if (board.getPlayerPosition(player_num) >= 82)
            { // IF AT END TILE - PLAYER NUM IS WINNER
                // cout<<board.getPlayerPosition(player_num)<<endl;
                winner = true;
                winner_num = player_num;
                break;
            }
            if (board.isPositionHailStorm(player_position))
            { // if hailstorm, move back random # of tiles
                cout << "OH NO A HAILSTORM GET DOWN!!" << endl;
                int hailstorm_move;
                if (board.getPlayerPosition(player_num) > 0)
                {
                    hailstorm_move = -(rand() % board.getPlayerPosition(player_num));
                }
                else
                {
                    hailstorm_move = 0;
                }

                cout << users.at(player_num).getUserName() << " has been sent back " << -hailstorm_move << " tiles!" << endl;
                board.movePlayer(hailstorm_move, player_num);
                cout << endl;
                if (board.getPlayerPosition(player_num) < 0)
                { // if put back before start tile
                    board.setPlayerPosition(0, player_num);
                }
            }

            users.at(player_num).setStamina(users.at(player_num).getStamina() - 1);
            if (users.at(player_num).getStamina() <= 0)
            {
                users.at(player_num).setLostTurns(2); // if no stamina lose two turns
            }
            board.setLastMove(board.getMove(), player_num);
            board.setMove(0);
        }
        cout << endl;
        board.displayBoard(0);
        cout << endl;
    }
    cout << "Game over!" << endl;
    cout << users.at(winner_num).getUserName() << " has won the game! You are going to candy mountain!" << endl;
    cout<<endl;
    for (int i = 0; i < number_of_players; i++)
    {
        cout << users.at(i).getUserName() << "'s final stats" << endl;
        cout << "their character was: " << users.at(i).getName() << endl;
        cout << "with stamina: " << users.at(i).getStamina() << endl;
        cout << "with gold: " << users.at(i).getGold() << endl;
        users.at(i).printInventory();
        cout << endl;
    }

    ofstream out_file("results.txt");
    out_file << users.at(winner_num).getUserName() << " has won the game! You are going to candy mountain!" << endl;
    out_file<<endl;
    for (int i = 0; i < number_of_players; i++)
    {
        out_file << users.at(i).getUserName() << "'s final stats" << endl;
        out_file << "their character was: " << users.at(i).getName() << endl;
        out_file << "with stamina: " << users.at(i).getStamina() << endl;
        out_file << "with gold: " << users.at(i).getGold() << endl;
        users.at(i).outfileInventory(out_file);
        out_file << endl;
    }

    return 0;
}