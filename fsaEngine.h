#include <bits/stdc++.h>
#include "data.h"

using namespace std;

void addSigma(ifstream& fin, string line)
{
    while(getline(fin, line))
    {
        if(line == "End") break;
        sigma.push_back(line);
    }
}

void addStates(ifstream& fin, string line, vector<int> states, int start[], int final[])
{
    while(getline(fin, line))
    {
        if(line == "End") break;
        if(line.find(',') == string::npos)
            states.push_back(stoi(line));
        else
        {
            string s = line.substr(0, line.find(','));
            states.push_back(stoi(s));
            if(line.find('S') != string::npos) start[stoi(s)] = 1;
            if(line.find('F') != string::npos) final[stoi(s)] = 1;
        }
    }
}

void addTransitions(ifstream& fin, string line, vector<int> states, vector<string> sigma, int start[], int final[], FSA_data transitions[])
{
    int index = 0;
    while(getline(fin, line))
    {
        if(line == "End") break;
        string s1 = line.substr(0, line.find(','));
        string s2 = line.substr(line.find(',')+1, line.rfind(',')-line.find(',')-1);
        string s3 = line.substr(line.rfind(',')+1);
        transitions[index].state1 = stoi(s1);
        transitions[index].sigma = s2;
        transitions[index].state2 = stoi(s3);
        if(start[stoi(s1)] == 1) transitions[index].si = 1;
        if(final[stoi(s1)] == 1) transitions[index].sf1 = 1;
        if(final[stoi(s3)] == 1) transitions[index].sf2 = 1;
        index++;
    }
}

bool fsaValidation(ofstream& fout, vector<int>& states, vector<string> sigma, int start[], FSA_data transitions[])
{
    for(int i=0; i<1000; i++)
    {
        if(transitions[i].state1 == 0) break;
        if(find(states.begin(), states.end(), transitions[i].state1) == states.end())
        {
            fout << "The state " << transitions[i].state1 << " is not present in the list of states\n";
            return 0;
        }
        if(find(states.begin(), states.end(), transitions[i].state2) == states.end())
        {
            fout << "The state " << transitions[i].state2 << " is not present in the list of states\n";
            return 0;
        }
        if(find(sigma.begin(), sigma.end(), transitions[i].sigma) == sigma.end())
        {
            fout << "The sigma " << transitions[i].sigma << " is not present in the alphabet\n";
            return 0;
        }
    }
    int startCount = 0;
    for(int i=0; i<1000; i++)
    {
        if(start[i] == 1) startCount++;
    }
    if(startCount != 1)
    {
        fout << "There is not exactly one start state\n";
        return 0;
    }
    for(int i=0; i<1000; i++)
    {
        if(transitions[i].state1 == 0) break;
        for(int j=i+1; j<1000; j++)
        {
            if(transitions[j].state1 == 0) break;
            if(transitions[i].state1 == transitions[j].state1 && transitions[i].sigma == transitions[j].sigma)
            {
                fout << "There are two transitions with the same state1 and sigma\n";
                return 0;
            }
        }
    }
    fout << "FSA valid";
    return 1;
}

void fsaStringCheck(string str, int currentState, int start[], int final[], FSA_data transitions[])
{
    for(int i=0; i<1000; i++) if(start[i]) currentState = i;
    for(int i=0; i<str.size(); i++)
    {
        for(int j=0; j<1000; j++)
        {
            if(transitions[j].state1 == currentState && transitions[j].sigma == str.substr(i, 1))
            {
                currentState = transitions[j].state2;
                break;
            }
        }
        if(i == str.size()-1)
        {
            if(final[currentState]) cout << "accepted";
            else cout << "rejected";
        }
    }
}