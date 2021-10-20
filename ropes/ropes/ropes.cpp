// ropes.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

vector<pair<int, int>> sortDecending(vector<pair<int, int>> list);
void printVectorPair(vector<pair<int, int>> list);
void LCS_LENGTH(vector<pair<int, int>> A, vector<pair<int, int>> B, vector<vector<string>>& direction, vector<vector<int>>& cost);
void GET_LCS(vector<vector<string>> direction, vector<pair<int, int>> A, vector<int>& answer, int x, int y);
void print2DArray(vector<vector<string>> array);
void print2DArray(vector<vector<int>> array);
int Remove_Duplicates(vector<int>& answerArray, vector<pair<int, int>> diameter, vector<pair<int, int>> strength);
int randNumber();

int main(int argc, char** argv)
{
    vector<pair<int, int>> Diameter; //Diameter Array
    vector<pair<int, int>> Strength; //Strength Array
    pair<vector<vector<int>>, vector<vector<string>>> Cost_Direction;
    vector<int> answer; //Answer Array
    answer.resize(Diameter.size());
    answer.resize(Diameter.size());
    
    //Fill vectors
    if (argc == 2)
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

    //Run Testing if test is written after file in cmd line
    if (argc == 3)
    {
        int numberOfTests = 100;
        ofstream file;
        file.open("sortTests.csv", std::ofstream::out | std::ofstream::trunc);
        file << "Time values are in nanoseconds\n";
        file << "Test Length, Time (ns), answer length\n";

        for (int i = 2; i < numberOfTests + 1; i++)
        {
            //Generate the vectors to sort
            vector<pair<int, int>> diameter(i);
            vector<pair<int, int>> strength(i);
            vector<int> answer; //Answer Array
            srand(time(NULL));
            
            for (int j = 0; j < i; j++)
            {
                diameter[j] = make_pair(randNumber(), j);
                strength[j] = make_pair(randNumber(), j);
            }
            vector<pair<int, int>> sortedDiameter = sortDecending(diameter);
            vector<pair<int, int>> sortedStrength = sortDecending(strength);

            int length = diameter.size();
            vector<vector<string>> direction(length + 1, vector<string>(length + 1));
            vector<vector<int>> cost(length + 1, vector<int>(length + 1));

            //Time Tests
            auto start = chrono::high_resolution_clock::now();
            LCS_LENGTH(sortedDiameter, sortedStrength, direction, cost);
            GET_LCS(direction, sortedDiameter, answer, sortedDiameter.size(), sortedDiameter.size());
            int duplicateCount = Remove_Duplicates(answer, diameter, strength);
            auto end = chrono::high_resolution_clock::now();
            auto elapsedTime = end - start;

            file << i << "," << elapsedTime.count() << "," << answer.size() - duplicateCount << "\n";
        }

        file.close();
        return 0;
    }

    //Sort each component decending
    vector<pair<int, int>> sortedDiameter = sortDecending(Diameter);
    vector<pair<int, int>> sortedStrength = sortDecending(Strength);


    //Set direction and cost 2d arrays
    int length = Diameter.size();
    vector<vector<string>> direction(length + 1, vector<string>(length + 1));
    vector<vector<int>> cost(length + 1, vector<int>(length + 1));

    //Run LCS
    LCS_LENGTH(sortedDiameter, sortedStrength, direction, cost);

    //Evaluate LCS Results
    GET_LCS(direction, sortedDiameter, answer, sortedDiameter.size(), sortedDiameter.size());
    
    //Print direction array for debugging
    //print2DArray(direction);
    //print2DArray(direction);

    int duplicateCount = Remove_Duplicates(answer, Diameter, Strength);

    
    //Print Answer
    cout << answer.size() - duplicateCount << endl;
    for (int i = 0; i < answer.size(); i++)
    {
        if(answer[i] != -1)
            cout << answer[i] << " -> " << Diameter[answer[i]].first << " : " << Strength[answer[i]].first << endl;
    }

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

void print2DArray(vector<vector<string>> array)
{
    for(int i = 0; i < array.size(); i++)
    {
        for(int j = 0; j < array.size(); j++)
        {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }
}

void print2DArray(vector<vector<int>> array)
{
    for(int i = 0; i < array.size(); i++)
    {
        for(int j = 0; j < array.size(); j++)
        {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }
}

void LCS_LENGTH(vector<pair<int, int>> A, vector<pair<int, int>> B, vector<vector<string>> &direction, vector<vector<int>> &cost)
{
    int length = A.size();

    for (int x = 0; x < length; x++)
        cost[x][0] = 0;
    
    for (int y = 0; y < length; y++)
        cost[0][y] = 0;

    for (int x = 1; x <= length; x++)
    {
        for (int y = 1; y <= length; y++)
        {
            if (A[x-1].second == B[y-1].second) //GRADING: REUSE
            {
                cost[x][y] = cost[x - 1][y - 1] + 1; //GRADING: UPDATE
                direction[x][y] = "UL";
            }
            else if (cost[x - 1][y] > cost[x][y - 1]) //GRADING: REUSE
            {
                cost[x][y] = cost[x - 1][y]; //GRADING: UPDATE
                direction[x][y] = "L";
            }
            else
            {
                cost[x][y] = cost[x][y - 1]; //GRADING: UPDATE
                direction[x][y] = "U";
            }
        }
    }
}

void GET_LCS(vector<vector<string>> direction, vector<pair<int, int>> A, vector<int> &answer, int x, int y)
{
    if (x == 0 or y == 0)
        return;
    if (direction[x][y] == "UL")
    {
        GET_LCS(direction, A, answer, x, y - 1);
        answer.push_back(A[x-1].second);
    }
    else if (direction[x][y] == "U")
        GET_LCS(direction, A, answer, x, y - 1);
    else
        GET_LCS(direction, A, answer, x - 1, y);
}

int Remove_Duplicates(vector<int>& answerArray, vector<pair<int, int>> diameter, vector<pair<int, int>> strength)
{
    int currentDiameter = diameter[0].first;
    int currentStrength = strength[0].first;
    int duplicateCount = 0;
    for (int i = 1; i < answerArray.size(); i++)
    {
        if (currentDiameter == diameter[i].first and currentStrength == strength[i].first)
        {
            answerArray[i] == -1;
            duplicateCount++;
        }
        else
        {
            currentDiameter = diameter[i].first;
            currentStrength = strength[i].first;
        }
    }

    return duplicateCount;
}

int randNumber()
{
    return rand() % 10000;
}