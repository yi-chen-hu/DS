//
// Instructor: Sai-Keung WONG
// Email:	cswingo@cs.nctu.edu.tw
//			wingo.wong@gmail.com
//
// National Chiao Tung University, Taiwan
// Computer Science
// Date: 2019/03/17
//
#include <iostream>

/*
Generate a random numbe 
between x0 and x1 (inclusive).
*/
double getRandDouble(double x0, double x1)
{
    int r = rand();
    double f = r/(double)RAND_MAX;
    return x0 + f*(x1-x0);
}