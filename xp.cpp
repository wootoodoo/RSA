#include "XP.h"

using namespace std;


XP XPinitDecimal(string s) {
   XP a;
   int length = s.size(); 
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
   unsigned char sum[NN] = {0};
   XP c = XPinitDecimal("0");

   for (int i = NN - 1; i > 0; i--) {
      char x = a.digit[i] + b.digit[i] + sum[i];
      if (x > 0 && i < NN - 1) c.length++;
      if (x > 9) {
         sum[i - 1] = 1;
         x -= 10;
      }
      c.digit[i] = x;
   }
   return c;
}

XP XPrand(int n) {
   int x;
   stringstream ss;

   srand (time(NULL));
   for (int i = 0; i < n; i++) {
      x = rand() % 10;
      ss << x;
   }
   XP out = XPinitDecimal(ss.str());
   return out;
}

bool XPisOdd(XP a) {
   char lastDigit = a.digit[NN - 1];
   return lastDigit % 2 == 1;
}

int XPgreater(XP a, XP b) {
   if (a.length > b.length) {return 1;}
   if (a.length == b.length) {
      for (int i = 0; i < a.length; i++) {
         if (a.digit[NN - a.length + i] > b.digit[NN - a.length + i]) {return 1;}
         if (a.digit[NN - a.length + i] == b.digit[NN - a.length + i]) {continue;}
         else break;
      }
   }
   return -1;
}

int XPless(XP a, XP b) {
   if (a.length < b.length) {return 1;}
   if (a.length == b.length) {
      for (int i = 0; i < a.length; i++) {
         if (a.digit[NN - a.length + i] < b.digit[NN - a.length + i]) {return 1;}
         if (a.digit[NN - a.length + i] == b.digit[NN - a.length + i]) {continue;}
         else break;
      }
   }
   return -1;
}

int XPeq(XP a, XP b) {
   if (a.length == b.length) {
      for (int i = 0; i < a.length; i++) {
         if (i == a.length - 1 && a.digit[NN - a.length + i] == b.digit[NN - a.length + i]) {return 1;}
         if (a.digit[NN - a.length + i] == b.digit[NN - a.length + i]) {continue;}
         else break;
      }
   }
   return -1;
}

XP XPsub(XP a, XP b) {
   if (XPless(a, b) == 1) throw "first XP is less than 2nd XP!";
   unsigned char sub[NN] = {0};

   for (int i = NN - 1; i >= NN - a.length; i--) {
      if (a.digit[i] == 0) {
         a.digit[i] += 10;
         sub[i - 1]++;
      }
      a.digit[i] -= sub[i];
      if (i == NN - a.length && a.digit[i] == 0) {
         a.length--;
      }
      if (a.digit[i] < b.digit[i]) {
         a.digit[i] += 10;
         sub[i - 1]++;
      }
      a.digit[i] -= b.digit[i];
   }
   return a;
}

int main() {
   XP a, b, c;
   
   try {
      a = XPinitDecimal("1234567890");   // a   = 123456789
      b = XPinitDecimal("545454545");    // b   =  54545454
      c = XPadd(a, b);                  // c   =  a + b
      XPshowDecimal(c);                 // print 178002243
      XPshowDecimal(XPrand(99));
      printf(XPisOdd(c) ? "true" : "false");
      cout << endl;
      printf("%d\n", XPgreater(a, b));
      printf("%d\n", XPless(b, a));
      printf("%d\n", XPeq(a, a));
      XPshowDecimal(XPsub(a, b));
   } catch (string msg) {
      cout << msg << endl;
   }

}