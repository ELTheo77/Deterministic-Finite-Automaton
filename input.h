#include <bits/stdc++.h>

using namespace std;

void fsaInput(ifstream& fin, string line)
{
    getline(fin, line);
    while(line[0] == '#') getline(fin, line);
    for(int i=0; i<3; i++)
    {
        while(line[0] == '#') getline(fin, line);
        if(line == "Sigma:") 
        {
            addSigma(fin, line);
            if(i != 2) getline(fin, line);
            while(line[0] == '#') getline(fin, line);
        }
        else if(line == "States:") 
        {
            addStates(fin, line, states, start, final);
            if(i != 2) getline(fin, line);
            while(line[0] == '#') getline(fin, line);
        }
        else if(line == "Transitions:") 
        {
            addTransitions(fin, line, states, sigma, start, final, transitions);
            if(i != 2) getline(fin, line);
            while(line[0] == '#') getline(fin, line);
        }
    }
}

void customInputFile()
{
    ofstream fout("newInput.txt");
    fout << "#Alphabet\nSigma:\n";
    cout << "Enter the DFA alphabet (type 'End' when done): ";
    while(true)
    {
        string s;
        cin >> s;
        fout << s << "\n";
        if(s == "End") break;
    }
    fout << "#States\nStates:\n";
    cout << "Enter the DFA states. Starting/final states must be entered as \"State_Number,S\"/\"State_Number,F\" (type 'End' when done): ";
    while(true)
    {
        string s;
        cin >> s;
        fout << s << "\n";
        if(s == "End") break;
    }
    fout << "#Transitions\nTransitions:\n";
    cout << "Enter the DFA transitions using the following format: \"State_Number,Letter,State_Number\" (type 'End' when done): ";
    while(true)
    {
        string s;
        cin >> s;
        fout << s << "\n";
        if(s == "End") break;
    }
    fout.close();
}