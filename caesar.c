#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//list of prototypes
bool keyChecker(string secondString);
string plainChecker(string s, int key);

int main(int argc, string argv[]) {


    //check if command line exactly two command line arguments, and if 2nd string is a number
    if  (argc != 2 || keyChecker(argv[1]) == false) {

        printf("Usage: ./caesar key\n");
        return 1;

    }


    //convert 2nd command line argument to an integer
    int stringtoKey = atoi(argv[1]);


    string plainText = get_string("plaintext: ");

    //check if alphabetical, then cipher plaintext
    string cipherText = plainChecker(plainText, stringtoKey);

    printf("ciphertext: %s\n", cipherText);




}

 //iterate through 2nd command line argument to make sure its just a string of numbers
bool keyChecker(string secondString) {

    for (int x = 0; x < strlen(secondString); x++) {

        if (isdigit(secondString[x]) == false) {

            return false;


         }


    }

    return true;

}


// copy parameter into sCopy, get int down to alphabetical index
// then use modulo formula to wrap around if needed
// get that value and add to 65 or 97 ascii to get corresponding ciphertext
string plainChecker(string s, int key) {

    string sCopy = s;

    for (int x = 0; x < strlen(s); x++) {

        if (isalpha(s[x])) {

            if (isupper(s[x])) {

                int y = s[x] - 65;

                int z = (y + key) % 26;

                sCopy[x] = z + 65;

            }

            else {

                 int y  = s[x] - 97;

                int z = (y + key) % 26;

                sCopy[x] = z + 97;



            }


        }

    }

    return sCopy;


}