#include <iostream>
#include <stdio.h>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <sstream>

#define N  100         // maximum number of digits supported
#define NN (2*N + 1)   // number of digits allocated

typedef struct {        // struct to help with the extended precision arithmetic
   unsigned char digit[NN];
   int length;
} XP;

typedef struct {        // struct to help with the calculation of Division
   XP quotient;
   XP remainder;
} Div;

XP XPinitDecimal(std::string s);    // Initialises a extended precision decimal based on a input string, up to a 100 digits
XP XPadd(XP a, XP b);               // Prints out the extended precision number in full
XP XPrand(int n);                   // Generate a pseudo-random number based on the clock, of length n
bool XPisOdd(XP a);                 // Determines if a extended precision number is odd   
int XPgreater(XP a, XP b);          // If a is greater than b, then return 1. Else it returns -1
int XPless(XP a, XP b);             // If a is less than b, then return 1. Else it returns -1
int XPeq(XP a, XP b);               // If a is equal to b, then return 1. Else it returns -1
XP XPsub(XP a, XP b);               // Multiplication of a and b
Div XPdiv(XP a, XP b);              // Division of a by b, returns the quotient and remainder in Div struct