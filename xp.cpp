#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;

#define N  100         // maximum number of digits supported
#define NN (2*N + 1)   // number of digits allocated

typedef struct {
   unsigned char digit[NN];
   int length;
} XP;

XP XPinitDecimal(string s) {
   XP a;
   int length = s.size(); //sizeof(s)/sizeof(s[0]);
   a.length = length;
   if (length > N) throw "length of input is larger than N!";

    for (int i = 0; i < length; i++) {
       if (s[i] > '9' || s[i] < '0') throw "The digits are out of range";
        a.digit[NN - length + i] = s[i] - '0';
    }
    for (int i = 0; i < NN - length; i++) {
       a.digit[i] = 0;
    }
    return a;
}

void XPshowDecimal(XP c) {
   for (int i = 0; i < c.length; i++) {
      printf("%d", c.digit[NN - c.length + i]);
      }
      cout << endl;
}

XP XPadd(XP a, XP b) {
   unsigned char sum[NN];
   XP c;
   int count = 0;

   for (int i = NN - 1; i >= 0; i--) {
      char x = a.digit[i] + b.digit[i] + sum[i];
      if (x > 9) {
         sum[i - 1] = 1;
         x -= 10;
      }
      c.digit[i] = x;
      if (x > 0) count++;
   }
   c.length = count;
   
   return c;
}

int main() {
   XP a, b, c;
   
   
   try {
      a = XPinitDecimal("123456789");   // a   = 123456789
      b = XPinitDecimal("54545454");    // b   =  54545454
      c = XPadd(a, b);                  // c   =  a + b
      XPshowDecimal(c);                 // print 178002243
   } catch (string msg) {
      cerr << msg << endl;
   }

}

