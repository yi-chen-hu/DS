//********************************************
// Student Name			:
// Student ID			:
// Student Email Address:
//********************************************
//
// Prof. Sai-Keung Wong
// Email:	cswingo@nycu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2022/04/25
//
#include "mySystem_2048.h"
#include <iostream>

using namespace std;

static unsigned char specialKeys[] = {
    GLUT_KEY_UP,
    GLUT_KEY_DOWN,
    GLUT_KEY_LEFT,
    GLUT_KEY_RIGHT
};

int numSpecialKeys = sizeof(specialKeys)/sizeof(unsigned char);

MY_2048::MY_2048( )
{
    mNX = 4;
    mNZ = 4;
    reset( );

    mPositionX = 0;
    mPositionZ = 0;
    mFlgFocus = true;
    //
    flg_AutoPlay = false;
    for (int j = 0; j < mNZ; ++j) {
        for (int i = 0; i < mNX; ++i) {
            mBoard[j][i] = 0;
        }
    }
}

MY_2048::MY_2048( int nx, int nz )
{
    mPositionX = 0;
    mPositionZ = 0;
    mFlgFocus = true;
    //
    // Implement your own stuff
    //
    mNX = nx;
    mNZ = nz;
    reset();
    //
    flg_AutoPlay = false;
}

void MY_2048::setDimension(int nx, int nz)
{
    mFlgFocus = true;
    
    //
    // Implement your own stuff
    //
    mNX = nx;
    mNZ = nz;
}


void MY_2048::setFocus( bool flg )
{
    mFlgFocus = flg;
}

void MY_2048::setPosition( int x, int z )
{
    mPositionX = x;
    mPositionZ = z;
}

void MY_2048::setPreviousBoard()
{
    for (int j = 0; j < mNZ; ++j) {
        for (int i = 0; i < mNX; ++i) {
            mPreviousBoard[j][i] = mBoard[j][i];
        }
    }

}

//
// Copy the m's previous board 
// to the object's mBoard.
//
void MY_2048::copyPrevious(const BASE_SYSTEM* m)
{
    for ( int j = 0; j < mNZ; ++j ) {
        for ( int i = 0; i < mNX; ++i ) {
            this->mBoard[ j ][ i ] = ((MY_2048*)m)->mPreviousBoard[ j ][ i ];
        }
    }
}

//
//reset the game board
//
void MY_2048::reset( )
{
    mEvent = 0;
    ///////////////////////////////////////
    //
    // Implement your own stuff
    //
    mFlgFocus = true;
    flg_AutoPlay = false;
    for (int j = 0; j < mNZ; ++j) {
        for (int i = 0; i < mNX; ++i) {
            mBoard[j][i] = 0;
        }
    }
    setPreviousBoard();
}

//
// show messages and ask for input (if any)
//
void MY_2048::askForInput( )
{
    //
    // Implement your own stuff
    //
    cout << "MY_2048" << endl;
    cout << "Key usage:" << endl;
    cout << "1: generate randomly the numbers 2 and 4 for all the cells" << endl;
    cout << "2: generate randomly the numbers 2, 4 and 8 for all the cells" << endl;
    cout << "3: generate randomly the numbers for all the cells" << endl;
    cout << "r: clear all the cells" << endl;
    cout << " " << endl;
    cout << "UP, DOWN, LEFT, RIGHT: move the numbers to the respective side" << endl;

}

//
// randomly generate a new number
//
void MY_2048::generateNumber( )
{
    //
    // Implement your own stuff
    //
    for (int j = mNZ - 1; j >= 0 ; j--)
    {
        for (int i = mNX - 1; i >= 0; i--)
        {
            if (mBoard[j][i] == 0)
            {
                mBoard[j][i] = 2 << (rand() % 2);
                return;
            }
        }
    }
    
}


void MY_2048::rotateClockwise()
{
    for (int i = 0; i < mNX / 2; i++)
    {
        for (int j = i; j < mNX - i - 1; j++)
        {
            // Swapping elements after each iteration in Anticlockwise direction
            int temp = mBoard[i][j];
            mBoard[i][j] = mBoard[j][mNX - i - 1];
            mBoard[j][mNX - i - 1] = mBoard[mNX - i - 1][mNX - j - 1];
            mBoard[mNX - i - 1][mNX - j - 1] = mBoard[mNX - j - 1][i];
            mBoard[mNX - j - 1][i] = temp;
        }
    }
}

void MY_2048::rotateCounterClockwise()
{
    for (int i = 0; i < mNX / 2; i++)
    {
        for (int j = i; j < mNX - i - 1; j++)
        {
            // Swapping elements after each iteration in Clockwise direction
            int temp = mBoard[i][j];
            mBoard[i][j] = mBoard[mNX - 1 - j][i];
            mBoard[mNX - 1 - j][i] = mBoard[mNX - 1 - i][mNX - 1 - j];
            mBoard[mNX - 1 - i][mNX - 1 - j] = mBoard[j][mNX - 1 - i];
            mBoard[j][mNX - 1 - i] = temp;
        }
    }
}

