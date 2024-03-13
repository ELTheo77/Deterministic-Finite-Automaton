#include <bits/stdc++.h>
#include "functions.h"

using namespace std;

int main(int argc, char *argv[])
{
    string input, output;
    cout << "Enter input and output files: ";
    cin >> input >> output;
    ifstream fin(input);
    ofstream fout(output);

    fsaCitire(fin);

    if(fsaVerificare(fout))
    {
        try
        {
            string str = argv[1];
            fsaStringCheck(str);
        }
        catch(const exception& e)
        {
            cout << "N-AI ARGUMENTE";
        }
    }

    return 0;
}