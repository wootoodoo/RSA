/*
This program is a helper program that will help to calculate integer arithmetic for up to a 100 digits in length
This is necessary for the calculations in the RSA algorithm
*/

#include "XP.h"

using namespace std;

XP XPinitDecimal(string s) {     // Initialises a extended precision decimal based on a input string, up to a 100 digits
   XP a;
   int length = s.size(); 
   a.length = length;
   if (length > N) throw "length of input is larger than N!";

   for (int i = 0; i < length; i++) {
       if (s[i] > '9' || s[i] < '0') throw "The digits are out of range"; // catch any digit that is not between '0' and '9'
        a.digit[NN - length + i] = s[i] - '0';      // make all the char between 0 and 9 in ASCII
   }
   for (int i = 0; i < NN - length; i++) {
       a.digit[i] = 0;
   }
   return a;
}

void XPshowDecimal(XP c) {       // Prints out the extended precision number in full
   for (int i = 0; i < c.length; i++) {
      printf("%d", c.digit[NN - c.length + i]);
      }
      cout << endl;
}

XP XPadd(XP a, XP b) {        // Sums together 2 extended precision numbers
   unsigned char sum[NN] = {0};     // Create a new char array to store the overflow when 2 digits sum to more than 10
   XP c = XPinitDecimal("0");       
   int longer = max(a.length, b.length);

   for (int i = NN - 1; i > 0; i--) {
      if (i < NN - longer - 1) break;
      char x = a.digit[i] + b.digit[i] + sum[i];   
      if (i < NN - 1) {
         if (i == NN - longer - 1 && x == 0) break;
         c.length++;       // Increase the length of c for digits more than length 1 and up to 1 digit pass the longer length
      }
      if (x > 9) {
         sum[i - 1] = 1;   // Overflow when 2 digits sum to more than 10
         x -= 10;
      }
      c.digit[i] = x;
   }
   return c;
}

XP XPrand(int n) {      // Generate a pseudo-random number based on the clock, of length n
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

bool XPisOdd(XP a) {    // Determines if a extended precision number is odd
   char lastDigit = a.digit[NN - 1];
   return lastDigit % 2 == 1;
}

int XPgreater(XP a, XP b) {      // If a is greater than b, then return 1. Else it returns -1
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

int XPless(XP a, XP b) {         // If a is less than b, then return 1. Else it returns -1
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

int XPeq(XP a, XP b) {        // If a is equal to b, then return 1. Else it returns -1
   if (a.length == b.length) {
      for (int i = 0; i < a.length; i++) {
         if (i == a.length - 1 && a.digit[NN - a.length + i] == b.digit[NN - a.length + i]) {return 1;}
         if (a.digit[NN - a.length + i] == b.digit[NN - a.length + i]) {continue;}
         else break;
      }
   }
   return -1;
}

XP XPsub(XP a, XP b) {        // Subtract b from a
   if (XPless(a, b) == 1) throw "first XP is less than 2nd XP!";
   unsigned char sub[NN] = {0};     // Char array to store if next digit in a is required to +10 to current digit

   for (int i = NN - 1; i >= NN - a.length; i--) {
      if (a.digit[i] == 0) {        // Check if the least significant digit of a is 0, if so +10
         a.digit[i] += 10;      
         sub[i - 1]++;
      }
      a.digit[i] -= sub[i];         // Minus if this digit owes 1
      if (a.digit[i] < b.digit[i]) {  // Check if a is less than b, if so +10
         a.digit[i] += 10;
         sub[i - 1]++;
      }
      a.digit[i] -= b.digit[i];
   }
   int i = NN - a.length;
   while (a.digit[i] == 0 && i < NN) { // Make sure that the length of a is correct!
      a.length--;
      i++;
   }
   return a;
}

XP XPmul(XP a, XP b) {        // Multiplication of a and b
   int count = 0;       // count is used to store which digit of b we are on
   XP sum = XPinitDecimal("0");

   for (int x = NN - 1; x >= NN - b.length; x--) {       // For each digit in b
      unsigned char carryOver[NN] = {0};     // carryOver char array to the next digit of a
      unsigned char mul[NN] = {0};           // Used to store the multiplication answer
      int length = 0;                        // Store length of multiplication of a for this digit of b
      
      for (int y = 0; y <= a.length; y++) {        // For each digit in a
         unsigned char temp = b.digit[x] * a.digit[NN - 1 - y] + carryOver[NN - 1 - y];
         if (temp > 9) {         // carryOver if temp is more than 9
            carryOver[NN - 2 - y] = temp / 10;
            temp %= 10;
         }
         mul[NN - 1 - y] = temp;    
         if (y < a.length) length++;            // Up to the length of a
         if (y == a.length && temp != 0) length++; // Check if length of multiplication is longer than a
      }
      string add;
      for (int i = NN - length; i < NN; i++){      
         add.append(sizeof(char), mul[i] + '0');     // Generate the multiplication string, not forgetting to add back '0'
      }
      add.append(count, '0');             // Multiply by the correct number of 10s in b
      count++;
      sum = XPadd(sum, XPinitDecimal(add));  // add the multiplication into the total sum
   }
   return sum;
}

Div XPdiv(XP a, XP b) {          // Division of a by b, returns the quotient and remainder in Div struct
   Div result;

   if (XPless(a, b) == 1) {      // if (a < b)
      result.quotient = XPinitDecimal("0");
      result.remainder = a;
      return result;             // return (0, a)
   }
   
   result = XPdiv(a, XPmul(b, XPinitDecimal("2")));                     // (q, r) = div(a, 2b)
   result.quotient = XPmul(result.quotient, XPinitDecimal("2"));        //  q = 2q
   
   if (XPless(result.remainder, b) == 1) {      //  if (r < b) return (q, r)
      return result;
   }
   
   else {         // else return (q + 1, r - b)
      result.quotient = XPadd(result.quotient, XPinitDecimal("1"));
      result.remainder = XPsub(result.remainder, b);
   }
}

XP XPrsa(XP a, XP b, XP n) {                          // Does the RSA calculation a ^ b mod n
   XP t, c;
   if (XPgreater(b, XPinitDecimal("3")) == 1) {       // if b is larger than 3, need to recurse
      t = XPrsa(a, XPdiv(b, XPinitDecimal("2")).quotient, n);
      c = XPdiv(XPmul(t, t), n).remainder;            // c = (t * t) mod n
   }
   else if (XPeq(b, XPinitDecimal("3")) == 1) {       // special case for when b is equals to 3
      t = XPdiv(XPmul(a, a), n).remainder;
      c = XPdiv(XPmul(t, a), n).remainder;
   }
   else {                                             // b is equals to 2
      c = XPdiv(XPmul(a, a), n).remainder;
   }
   
   if (XPisOdd(b) && XPgreater(b, XPinitDecimal("3")) == 1) {        // if b is odd, must multiply by a one more time
      c = XPdiv(XPmul(c, a), n).remainder;
   }
   return c;
}

int main() {
   XP a, b, n;
   
   try {
      string in = "";

      while (true) // Code for debugging
      {
         XP result;
         cout << "a: ";
         getline(cin, in);
         a = XPinitDecimal(in);
         cout << "b: ";
         getline(cin, in);
         b = XPinitDecimal(in);
         cout << "n: ";
         getline(cin, in);
         n = XPinitDecimal(in);
         result = XPrsa(a, b, n);
         cout << "remainder: ";
         XPshowDecimal(result);
      }
      
   } catch (string msg) {
      cout << msg << endl;
   }
}