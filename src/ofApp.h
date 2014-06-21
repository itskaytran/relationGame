#pragma once
#ifndef _0F_APP
#define _0F_APP

#include "ofMain.h"
#include "ofCharacter.h"
#include "ofMinigame.h"
#include "ofxTextSuite.h"
#include <sstream>

#define MINIGAMETIME 1
#define INSTRUCTLENGTH 7
#define NUMBEROFCHARACTERS 10

#define NUMTOPS 1
#define NUMBOTTOMS 1
#define NUMEYES 1
#define NUMHAIR 1
#define NUMSHOES 1

class ofApp : public ofBaseApp{

public:
    // Public Methods
    void setup();
    void update();
    void resetFont();
    void draw();
    void quickSort( ofCharacter*[], int, int);

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    enum ScreenType { START, INSTRUCTIONS, PARTY, MINIGAME, PAUSE, ENDING };
    
private:
    ScreenType currentScreen, previousScreen;
    
    // Private Member Variables
    ofImage logo;
    ofImage screenBG;
    
    ofCharacter* player;
    
    int numOfCharacters;
    ofCharacter** characters; // Array of Characters
    
    ofMinigame* modeParty;
    
    char timerString[255];
    ofTrueTypeFont myFont;
    
    void mergeSortCharacters( ofCharacter** );
    
    ofxTextBlock        myText;
    TextBlockAlignment  alignment;
    
    float marginTop, lineSpacing;
    string instructions[ INSTRUCTLENGTH ] = {
        "NAME: ",
        "INSTRUCTIONS: ",
        "HOW DO YOU WANT TO INTRODUCE YOURSELF?"
    };
    
    string getRandNum( std::ostringstream&, int );

};

#endif