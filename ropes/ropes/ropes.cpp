// ropes.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<int, int>> sortDecending(vector<pair<int, int>> list);
void printVectorPair(vector<pair<int, int>> list);
pair<vector<vector<int>>, vector<vector<string>>> LCS_LENGTH(vector<pair<int, int>> A, vector<pair<int, int>> B, vector<vector<string>>& direction, vector<vector<int>>& cost);
void GET_LCS(vector<vector<string>> direction, vector<pair<int, int>> A, vector<int>& answer, int x, int y);

int main(int argc, char** argv)
{
    vector<pair<int, int>> Diameter; //Diameter Array
    vector<pair<int, int>> Strength; //Strength Array
    pair<vector<vector<int>>, vector<vector<string>>> Cost_Direction;
    vector<int> answer; //Answer Array
    answer.resize(Diameter.size());
    answer.resize(Diameter.size());
    
    if (argc > 1)
    {
        ifstream inFile;
        int diameter = 0;
        int strength = 0;
        int index = 0;
        inFile.open(argv[1]);

        if (!inFile.is_open())
        {
            cout << "Failed to open file!" << endl;
            return -1;
        }

        while (inFile >> diameter)
        {
            inFile >> strength;
            Diameter.push_back(make_pair(diameter, index));
            Strength.push_back(make_pair(strength, index));
            index++;
        }

        inFile.close();
    }

    vector<pair<int, int>> sortedDiameter = sortDecending(Diameter);
    vector<pair<int, int>> sortedStrength = sortDecending(Strength);

    //printVectorPair(Diameter);
    //printVectorPair(sortedDiameter);
    int length = Diameter.size();
    vector<vector<string>> direction(length, vector<string>(length));
    vector<vector<int>> cost(length, vector<int>(length));

    Cost_Direction = LCS_LENGTH(sortedDiameter, sortedStrength, direction, cost);
    GET_LCS(direction, sortedDiameter, answer, sortedDiameter.size() - 1, sortedDiameter.size() - 1);
    
    for (int i = 0; i < answer.size(); i++)
        cout << answer[i] << endl;

    return 0;
}


vector<pair<int, int>> sortDecending(vector<pair<int, int>> list)
{
    sort(list.begin(), list.end());
    return list;
}

void printVectorPair(vector<pair<int, int>> list)
{
    cout << "Element\t"
        << "index" << endl;
    for (int i = 0; i < list.size(); i++) {
        cout << list[i].first << "\t"
            << list[i].second << endl;
    }
}

pair<vector<vector<int>>, vector<vector<string>>> LCS_LENGTH(vector<pair<int, int>> A, vector<pair<int, int>> B, vector<vector<string>> &direction, vector<vector<int>> &cost)
{
    int length = A.size();

    for (int x = 1; x < length; x++)
        cost[x][0] = 0;
    
    for (int y = 0; y < length; y++)
        cost[0][y] = 0;

    for (int x = 1; x < length; x++)
    {
        for (int y = 1; y < length; y++)
        {
            if (A[x] == B[y])
            {
                cost[x][y] = cost[x - 1][y - 1] + 1;
                direction[x][y] = "UL";
            }
            else if (cost[x - 1][y] > cost[x][y - 1])
            {
                cost[x][y] = cost[x - 1][y];
                direction[x][y] = "L";
            }
            else
            {
                cost[x][y] = cost[x][y - 1];
                direction[x][y] = "U";
            }
        }
    }
    return make_pair(cost, direction);
}

void GET_LCS(vector<vector<string>> direction, vector<pair<int, int>> A, vector<int> &answer, int x, int y)
{
    if (x == 0 or y == 0)
        return;
    if (direction[x][y] == "UL")
    {
        GET_LCS(direction, A, answer, x, y - 1);
        answer.push_back(A[x].second);
    }
    else if (direction[x][y] == "U")
        GET_LCS(direction, A, answer, x, y - 1);
    else
        GET_LCS(direction, A, answer, x - 1, y);
}
