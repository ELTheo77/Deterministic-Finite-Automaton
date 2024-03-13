#include <bits/stdc++.h>
#include "functions.h"

using namespace std;

int main(int argc, char *argv[])
{
    fsaCitire();

    if(fsaVerificare())
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