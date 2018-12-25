/** Alex Djordjevic Ceasar Cipher Encryption Program

    This program uses a modified version of the Ceaser Cipher to encrypt
    words and sentences. As a key, it uses the first line(should be a single word)
    from an input DAT file, and uses it to encrypt the second line in the file.

*/
///Headers & libraries
#include <iostream>
#include <fstream>
#include <apstring.h>
#include <apstring.cpp>

using namespace std;

int main(){

    ifstream fileOne("encode.dat");

    /**Declaration of variables*/

    int key[21] = {0};
    int counter = 0;
    int keylength = 0;
    apstring word = "";
    apstring message = "";

    ///Checks if the file was opened
    if(!fileOne){
        cout << "file not opened";
    }
    else{
        cout << "Welcome to The Enigmazor 3000." << endl << endl;
        getline(fileOne, message);  ///Reads in the key
        keylength = message.length(); /// Stores the length of the key
        cout << "The encoding key is: " << message << endl;
        for(int i = 0; i < keylength; i++){
            key[i] = (int)message[i] - 65; ///Converts the key into numbers and stores it in an int array
        }
        cout << endl << "The message you want to encode is: ";
        getline(fileOne, message); /// Reads in the message into the char array
        cout << message;
            for(int j = 0; j < message.length(); j++){
                if((int)message[j] > 64 && (int)message[j] < 91){
                    word += (int)message[j] - key[counter%keylength]; ///Encrypts the message using the proper shift from the key
                    counter ++; ///Counter keeps track of how many letters have been encrypted, so that later words are attached to the end
                }
                if((int)word[counter-1] > 90){
                    word[counter-1] -= 26;  ///Loops letter back if they go past Z(90)
                }
            }


        cout << endl << endl << "The encrypted message is:  " << word << endl; ///Displays the encrypted message

    }
    return 0;
}
