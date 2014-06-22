//
//  ofCharacter.cpp
//  relationGame
//
//  Created by Emrys on 6/20/14.
//

#include "ofCharacter.h"
#define WAITTIME 4
#define WALKTIME 10

// Default Constructor - Used to create a character
ofCharacter::ofCharacter( string name, string introduction, int attraction, string bodyPath, string basePath, string eyesPath, string hairPath, string shoesPath, string topsPath, string bottomsPath, float x, float y, float speedX, float speedY )
    : name(name), introduction( introduction), attraction(attraction), x(x), y(y), imgX(0), currentPos(4), dirX(0), dirY(0), speedX( speedX ), speedY( speedY ), range( ofRandom( 1, 5 ) ), isWalking( true )
{
    charImage.loadImage( bodyPath );
    baseImage.loadImage( basePath );
    eyesImage.loadImage( eyesPath );
    hairImage.loadImage( hairPath );
    shoesImage.loadImage( shoesPath );
    topsImage.loadImage( topsPath );
    bottomsImage.loadImage( bottomsPath );
    
    genColor( charColor );
    genColor( eyesColor );
    genColor( hairColor );
    genColor( shoesColor );
    genColor( topsColor );
    genColor( bottomsColor );

    footSpace =charImage.getHeight() / 5;
    footRect = ofRectangle(x, y + MAPHEIGHT - footSpace, MAPWIDTH, footSpace );
    
    startTime = ofGetElapsedTimeMillis();

}

ofCharacter::~ofCharacter(){};


void ofCharacter::genColor( ofColor& var ){
    var.r = static_cast<int>( ofRandom( 0, 255 ) );
    var.g = static_cast<int>( ofRandom( 0, 255 ) );
    var.b = static_cast<int>( ofRandom( 0, 255 ) );
}

// Update Method - Used to refresh character's properties

void ofCharacter::update( bool player){
    
    if ( player ){
        if( x < 0 ){ x = 0 ;}
        else if (x + MAPWIDTH > (ofGetWidth() / 4) * 3 ) { x = (ofGetWidth() / 4) * 3 - MAPWIDTH; }
        if( y < 0 ){ y = 0 ;}
        else if (y + MAPHEIGHT > ofGetHeight() ) { y = ofGetHeight() - MAPHEIGHT; }
        x += dirX * speedX;
        y += dirY * speedY;
    }
    else{
        
        
        if( isWalking ) {
            
            // Every PROBTIME seconds, check if it is time to alter between walking and standing
            if( ofGetElapsedTimeMillis() - startTime > WALKTIME * 1000 ){
                if( ofRandom( -1, 1 ) > 0 ) { isWalking = !isWalking; }
                startTime = ofGetElapsedTimeMillis();
            }
            
            if( x < 0 ){
                x = 0;
                speedX *= ofRandom(-1.5, -0.5);
            } else if( x + MAPWIDTH > (ofGetWidth() / 4) * 3 ){
                x = (ofGetWidth() / 4) * 3 - MAPWIDTH;
                speedX *= ofRandom(-1.5, -0.5);
            }
            
            if( y < 0 ){
                y = 0;
                speedY *= ofRandom(-1.5, -0.5);
            } else if( y + MAPHEIGHT > ofGetHeight() ){
                y =  ofGetHeight() - MAPHEIGHT;
                speedY *= ofRandom(-1.5, -0.5);
            }
            
            x += speedX;
            y += speedY;
            
            if( speedX > 0 ) { dirX = 1; }
            else if( speedX == 0 ) { dirX = 0; }
            else if( speedX < 0 ) { dirX = -1; }
            
            if( speedY > 0 ) { dirY = 1; }
            else if( speedY == 0 ) { dirY = 0; }
            else if( speedY < 0 ) { dirY = -1; }
        }
        else {
            // Every PROBTIME seconds, check if it is time to alter between walking and standing
            if( ofGetElapsedTimeMillis() - startTime > WAITTIME * 1000 ){
                if( ofRandom( -1, 1 ) > 0 ) { isWalking = !isWalking; }
                startTime = ofGetElapsedTimeMillis();
            }
        }
    }
    
    if( isWalking ){
        // LEFT: X = -1, Y = 0
        if( dirX == -1 ){
            animateWalkLeft();
        }
        // RIGHT: X = 1, Y = 0
        else if( dirX == 1 ){
            animateWalkRight();
        }
        // UP: X = 0, Y = -1
        else if( dirY == -1 ){
            animateWalkBackward();
        }
        // DOWN: X = 0, Y = 1
        else if( dirY == 1 ){
            animateWalkForward();
        }

    }
    
    footRect.setPosition(x, y + MAPHEIGHT - footSpace );
    
}





bool ofCharacter::timeToTransition(){
    if( ofGetElapsedTimeMillis() - targetTime > 100 ){
        targetTime = ofGetElapsedTimeMillis();
        return true;
    }
    return false;
}

void ofCharacter::animateWalkLeft(){
    if( timeToTransition() ){
        currentPos++;
        if( currentPos >= 4 ) { currentPos = 0; }
    }
}

void ofCharacter::animateWalkForward(){
    if( timeToTransition() ){
        currentPos++;
        if( currentPos >= 8 ) { currentPos = 4; }
    }
}

void ofCharacter::animateWalkRight(){
    if( timeToTransition() ){
        currentPos++;
        if( currentPos >= 12 ) { currentPos = 8; }    }
}

void ofCharacter::animateWalkBackward(){
    if( timeToTransition() ){
        currentPos++;
        if( currentPos >= 16 ) { currentPos = 12; }
    }
}

// Update Method - Used to refresh character's properties
void ofCharacter::draw(){
    ofSetColor( 120, 120, 120, 100 );
    ofEllipse( x + MAPWIDTH/2,
              y + MAPHEIGHT,
              range * (MAPHEIGHT) / 2,
              range * (MAPHEIGHT) / 4 );
    
    ofSetColor( charColor );
    charImage.drawSubsection( x, y, MAPWIDTH, MAPHEIGHT, MAPWIDTH * currentPos, 0);
    
    ofSetColor( 255, 255, 255 );
    baseImage.drawSubsection( x, y, MAPWIDTH, MAPHEIGHT, MAPWIDTH * currentPos, 0);
    
    ofSetColor( eyesColor );
    eyesImage.drawSubsection( x, y, MAPWIDTH, MAPHEIGHT, MAPWIDTH * currentPos, 0);
    
    ofSetColor( shoesColor );
    shoesImage.drawSubsection( x, y, MAPWIDTH, MAPHEIGHT, MAPWIDTH * currentPos, 0);
    
    ofSetColor( bottomsColor );
    bottomsImage.drawSubsection( x, y, MAPWIDTH, MAPHEIGHT, MAPWIDTH * currentPos, 0);
    
    ofSetColor( topsColor );
    topsImage.drawSubsection( x, y, MAPWIDTH, MAPHEIGHT, MAPWIDTH * currentPos, 0);
    
    ofSetColor( hairColor );
    hairImage.drawSubsection( x, y, MAPWIDTH, MAPHEIGHT, MAPWIDTH * currentPos, 0);
    
    ofSetColor( 255, 255, 255, 100 );
    ofRect(footRect.x, footRect.y, footRect.width, footRect.height );
    
}