#include <bits/stdc++.h>

using namespace std;

string line;
int currentState;
vector<string> sigma;
vector<int> states;
int start[1000];
int final[1000];

struct FSA_data
{
    int state1;
    string sigma;
    int state2;
    bool sf1;
    bool sf2;
    bool si;
}transitions[1000];