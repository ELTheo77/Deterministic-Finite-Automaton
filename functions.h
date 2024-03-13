#include <bits/stdc++.h>

using namespace std;

string line;
int stareCurenta;
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
}tranzitii[1000];

void prelucrareSigma(ifstream& fin)
{
    while(getline(fin, line))
    {
        if(line == "End") break;
        sigma.push_back(line);
    }
    //for(int i=0; i<sigma.size(); i++) fout << sigma[i] << "\n";
}

void prelucrareStates(ifstream& fin)
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
    //for(int i=0; i<states.size(); i++) fout << states[i] << "\n";
}

void prelucrareTransitions(ifstream& fin)
{
    int index = 0;
    while(getline(fin, line))
    {
        if(line == "End") break;
        string s1 = line.substr(0, line.find(','));
        string s2 = line.substr(line.find(',')+1, line.rfind(',')-line.find(',')-1);
        string s3 = line.substr(line.rfind(',')+1);
        tranzitii[index].state1 = stoi(s1);
        tranzitii[index].sigma = s2;
        tranzitii[index].state2 = stoi(s3);
        if(start[stoi(s1)] == 1) tranzitii[index].si = 1;
        if(final[stoi(s1)] == 1) tranzitii[index].sf1 = 1;
        if(final[stoi(s3)] == 1) tranzitii[index].sf2 = 1;
        //fout << tranzitii[index].state1 << " " << tranzitii[index].sigma << " " << tranzitii[index].state2 << " " << tranzitii[index].si << " " << tranzitii[index].sf1 << " " << tranzitii[index].sf2 << "\n";
        index++;
    }
}

bool fsaVerificare(ofstream& fout)
{
    for(int i=0; i<1000; i++)
    {
        if(tranzitii[i].state1 == 0) break;
        if(find(states.begin(), states.end(), tranzitii[i].state1) == states.end())
        {
            fout << "The state " << tranzitii[i].state1 << " is not present in the list of states\n";
            return 0;
        }
        if(find(states.begin(), states.end(), tranzitii[i].state2) == states.end())
        {
            fout << "The state " << tranzitii[i].state2 << " is not present in the list of states\n";
            return 0;
        }
        if(find(sigma.begin(), sigma.end(), tranzitii[i].sigma) == sigma.end())
        {
            fout << "The sigma " << tranzitii[i].sigma << " is not present in the alphabet\n";
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
        if(tranzitii[i].state1 == 0) break;
        for(int j=i+1; j<1000; j++)
        {
            if(tranzitii[j].state1 == 0) break;
            if(tranzitii[i].state1 == tranzitii[j].state1 && tranzitii[i].sigma == tranzitii[j].sigma)
            {
                fout << "There are two transitions with the same state1 and sigma\n";
                return 0;
            }
        }
    }
    fout << "FSA valid";
    return 1;
}

void fsaCitire(ifstream& fin)
{
    getline(fin, line);
    while(line[0] == '#') getline(fin, line);
    for(int i=0; i<3; i++)
    {
        while(line[0] == '#') getline(fin, line);
        if(line == "Sigma:") 
        {
            prelucrareSigma(fin);
            if(i != 2) getline(fin, line);
            while(line[0] == '#') getline(fin, line);
        }
        else if(line == "States:") 
        {
            prelucrareStates(fin);
            if(i != 2) getline(fin, line);
            while(line[0] == '#') getline(fin, line);
        }
        else if(line == "Transitions:") 
        {
            prelucrareTransitions(fin);
            if(i != 2) getline(fin, line);
            while(line[0] == '#') getline(fin, line);
        }
    }
}

void fsaStringCheck(string str)
{
    for(int i=0; i<1000; i++) if(start[i]) stareCurenta = i;
    for(int i=0; i<str.size(); i++)
    {
        for(int j=0; j<1000; j++)
        {
            if(tranzitii[j].state1 == stareCurenta && tranzitii[j].sigma == str.substr(i, 1))
            {
                stareCurenta = tranzitii[j].state2;
                break;
            }
        }
        if(i == str.size()-1)
        {
            if(final[stareCurenta]) cout << "accepted";
            else cout << "rejected";
        }
    }
}