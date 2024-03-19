//The FSA inputs are defined as the greek letter sigma

#include <bits/stdc++.h>
#include "fsaEngine.h"
#include "input.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout << "Run with an existing input file or create one from scratch? (EXISTING/NEW): ";
    string input, output, answer;
    cin >> answer;
    if(answer == "NEW")
    {
        customInputFile();
        ifstream fin("newInput.txt");
        cout << "\nEnter output file: ";
        cin >> output;
        ofstream fout(output);

        fsaInput(fin, line);

        if(fsaValidation(fout, states, sigma, start, transitions))
        {
            try
            {
                string str = argv[1];
                fsaStringCheck(str, currentState, start, final, transitions);
            }
            catch(const exception& e)
            {
                cout << "No arguments given. Please run the program again with a string as an argument. Command prompt example: File Path\\fsa.exe input_string";
            }
        }
    }
    else
    {
        cout << "Enter input and output files: ";
        cin >> input >> output;
        ifstream fin(input);
        ofstream fout(output);

        fsaInput(fin, line);

        if(fsaValidation(fout, states, sigma, start, transitions))
        {
            try
            {
                string str = argv[1];
                fsaStringCheck(str, currentState, start, final, transitions);
            }
            catch(const exception& e)
            {
                cout << "No arguments given. Please run the program again with a string as an argument. Command prompt example: File Path\\fsa.exe input_string";
            }
        }
    }

    return 0;
}