// ropes.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char** argv)
{
    vector<int> D; //Diameter Array
    vector<int> S; //Strength Array
    vector<int> a; //Answer Array
    
    if (argc > 1)
    {
        ifstream inFile;
        int diameter = 0;
        int strength = 0;
        inFile.open(argv[1]);

        if (!inFile.is_open())
        {
            cout << "Failed to open file!" << endl;
            return -1;
        }

        while (inFile >> diameter)
        {
            inFile >> strength;
            D.push_back(diameter);
            S.push_back(strength);
        }

        inFile.close();
    }

    return 0;
}


int T(int index, int pa, vector<int> D, vector<int> S)
{
    if (index == 0 or pa == 0)
        return 0;

    if (index == 1 and S[1] > pa)
        return 1;

    if (index > 0 and
        pa > 0 and
        S[index] <= pa and
        S[index - 1] < S[index])
        return T(index - 1, pa - 1, D, S) + 1;

    if (index > 0 and pa > 0)
        return max(T(index - 1, pa, D, S), T(index, pa - 1, D, S));
}

