/*===========================================================
# Author:       Eiki Yamashiro
# Github:       github.com/Eikinho/smith_waterman
# FileName:     busca_exaustiva.cpp
# Email:        eikisantos@outlook.com
# Version:      0.0.1
===========================================================*/

// INCLUDES
#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <string>

// DEFINES
#define MATCH 2
#define MISMATCH -1
#define GAP -1

using namespace std;

struct Sequency
{
    int id;
    int size;
    vector<char> sequency;
};

struct Cursor
{
    Sequency one;
    Sequency two;
    vector<char> output;
};

int is_match(char a, char b)
{
    if (a == b)
    {
        return 2;
    }
    return -1;
}

void cout_sequency_init(Sequency sequency)
{
    cout << "Sequency " << sequency.id << ": ";

    for (int i = 0; i <= sequency.size; i++)
    {
        cout << sequency.sequency[i];
    }

    cout << '\n';
}

Cursor init()
{
    int m, n;
    cin >> n >> m;

    vector<char> seqOne;
    vector<char> seqTwo;
    seqOne.push_back(' ');
    seqTwo.push_back(' ');

    for (int i = 0; i < n; i++)
    {
        char base;
        cin >> base;
        seqOne.push_back(base);
    }
    for (int i = 0; i < m; i++)
    {
        char base;
        cin >> base;
        seqTwo.push_back(base);
    }

    Cursor return_cursor;
    Sequency _one;
    Sequency _two;
    _one.size = n;
    _one.sequency = seqOne;
    _two.size = m;
    _two.sequency = seqTwo;

    if (_two.size >= _one.size)
    {
        return_cursor.one = _one;
        return_cursor.two = _two;
    }
    else 
    {
        return_cursor.one = _two;
        return_cursor.two = _one;
    }   

    return_cursor.one.id = 1;
    return_cursor.two.id = 2;

    return return_cursor;
}

// https://www.geeksforgeeks.org/convert-character-array-to-string-in-c/
string convertToString(Sequency sequency)
{
    vector<char> a = sequency.sequency;
    int size = sequency.size;
    int i;
    string s = "";
    for (i = 1; i < size+1; i++) {
        s = s + a[i];
    }
    return s;
}

int main()
{
    // reading .txt file that contains both sequencies. Create the cursor. 
    Cursor cursor = init();
    string s1 = convertToString(cursor.one);
    string s2 = convertToString(cursor.two);

    vector<string> subsequencies_one;
    vector<string> subsequencies_two;

    string choosed_one;
    string choosed_two;

    int score = 0;
    int max_score = 0;

    for (unsigned int i = 0; i < s1.size(); i++)
    {
        for (unsigned int j = 0; j < s1.size(); j++)
        {
            subsequencies_one.push_back(s1.substr(i,j));
        }
    }

    for (unsigned int i = 0; i < s2.size(); i++)
    {
        for (unsigned int j = 0; j < s2.size(); j++)
        {
            subsequencies_two.push_back(s2.substr(i,j));
        }
    }

    for (unsigned int i = 0; i < subsequencies_one.size(); i++)
    {
        for (unsigned int j = 0; j < subsequencies_two.size(); j++)
        {
            if(int(subsequencies_one[i].size()) == int(subsequencies_two[j].size()))
            {
                score = 0;
                for (unsigned int k = 0; subsequencies_one[i].size(); i++)
                {
                    score += is_match(subsequencies_one[i][k], subsequencies_two[j][k]);
                }
                if (score > max_score)
                {
                    choosed_one = subsequencies_one[i];
                    choosed_two = subsequencies_two[j];
                    max_score = score;
                }
            }             
        }
    }

    cout << max_score << endl;

    return 0;
} 