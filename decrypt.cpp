#include<iostream>
#include<cstring>
#include<string>
#include<math.h>
#include <fstream>
#define ARRAY_SIZE 10000
using namespace std;

double propability[26] = {0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015, 0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749, 0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758, 0.00978, 0.02360, 0.00150, 0.01974, 0.00074};

string decrypt_help(string input, int offset) {//decrypts text AFTER finding the offset
    if(offset==0) return input;
    else {
        for (long unsigned int i=0; i<input.length(); i++)  {
            char current=input[i];
            //if its not a letter
            if(current<'A' || current>'z' || (current>'Z' && current<'a')){
                input[i] = current;
                continue;
            }
            //if its small letter
            if (current<='z' && current>='a'){
                //check what letter is it in the order in the alphabet
                int num=current-'a';
                if((num-offset) < 0){// if it makes the alphabet loop
                    //the +26 loops the aplhabet in case num - offset is negative thus -> goes before the ascii character 'a'
                    input[i] = 'a' + num - offset + 26;
                    continue;
                }
                else if((num-offset)>=0){ // if it doesnt make the alphabet loop
                    input[i] = 'a' + num - offset;
                    continue;
                }
            }
            //if its capital letter
            if (current<='Z' && current>='A'){
                //check what letter is it in the order in the alphabet
                int num=current-'A';
                if((num-offset) < 0){// if it makes the alphabet loop
                    //the +26 loops the aplhabet in case num - offset is negative thus -> goes before the ascii character 'a'
                    input[i] = 'A' + num - offset + 26;
                    continue;
                }
                else if((num-offset)>=0){ // if it doesnt make the alphabet loop
                    input[i] = 'A' + num - offset;
                    continue;
                }
            }
        }
        return input;
    }
}

double entropy_help(string text){ //calculates the entropy for ONE given decrypted text at a time
    //for a given decrypted text find the entropy formula
    //calculate the letter counter matrix
    int letter_counter[26] = {0};
    for (long unsigned int i=0; i<text.length(); i++){
        for (int j=0; j<26; j++){
            if(text[i]=='a'+j || text[i]=='A'+j) {
                ++letter_counter[j];
                continue;
            }
        }
    }
    //calculate the big sum in the entropy formula
    double sum=0;
    for (int i=0; i<26; i++){
        sum += letter_counter[i]*(log(propability[i]));
    }
    //calculate the entropy and return it
    return (-1.0)*(sum);
}

int main(int argc, char *argv[]){
    if (argc!=2) { // Input management
        cout << "Incorrect Input" << endl;
        return -1;
    }

    //open the file
    ifstream encrypted_file;
    encrypted_file.open(argv[1]);
    //encrypted_file.open(argv[1]);
    string to_decrypt = "";
    char c;
    while(encrypted_file>>noskipws>>c){
        to_decrypt += c;
    }
    encrypted_file.close();

    //make all the possible decryptions
    double entropy[26];
    for (int i=1; i<26; i++) {
        entropy[i] = entropy_help(decrypt_help(to_decrypt,i));
        //cout<<i<<" : "<<entropy[i]<<endl;
    }
    //check what is the offset
    int offset = 1;
    for (int i=1; i<26; i++){
        if (entropy[i]<entropy[offset]) {offset = i;}
    }

    //cout<<offset;
    //print the decrypted decrypted text
    cout<<decrypt_help(to_decrypt, offset);
    return 0;

}
