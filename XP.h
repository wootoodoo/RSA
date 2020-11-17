#include <iostream>
#include <stdio.h>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <sstream>

#define N  100         // maximum number of digits supported
#define NN (2*N + 1)   // number of digits allocated

typedef struct {
   unsigned char digit[NN];
   int length;
} XP;

XP XPinitDecimal(std::string s);
XP XPadd(XP a, XP b);
XP XPrand(int n);
bool XPisOdd(XP a);
int XPgreater(XP a, XP b);
int XPless(XP a, XP b);
int XPeq(XP a, XP b);
XP XPsub (XP a, XP b);