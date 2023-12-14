#ifndef BOARD_H
#define BOARD_H
#include "Player.h"

#define RED "\033[;41m"     /* Red */
#define GREEN "\033[;42m"   /* Green */
#define BLUE "\033[;44m"    /* Blue */
#define MAGENTA "\033[;45m" /* Magenta */
#define CYAN "\033[;46m"    /* Cyan */
#define ORANGE "\033[48;2;230;115;0m"  /* Orange (230,115,0)*/
#define RESET "\033[0m"


struct Tile
{
    string color;
    string tile_type;
};

struct Card{
    int color_type;
    bool color_double;
};

class Board
{
private:
    const static int _BOARD_SIZE = 83;
    Tile _tiles[_BOARD_SIZE];
    const static int _MAX_CANDY_STORE = 3;
    const static int _MAX_HIDDEN_TREASURE = 3;
    const static int _MAX_SPECIAL_TILE = 21;
    const static int _MAX_CHARACTERS = 5;
    int _candy_store_position[_MAX_CANDY_STORE];
    int _special_tile_position[_MAX_SPECIAL_TILE];
    int _hidden_treasure_position[_MAX_HIDDEN_TREASURE];
    int _candy_store_count;
    int _player_count;
    vector<int> _player_position;
    Player _characters[_MAX_CHARACTERS];
    vector<int>last_move;
    vector<int>turns;
    int _move = 0;
    Card m1 = {0, false}, m2 = {0, true}, g1 = {1, false}, g2 = {1, true}, b1 = {2, false}, b2 = {2, true};
    int gummy_number = 0;
    int gummy[10][3];
    //bool x;

public:
    Board();

    void resetBoard();
    void displayTile(int position);
    void displayBoard(int player_num);

    bool setPlayerPosition(int new_position, int player_num);
    void setPlayerCount(int number_of_players);
    void setCharacter(Player, int);

    Player getCharacter(int char_num) const;
    int getPlayerCount() const;
    int getBoardSize() const;
    int getCandyStoreCount() const;
    int getPlayerPosition(int player_num) const;
    //Card drawCard(Card, Card, Card, Card, Card, Card);
    void drawCard(int player_num);
    void setMove(int);
    int getMove() const;

    bool addCandyStore(int);
    bool isPositionCandyStore(int); 
    bool isPositionSpecialTile(int);
    bool isPositionHiddenTreasure(int);
    bool isRiddleSolved();
    bool isPositionHailStorm(int);

    bool movePlayer(int tile_to_move_forward, int player_num);
    void setLastMove(int moved, int player_num);
    int getLastMove(int player_num) const;
    // void setTurns(int, int player_num);
    // int getTurns(int player_num) const;

    void gummyInitialize();
    void setGummy(int, int, int);
    int checkGummy(int, int);
};

#endif