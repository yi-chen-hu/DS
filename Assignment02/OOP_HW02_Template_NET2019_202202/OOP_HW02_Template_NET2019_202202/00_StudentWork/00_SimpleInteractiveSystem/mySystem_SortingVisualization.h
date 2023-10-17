//
// Instructor: Sai-Keung WONG
// Email:	cswingo@nycu.edu.tw
//			wingo.wong@gmail.com
//
// National Yang Ming Chiao Tung University, Taiwan
// Computer Science
// Date: 2022/03/17
//
/*
Visualizing the process of sorting some integers.
*/
#ifndef __MY_SORTING_VISUALIZATION_H_
#define __MY_SORTING_VISUALIZATION_H_
#include "../headers.h"
#include <string>
#include "../primitives/vector3d.h"
#include <vector>
#include "base_class.h"
using std::vector;
class SORTING_VISUALIZATION : public BASE_SYSTEM
{
protected:
    vector<int> mNumbers;
    int mNumElements;
    int mMinValue, mMaxValue;
    int mCurrentIndex;
    int mMaxNonHandledElementIndex;
//
    void checkAndSwapTwoElements( int index );
public:
    SORTING_VISUALIZATION( );
    bool handleKeyPressedEvent(int key);
    void reset( );
    void askForInput( );
    int getNumOfElements( ) const;
    int getElement( int elementIndex ) const;
    int getMaxNonHandledElementIndex( ) const;
    void processOneSwapStep( );
    int getCurrentElementIndex( ) const;
    //
    int getMinOfInterval() const;
    int getMaxOfInterval() const;
};
#endif