void MY_2048::moveDown( )
{
    //
    // Implement your own stuff
    // 
    for (int i = 0; i < mNX; i++)
    {
        int b[10] = { 0 };
        int j = 0;
        int z = 0;
        while (j < mNZ)
        {
            if (mBoard[j][i] == 0)
            {
                j++;
                continue;
            }
            if (j == mNZ - 1)
            {
                b[z++] = mBoard[j][i];
                break;
            }
            for (int k = j + 1; k < mNZ; k++)
            {
                if (mBoard[k][i] == 0 && k == mNZ - 1)
                {
                    b[z++] = mBoard[j][i];
                    j++;
                    break;
                }
                if (mBoard[k][i] == 0)
                {
                    continue;
                }
                if (mBoard[j][i] == mBoard[k][i])
                {
                    b[z++] = mBoard[j][i] * 2;
                    j = k + 1;
                    break;
                }
                else
                {
                    b[z++] = mBoard[j][i];
                    j++;
                    break;
                }
            }
        }
        for (int j = 0; j < mNZ; j++)
        {
            mBoard[j][i] = b[j];
        }
    }
}

void MY_2048::moveUp( )
{
    //
    // Implement your own stuff
    //
    rotateClockwise();
    rotateClockwise();
    moveDown();
    rotateCounterClockwise();
    rotateCounterClockwise();

}

void MY_2048::moveLeft( )
{
    //
    // Implement your own stuff
    //
    rotateCounterClockwise();
    moveDown();
    rotateClockwise();
}

void MY_2048::moveRight( )
{
    //
    // Implement your own stuff
    //
    rotateClockwise();
    moveDown();
    rotateCounterClockwise();
}

void MY_2048::generateNumbers_All_2to4( )
{
    //
    // Implement your own stuff
    //
    for (int i = 0; i < mNX; i++)
    {
        for (int j = 0; j < mNZ; j++)
        {
            mBoard[i][j] = 2 << (rand() % 2);
        }
    }
    
}

void MY_2048::generateNumbers_All_2to8( )
{
    //
    // Implement your own stuff
    //
    for (int i = 0; i < mNX; i++)
    {
        for (int j = 0; j < mNZ; j++)
        {
            mBoard[i][j] = 2 << (rand() % 3);
        }
    }
}

void MY_2048::generateNumbers_All( )
{
    //
    // Implement your own stuff
    //
    for (int i = 0; i < mNX; i++)
    {
        for (int j = 0; j < mNZ; j++)
        {
            mBoard[i][j] = 2 << (rand() % 9);
        }
    }
}

void MY_2048::handleKeyPressedEvent( unsigned char key )
{
    switch( key ) {
    case 'r':
    case 'R':
        reset( );
        break;
    case '1':
        reset();
        generateNumbers_All_2to4( );
        break;
    case '2':
        reset();
        generateNumbers_All_2to8( );
        break;
    case '3':
        reset();
        generateNumbers_All( );
        break;

    case 'a':
    case 'A':
        //flg_AutoPlay
        //for one step
        performAction(getBestAction(7));
        break;
    case ' ':
        // toggle to auto-play
        flg_AutoPlay = !flg_AutoPlay;
        break;
    }
}

int MY_2048::evaluateScore()
{
    int score = 0;
    for (int i = 0; i < mNX; i++)
    {
        for (int j = 0; j < mNZ; j++)
        {   
            score += mBoard[j][i] * mBoard[j][i];
        }
    }
    return score;
}

int MY_2048::performAction_Recur(unsigned char key, int d)
{
    performAction(key);
    int score = 0;
    int bestScore = 0;
    if (d == 0)
    {
        score = evaluateScore();
        return score;
    }
    int b[10][10];

    //up
    for (int i = 0; i < mNX; i++)
    {
        for (int j = 0; j < mNZ; j++)
        {
            b[j][i] = mBoard[j][i];
        }
    }
    score = performAction_Recur(GLUT_KEY_UP, d - 1);
    for (int i = 0; i < mNX; i++)
    {
        for (int j = 0; j < mNZ; j++)
        {
            mBoard[j][i] = b[j][i];
        }
    }
    if (score > bestScore)
        bestScore = score;

    //down
    for (int i = 0; i < mNX; i++)
    {
        for (int j = 0; j < mNZ; j++)
        {
            b[j][i] = mBoard[j][i];
        }
    }
    score = performAction_Recur(GLUT_KEY_DOWN, d - 1);
    for (int i = 0; i < mNX; i++)
    {
        for (int j = 0; j < mNZ; j++)
        {
            mBoard[j][i] = b[j][i];
        }
    }
    if (score > bestScore)
        bestScore = score;

    //left
    for (int i = 0; i < mNX; i++)
    {
        for (int j = 0; j < mNZ; j++)
        {
            b[j][i] = mBoard[j][i];
        }
    }
    score = performAction_Recur(GLUT_KEY_LEFT, d - 1);
    for (int i = 0; i < mNX; i++)
    {
        for (int j = 0; j < mNZ; j++)
        {
            mBoard[j][i] = b[j][i];
        }
    }
    if (score > bestScore)
        bestScore = score;

    //right
    for (int i = 0; i < mNX; i++)
    {
        for (int j = 0; j < mNZ; j++)
        {
            b[j][i] = mBoard[j][i];
        }
    }
    score = performAction_Recur(GLUT_KEY_RIGHT, d - 1);
    for (int i = 0; i < mNX; i++)
    {
        for (int j = 0; j < mNZ; j++)
        {
            mBoard[j][i] = b[j][i];
        }
    }
    if (score > bestScore)
        bestScore = score;

    return bestScore;
}

