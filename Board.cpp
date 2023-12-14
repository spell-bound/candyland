#include "Board.h"

Board::Board()
{
    resetBoard();
}

void Board::resetBoard()
{
    const int COLOR_COUNT = 3;
    const string COLORS[COLOR_COUNT] = {MAGENTA, GREEN, BLUE};
    Tile new_tile;
    string current_color;
    for (int i = 0; i < _BOARD_SIZE - 1; i++)
    {
        current_color = COLORS[i % COLOR_COUNT];
        new_tile = {current_color, "regular tile"};
        _tiles[i] = new_tile;
    }
    new_tile = {ORANGE, "regular tile"};
    _tiles[_BOARD_SIZE - 1] = new_tile;

    _candy_store_count = 0;
    for (int i = 0; i < _MAX_CANDY_STORE; i++)
    {
        _candy_store_position[i] = -1;
    }
    for (int i = 0; i < _MAX_SPECIAL_TILE; i++)
    { // special tile declare
        _special_tile_position[i] = rand() % _BOARD_SIZE;
    }
    for (int i = 0; i < _MAX_HIDDEN_TREASURE; i++)
    { // hidden treasure declare
        _hidden_treasure_position[i] = rand() % _BOARD_SIZE;
    }
    for (int i = 0; i < _player_count; i++)
    {
        _player_position.push_back(0);
    }
    for (int i = 0; i < _player_count; i++)
    {
        last_move.push_back(0);
    }
    for (int i = 0; i < _player_count; i++)
    {
        turns.push_back(0);
    }
}

void Board::displayTile(int position)
{
    if (position < 0 || position >= _BOARD_SIZE)
    {
        return;
    }
    Tile target = _tiles[position];
    cout << target.color << " ";
    bool match = false;
    int match_count = 0;
    for (int i = 0; i < _player_count; i++)
    {
        if (position == _player_position.at(i)) //
        { //if player is at position, cout their number
            cout << i + 1;
            match_count++;
            match = true;
        }
    }
    if (match == false)
    { //if no players at tile cout space
        cout << " ";
    }
    if (match_count <= 1)
    {//if none player at tile cout space
        cout << " ";
    }
    cout << RESET;
}

void Board::displayBoard(int player_num)
{
    // First horizontal segment
    // cout<<"debug display board"<<endl;

    for (int i = 0; i <= 23; i++)
    {
        displayTile(i);
    }
    cout << endl;
    // First vertical segment
    for (int i = 24; i <= 28; i++)
    {

        for (int j = 0; j < 23; j++)
        { //23 spaces for each tile, then display tile
            cout << "   ";
        }

        displayTile(i);
        cout << endl;
    }
    // Second horizontal segment
    for (int i = 52; i > 28; i--)
    {
        displayTile(i);
    }
    cout << endl;
    // Second vertical segment
    for (int i = 53; i <= 57; i++)
    {
        displayTile(i);

        for (int j = 0; j < 23; j++)
        {
            cout << "   ";
        }
        cout << endl;
    }
    // Third horizontal segment
    for (int i = 58; i < _BOARD_SIZE; i++)
    {
        displayTile(i);
    }
    cout << ORANGE << "Castle" << RESET << endl;
}

bool Board::setPlayerPosition(int new_position, int player_num)
{
    if (new_position >= 0 && new_position < _BOARD_SIZE)
    {
        _player_position.at(player_num) = new_position;
        return true;
    }
    return false;
}

void Board::setPlayerCount(int number_of_players)
{
    _player_count = number_of_players;
}
void Board::setCharacter(Player char_p, int char_num)
{
    _characters[char_num] = char_p;
}
Player Board::getCharacter(int char_num) const
{
    return _characters[char_num];
}
int Board::getPlayerCount() const
{
    return _player_count;
}
int Board::getBoardSize() const
{
    return _BOARD_SIZE;
}

int Board::getCandyStoreCount() const
{
    return _candy_store_count;
}

int Board::getPlayerPosition(int player_num) const
{
    return _player_position.at(player_num);
}

