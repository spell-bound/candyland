------------------------
HOW TO COMPILE AND RUN
------------------------
Compile: g++ -Wall -Werror -Wpedantic -std=c++17 boardDriver.cpp Board.cpp Store.cpp Player.cpp 
Run: /Project 2
------------------------
DEPENDENCIES
------------------------
Board.h Player.h Store.h candies.txt candy_menu.txt characters.txt riddles.txt files must be in the folder for the program to run

------------------------
SUBMISSION INFORMATION
------------------------
CSCI1300 Fall 2023 Project 2
Author: Elijah Boyer-Otto
Recitation: 607 - Brendan Crowe
Date: Dec 5, 2023

------------------------
ABOUT THIS PROJECT
------------------------
This project implements an interactive board game fashioned after the game candy land. The players pick characters with different stats and candies, and navigate the board stumbling on hidden treasures and special tiles. The players can use candies they start with or find along the way to give themselves stat boosts and immunities. The candies can also be used to hinder the opponents by draining their stats or stealing their turns. The game ends when one player reaches the castle at the end of the board game. 