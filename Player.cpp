#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include "global.cpp"
using namespace std;

sf::Texture diceTexture;

class Player{
    public:
        string color;
        int numTurns;           // Number of turns taken by the player
        int killCount;          // Number of tokens killed by the player
        int numTokens;          // Number of tokens for each player
        int *tokenPosition;     // Store the position of each token
        int *tokenDistance;     // Store the distance of each token from the start
        int startingPoint;
        bool continue_running;  //this will be used as mutex for the player self
        sf::Texture tokenTexture;
        sf::RectangleShape symbolArea;

        vector<int> diceValues;  // Store the current dice rolls for the player
        int* tokenNumber;
        int nextToken;

        sf::RectangleShape *homeGrids;

        void initializePlayer(string color, int numTkn, int start, sf::RectangleShape *hmGrids, sf::RectangleShape *sym){
            this->color = color;
            numTurns = 0;
            killCount = 0;
            numTokens = numTkn;
            tokenPosition = new int[numTokens];
            tokenDistance = new int[numTokens];
            tokenNumber = new int[numTokens];
            startingPoint = start;
            symbolArea = *sym;
            
            for(int i = 0; i < numTokens; i++){
                this->tokenPosition[i] = -1;
                this->tokenDistance[i] = -1;
                this->tokenNumber[i] = i;

            }
            continue_running = true;
            nextToken = 0;
            
            homeGrids = hmGrids;

            if(color == "Red"){
                tokenTexture.loadFromFile("images/heart_tkn.png");
            }
            else if(color == "Green"){
                tokenTexture.loadFromFile("images/spade_tkn.png");
            }
            else if(color == "Blue"){
                tokenTexture.loadFromFile("images/club_tkn.png");
            }
            else if(color == "Yellow"){
                tokenTexture.loadFromFile("images/diamond_tkn.png");
            }
            // homeGrids[0].setTexture(&tokenTexture);
        }

        void playerDetails(){
            cout<<color<<endl
                <<numTurns<<endl
                <<killCount<<endl
                <<startingPoint<<endl;
            
            for(int i=0; i<numTokens; ++i)
                cout<<tokenPosition[i]<<" "<<tokenDistance[i]<<endl;
        }

        int throwDice(){
            int val=(rand()%6)+1;
            diceValues.push_back(val);
            
            return val;
        }

        void printDiceValues(){
            cout<<endl;
            cout<<color<<" Dice Values : ";
            for(int i=0; i<diceValues.size(); ++i)
                cout<<diceValues[i]<<" ";
            cout<<endl;
        }

        int selectDiceValue() {
            printDiceValues();
            while (true) {
                if (diceValues.empty()) {
                    cout << "No valid dice values left." << endl;
                    return -1;
                }
                int val;
                cout << "Enter the dice value: ";
                cin >> val;
                for (int i = 0; i < diceValues.size(); ++i) {
                    if (diceValues[i] == val) {
                        diceValues.erase(diceValues.begin() + i);
                        return val;
                    }
                }
                cout << "Invalid dice value" << endl;
            }
        }


        void printTokenPositions(){
            cout<<color<<" Token Positions:"<<endl;
            for(int i=0; i<numTokens; ++i)
                cout<<"Token "<<i<<" "<<tokenDistance[i]<<endl;
            cout<<endl;
        }

        void selectTokenNumber(int dvalue) {
            printTokenPositions();
            if (dvalue == 6) {
                while (true) {
                    int tokenIndex;
                    cout << "Enter the token number: ";
                    cin >> tokenIndex;
                    if (tokenIndex < numTokens) {
                        if (tokenPosition[tokenIndex] == -1 && tokenDistance[tokenIndex] == -1) {
                            tokenDistance[tokenIndex] = 0;
                            tokenPosition[tokenIndex] = startingPoint;
                            break;
                        } else {
                            // Update the old position to null texture value
                            playGroundGrids[tokenPosition[tokenIndex]].setTexture(nullptr);
                            moveToken(tokenIndex, dvalue);
                            break;
                        }
                    } else {
                        cout << "Invalid token number" << endl;
                    }
                }
            } else { // If the dice value is not 6
                while (true) {
                    int tokenIndex;
                    cout << "Enter the token number: ";
                    cin >> tokenIndex;
                    if (tokenCheckInPlay(tokenIndex)) {
                        if (tokenDistance[tokenIndex] + dvalue <= 51) {
                            // Update the old position to null texture value
                            playGroundGrids[tokenPosition[tokenIndex]].setTexture(nullptr);
                            moveToken(tokenIndex, dvalue);
                            break;
                        } else {
                            cout << "Token " << tokenIndex << " cannot move " << dvalue << " steps. It will exceed the board limit." << endl;
                        }
                    } else {
                        cout << "You need a 6 to start the token" << endl;
                    }
                }
            }
        }


        void moveToken(int tokenNumber, int distance){  // 50
            if(tokenDistance[tokenNumber] + distance >= 50 && tokenDistance[tokenNumber] + distance <= 55 && killCount > 0){
                tokenDistance[tokenNumber] += distance;
                homeGrids[distance].setTexture(&tokenTexture);
                return;
            }
            if(tokenDistance[tokenNumber] >= 56 && killCount > 0){
                tokenDistance[tokenNumber] = -100;
                tokenPosition[tokenNumber] = -100;
                return;
            }
            playGroundGrids[tokenPosition[tokenNumber]].setTexture(NULL);
            tokenPosition[tokenNumber] = (tokenPosition[tokenNumber]+distance)%52;
            tokenDistance[tokenNumber] += distance;
        }

        bool checkInPlay(){
            for(int i=0; i<numTokens; ++i){
                if(tokenPosition[i] != -1 && tokenDistance[i] != -1)
                    return true;
            }
            return false;
        }

        bool hasSix(){
            for(int i=0; i<diceValues.size(); ++i){
                if(diceValues[i] == 6)
                    return true;
            }
            return false;
        }
        bool tokenCheckInPlay(int tokenNumber){
            if(tokenPosition[tokenNumber] != -1 && tokenDistance[tokenNumber] != -1)
                return true;
            return false;
        }
        bool contains3Sixes(){
            int count = 0;
            for(int i=0; i<diceValues.size(); ++i){
                if(diceValues[i] == 6)
                    count++;
            }
            if(count >= 3)
                return true;
            return false;
        }
};