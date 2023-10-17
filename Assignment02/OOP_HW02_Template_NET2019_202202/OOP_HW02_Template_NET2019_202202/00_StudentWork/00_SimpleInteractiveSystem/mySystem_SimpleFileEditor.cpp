//
// Instructor: Sai-Keung WONG
// Email:	cswingo@nycu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2022/03/17
//
#include "mySystem_SimpleFileEditor.h"
#include <iostream>
#include <fstream>
using namespace std;

#define FILE_NAME "oop.txt"

SIMPLE_FILE_EDITOR::SIMPLE_FILE_EDITOR( )
{
    //BEGIN: DO NOT CHANGE
    mNX = 100; // number of columns
    mNY = 100; // number of rows
    mBitmap = new int[mNX*mNY];
    for ( int i = 0; i < mNX*mNY; ++i ) {
        mBitmap[ i ] = 0;
    }
    readFile( );
    //END: DO NOT CHANGE

}

/*
Set up the bitmap based on the data stored in a file.

Each line in the file is mapped to one row
of the bitmap in a consecutive manner.

Steps:
Open the file.
Read a file.
 Repeat until EOF
   read a line from the file each time
   set the bitmap based on the current line
Close the file.
*/
void SIMPLE_FILE_EDITOR::readFile( )
{
    mCurX = 0;
    mCurY = 0;
    ifstream inFile;
    inFile.open( FILE_NAME );
    string inputString;
    //
    // fill/modify your own stuff
    //
    
    while ( inFile ) {
        getline(inFile, inputString );
        if (inputString.size() == 0)
            continue;
        storeOneRowToBitmap(inputString);
    }
    
    inFile.close( );
}

/*
Set one row of the bitmap based on the input string inputString.
The elements of the row are mapped one to one to the input string.

The element of a bitmap is set as follows.

If inputString[i] is the space character, 
the value of the element is set as 0.
Otherwise, the value of the element is set to (int) inputString[i].
*/
void SIMPLE_FILE_EDITOR::storeOneRowToBitmap( const string &inputString )
{
    if (mCurY>= mNY) return;
    //
    // fill/modify your own stuff
    //
    for (mCurX = 0; mCurX < mNX; mCurX++)
    {
        int index = mCurX + mCurY * mNX;
        if (inputString[mCurX] == ' ')
            mBitmap[index] = 0;
        else
            mBitmap[index] = inputString[mCurX];
    }
    ++mCurY;
}

/*
Show the system title.
Show "No input is required!".
*/
void SIMPLE_FILE_EDITOR::askForInput( )
{
    //Show the system title
    //
    cout << "SIMPLE_FILE_EDITOR" << endl;
    cout << "<: rotate to left" << endl;
    cout << ">: rotate to right" << endl;
}

/*
Get the dimension of the bitmap to (nx, ny).
nx : number of columns
ny : number of rows
*/
void SIMPLE_FILE_EDITOR::getBitmapDimension(int &nx, int &ny) const
{
    nx = mNX;
    ny = mNY;
}

/*
Return the bitmap value at (x, y).
x : column index
y : row index
*/
int SIMPLE_FILE_EDITOR::getBitmapValue(int x, int y) const
{
    //
    // fill/modify your own stuff
    //
    int index = x + y*mNX;
    return mBitmap[index];
}

bool SIMPLE_FILE_EDITOR::handleKeyPressedEvent( int key )
{
    bool flg =false;
    switch(key) {
    case '<':
        rotateToLeft( );
        flg = true;
        break;
        case '>':
        rotateToRight( );
        flg = true;
        break;
    }

    return flg;
}


void SIMPLE_FILE_EDITOR::rotateToLeft( )
{

    for ( int j = 0; j < mNY; ++j ) {
        int temp;
        temp = mBitmap[0 + j * mNX];
        for (int i = 0; i < mNX - 1; i++)
        {
            mBitmap[i + j * mNX] = mBitmap[i + 1 + j * mNX];
        }
        mBitmap[mNX - 1 + j * mNX] = temp;
    }
}

void SIMPLE_FILE_EDITOR::rotateToRight( )
{
    for ( int j = 0; j < mNY; ++j ) {
        int temp;
        temp = mBitmap[mNX - 1 + j * mNX];
        for (int i = mNX -1; i > 0; i--)
        {
            mBitmap[i + j * mNX] = mBitmap[i - 1 + j * mNX];
        }
        mBitmap[0 + j * mNX] = temp;
    }
}