unsigned char MY_2048::getBestAction(int d)
{
    int bestScore = -1;
    int score = 0;
    int b[10][10];
    unsigned char bestAction = 0;
    if (d <= 0)
        return bestAction;

    //up
    for (int i = 0; i < mNX; i++)
    {
        for (int j = 0; j < mNZ; j++)
        {
            b[j][i] = mBoard[j][i];
        }
    }
    score = performAction_Recur(GLUT_KEY_UP, d - 1);
    for (int i = 0; i < mNX; i++)
    {
        for (int j = 0; j < mNZ; j++)
        {
            mBoard[j][i] = b[j][i];
        }
    }
    if (score > bestScore)
    {
        bestScore = score;
        bestAction = GLUT_KEY_UP;
    }

    //down
    for (int i = 0; i < mNX; i++)
    {
        for (int j = 0; j < mNZ; j++)
        {
            b[j][i] = mBoard[j][i];
        }
    }
    score = performAction_Recur(GLUT_KEY_DOWN, d - 1);
    for (int i = 0; i < mNX; i++)
    {
        for (int j = 0; j < mNZ; j++)
        {
            mBoard[j][i] = b[j][i];
        }
    }
    if (score > bestScore)
    {
        bestScore = score;
        bestAction = GLUT_KEY_DOWN;
    }

    //left
    for (int i = 0; i < mNX; i++)
    {
        for (int j = 0; j < mNZ; j++)
        {
            b[j][i] = mBoard[j][i];
        }
    }
    score = performAction_Recur(GLUT_KEY_LEFT, d - 1);
    for (int i = 0; i < mNX; i++)
    {
        for (int j = 0; j < mNZ; j++)
        {
            mBoard[j][i] = b[j][i];
        }
    }
    if (score > bestScore)
    {
        bestScore = score;
        bestAction = GLUT_KEY_LEFT;
    }

    //right
    for (int i = 0; i < mNX; i++)
    {
        for (int j = 0; j < mNZ; j++)
        {
            b[j][i] = mBoard[j][i];
        }
    }
    score = performAction_Recur(GLUT_KEY_RIGHT, d - 1);
    for (int i = 0; i < mNX; i++)
    {
        for (int j = 0; j < mNZ; j++)
        {
            mBoard[j][i] = b[j][i];
        }
    }
    if (score > bestScore)
    {
        bestScore = score;
        bestAction = GLUT_KEY_RIGHT;
    }

    return bestAction;
}

void MY_2048::performAction( unsigned char key ) {
bool flgDone = false;

    switch( key ) {
    case GLUT_KEY_UP:
        flgDone = true;
        setPreviousBoard();
        moveUp( );
        mEvent = GLUT_KEY_UP;
        break;
    case GLUT_KEY_DOWN:
        flgDone = true;
        setPreviousBoard();
        moveDown( );
        mEvent = GLUT_KEY_DOWN;

        break;
    case GLUT_KEY_LEFT:
        flgDone = true;
        setPreviousBoard();
        moveLeft( );
        mEvent = GLUT_KEY_LEFT;

        break;
    case GLUT_KEY_RIGHT:
        flgDone = true;
        setPreviousBoard();
        moveRight( );
        mEvent = GLUT_KEY_RIGHT;

        break;

    }

    if ( flgDone ) {
        generateNumber( );
    }
}

void MY_2048::handleSpecialKeyPressedEvent( unsigned char key )
{
    //
    // It takes a long time to show a message!
    //
    cout << "MY_2048::handleSpecialKeyPressedEvent:" << key << endl;
    performAction( key );
}

bool MY_2048::isAutoPlay() const
{
    return flg_AutoPlay;
}

//
// The update( ) function is called every frame.
//
// Design an algorithm to automatically perform
// one step.
//
void MY_2048::update( )
{
    //
    // It takes a long time to show a message!
    //
    cout << "MY_2048::update( )" << endl;
    cout << "MY_2048::flg_AutoPlay:\t" << flg_AutoPlay << endl;
    performAction(getBestAction(7));
    if (!flg_AutoPlay) return;

    //
    // Implement your own stuff
    //
}