void Board::drawCard(int player_num)
{
    int card_num = rand() % 6;
    // int move = 0;
    Card draw;
    switch (card_num)
    {
    case 0:
        draw = m1;
        cout << "You drew a Mushroom Magenta card. Your game piece advances to Magenta Tile." << endl;
        break;
    case 1:
        draw = m2;
        cout << "You drew a DOUBLE Mushroom Magenta card. Your game piece advances to the second Magenta Tile." << endl;
        break;
    case 2:
        draw = g1;
        cout << "You drew a Guava Green card. Your game piece advances to Green Tile." << endl;
        break;
    case 3:
        draw = g2;
        cout << "You drew a DOUBLE Guava Green card. Your game piece advances to the second Green Tile." << endl;
        break;
    case 4:
        draw = b1;
        cout << "You drew a Bubblegum Blue card. Your game piece advances to Blue Tile." << endl;
        break;
    case 5:
        draw = b2;
        cout << "You drew a DOUBLE Bubblegum Blue card. Your game piece advances to the second Blue Tile." << endl;
        break;
    default:
        cout << "CARD ERROR!" << endl;
        draw = Card();
    }
    for (int i = 0; i < 3; i++)
    {
        // movePlayer(1, player_num);
        // move++;
        setMove(i + 1);
        if ((getPlayerPosition(player_num) + getMove()) % 3 == draw.color_type)
        {
            if (draw.color_double)
            {
                // movePlayer(3, player_num);
                // move += 3;
                setMove(getMove() + 3);
            }
            break;
        }
    }
    //setPlayerPosition(getPlayerPosition(player_num) + getMove(), player_num);
    return;
}
void Board::setMove(int move)
{

    if (move > 0)
    {
        _move = move;
    }
    else
    {
        _move = 0;
    }
}
int Board::getMove() const
{
    return _move;
}

bool Board::addCandyStore(int position)
{
    if (_candy_store_count >= _MAX_CANDY_STORE)
    {
        return false;
    }
    _candy_store_position[_candy_store_count] = position;
    _candy_store_count++;
    return true;
}

bool Board::isPositionCandyStore(int board_position)
{
    for (int i = 0; i < _candy_store_count; i++)
    {
        if (_candy_store_position[i] == board_position)
        {
            return true;
        }
    }
    return false;
}

bool Board::isPositionSpecialTile(int board_position)
{
    for (int i = 0; i < _MAX_SPECIAL_TILE; i++)
    {
        if (_special_tile_position[i] == board_position)
        {
            return true;
        }
    }
    return false;
}
bool Board::isPositionHiddenTreasure(int board_position)
{
    for (int i = 0; i < _MAX_HIDDEN_TREASURE; i++)
    {
        if (_hidden_treasure_position[i] == board_position)
        {
            return true;
        }
    }
    return false;
}

bool Board::isRiddleSolved()
{
    ifstream riddle_file("riddles.txt");
    string line, riddle, required_input, answer, attempt;
    string riddle_arr[20][3];
    if (riddle_file.is_open())
    {
        int i = 0;
        while (getline(riddle_file, line))
        {
            stringstream ss(line);
            getline(ss, riddle, '(');
            getline(ss, required_input, ')');
            getline(ss, answer);
            answer = answer.substr(1);
            riddle_arr[i][0] = riddle;
            riddle_arr[i][1] = required_input;
            riddle_arr[i][2] = answer;
            i++;
        }
        int x = rand() % 20;
        cout << "Riddle me this bozo! " << riddle_arr[x][0] << endl;
        cout << "Your answer has to be in " << riddle_arr[x][1] << " format!" << endl;
        //cout << "answer: " << riddle_arr[x][2] << endl;
        getline(cin, attempt);
        if (attempt == riddle_arr[x][2])
        {
            cout << "You are the riddler! Watch out for batman" << endl;
            return true;
        }
        else
        {
            cout << "You suck at this! Better luck next time" << endl;
            return false;
        }
    }
    else
    {
        cout << "riddle file not found!!" << endl;
        return false;
    }
}

bool Board::isPositionHailStorm(int player_position)
{
    int hailstorm_chance = rand() % 100;
    if (hailstorm_chance <= 4)
    {
        return true;
    }
    else
        return false;
}

bool Board::movePlayer(int tile_to_move_forward, int player_num)
{
    int new_player_position = tile_to_move_forward + _player_position.at(player_num);
    if (new_player_position < 0/* || new_player_position >= _BOARD_SIZE*/)
    {
        return false;
    }
    _player_position.at(player_num) = new_player_position;
    return true;
}
void Board::setLastMove(int moved, int player_num)
{
    last_move[player_num] = moved;
}
int Board::getLastMove(int player_num) const
{
    return last_move.at(player_num);
}

// void Board::setTurns(int x, int player_num)
// {
//     if (x == 1)
//     {
//         turns[player_num] += 1;
//     }
//     else
//     {
//         turns[player_num] = 0;
//     }
// }
// int Board::getTurns(int player_num) const
// {
//     return turns.at(player_num);
// }
void Board::gummyInitialize()
{
    for (int i = 0; i < 10; i++)
    {
        gummy[i][0] = -1;
        gummy[i][1] = -1;
        gummy[i][2] = -1;
    }
}
void Board::setGummy(int position, int player_num, int turns_lost)
{
    if(gummy_number >= 10){
        cout<<"max gummies reached!"<<endl;
        return;
    }
    gummy[gummy_number][0] = position;
    gummy[gummy_number][1] = player_num;
    gummy[gummy_number][2] = turns_lost;
    gummy_number++;
}

int Board::checkGummy(int position, int player_num){
    for(int i=0; i<10; i++){
        if(gummy[i][0] == position && gummy[i][1] != player_num){
            return gummy[i][2];
        }
    }
    return 0;
}