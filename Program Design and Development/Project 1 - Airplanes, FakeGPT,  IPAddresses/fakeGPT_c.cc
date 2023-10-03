#include <string>
#include <iostream>
#include <vector>
using namespace std;

void politeQuestions() {
    string LofV;
    cout << "Give me a sentence:" << endl;
    getline(cin, LofV);
    vector<string> vec;
    int num = 0;
    string temp = "";
    for (int i = 0; i < LofV.length(); i++) {               // Looping through LofV character length
        if (LofV.at(i) == ' ' || i == LofV.length()-1) {    // Checking for ' ' delimiter or end of string
            if (i == LofV.length()-1) {                     // if it's the end of the string, add the last char
                temp = temp + LofV.at(i);
            }
            vec.push_back(temp);                            // push the temp(temporary string) onto the vector
            temp = "";
            num++;
        } else if (LofV.at(i) == ',') {
            continue;
        } else {                                            // else push the char onto the temp string being built
            if (isalpha(LofV.at(i))) {                      // if its a letter, convert it to the lower case version
                temp = temp + char(tolower(LofV.at(i)));
            } else {
                temp = temp + LofV.at(i);
            }
        }
    }

    int decider = 0;                                  // one int to determine the output at the end
     for (int i = 0; i < vec.size(); i++) {
        string temp = vec.at(i);
        if (temp == "who" || temp == "what" || temp == "when" || temp == "where" || temp == "why" || temp == "how") {
            decider = decider + 1;
        }
         if (temp == "please" || temp == "may") {
            decider = decider + 2;
        }
     }

     switch (decider) {                                // switching between outputs based off of total
        case 0:
            cout << "That is not a question! And you should be more polite." << endl;
            break;
        case 1:
            cout << "I’m not sure, you should google that! Your questions should also be more polite." << endl;
            break;
        case 2:
            cout << "That is not a question! But you said it so nicely." << endl;
            break;
        case 3: 
            cout << "I’m not sure, you should google that! Thanks for asking so politely." << endl;   
            break; 
     }
}

int main() {
    politeQuestions();

    return 0;
}