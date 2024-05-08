#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
using namespace std;

class Player{
    public:
        string color;
        int numTurns;           // Number of turns taken by the player
        int killCount;          // Number of tokens killed by the player
        int numTokens;          // Number of tokens for each player
        int *tokenPosition;     // Store the position of each token
        int *tokenDistance;     // Store the distance of each token from the start
        vector<int> diceValues;  // Store the current dice rolls for the player

        sf::RectangleShape *homeGrids;

        void initializePlayer(string color, int numTkn, sf::RectangleShape *hmGrids){
            this->color = color;
            numTurns = 0;
            killCount = 0;
            numTokens = numTkn;
            tokenPosition = new int[numTokens];
            tokenDistance = new int[numTokens];
            
            for(int i = 0; i < numTokens; i++){
                this->tokenPosition[i] = -1;
                this->tokenDistance[i] = 0;
            }
            
            homeGrids = hmGrids;
        }

        void playerDetails(){
            cout<<color<<endl
                <<numTurns<<endl
                <<numTokens<<endl;
            
            for(int i=0; i<numTokens; ++i)
                cout<<tokenPosition[i]<<" "<<tokenDistance[i]<<endl;
        }
        bool throwDice(){
            int val=(rand()%6)+1;
            diceValues.push_back(val);
            if(val==6)
                return true;
            else
                return false;
        }
};