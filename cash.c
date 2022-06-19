#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void) {
    int counter = 0;
    float change;

   do {
        change = get_float("Change owed: ");
   }
   while (change < 0);

   int newChange = round(change * 100);

   while (newChange > 0) {

       if (newChange >= 25) {

           newChange = newChange - 25;
           counter++;

       }

       else if (newChange >= 10) {

           newChange = newChange - 10;
           counter++;

       }

       else if (newChange >= 5) {

           newChange = newChange - 5;
           counter++;

       }

       else {

           newChange = newChange - 1;
           counter++;
       }

   }

   printf("%i\n", counter);

}