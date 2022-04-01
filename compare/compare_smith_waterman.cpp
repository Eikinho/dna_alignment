/*===========================================================
# Author:       Eiki Yamashiro
# Github:       github.com/Eikinho/smith_waterman
# FileName:     smith_waterman.cpp
# Email:        eikisantos@outlook.com
# Version:      0.1.1
===========================================================*/

// INCLUDES
#include <iostream>
#include <bits/stdc++.h>
#include <vector>

// DEFINES
#define MATCH 2
#define MISMATCH -1
#define GAP -1
#define NONE_ORIGIN -1

#define ID_DIAGONAL 100
#define ID_DELETION 101
#define ID_INSERTION 102
#define ID_MATCH 103
#define ID_MISMATCH 104

using namespace std;

// STRUCTS
struct Sequency
{
    int id;
    int size;
    vector<char> sequency;
};

struct Point
{
    int i;
    int j;
    int value;
    int origin;
};

struct SmithWaterman
{
    int score;
    vector<vector<Point>> matrix;
};

struct Cursor
{
    Sequency one;
    Sequency two;
    SmithWaterman smith_waterman;
    vector<char> output;
};

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
    _one.id = 1;
    _one.size = n;
    _one.sequency = seqOne;
    _two.id = 2;
    _two.size = m;
    _two.sequency = seqTwo;
    return_cursor.one = _one;
    return_cursor.two = _two;

    return return_cursor;
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

void cout_sequency(Sequency sequency)
{

    for (int i = 0; i <= sequency.size; i++)
    {
        cout << sequency.sequency[i] << " ";
    }

    cout << '\n';
}

void cout_matrix(Cursor cursor)
{
    cout << "S ";
    cout_sequency(cursor.two);

    for (int i = 0; i <= cursor.one.size; i++)
    {
        cout << cursor.one.sequency[i] << " ";
        for (int j = 0; j <= cursor.two.size; j++)
        {
            cout << cursor.smith_waterman.matrix[i][j].value << " ";
        }

        cout << '\n';
    }
}

vector<vector<Point>> create_matrix(Sequency seqOne, Sequency seqTwo)
{
    vector<vector<Point>> matrix;

    matrix.resize(seqOne.size + 1);

    for (int i = 0; i <= seqOne.size; i++)
    {
        matrix[i].resize(seqTwo.size + 1);
    }

    for (int i = 0; i <= seqOne.size; i++)
    {
        for (int j = 0; j < seqTwo.size; j++)
        {
            Point point;
            point.i = i;
            point.j = j;
            point.value = 0;
            point.origin = 0;
            matrix[i][j] = point;
        }
    }

    return matrix;
}

int mini_score(Cursor cursor, int i, int j)
{

    if (cursor.one.sequency[i] == cursor.two.sequency[j])
    {
        return MATCH;
    }

    else if (cursor.one.sequency[i] != cursor.two.sequency[j])
    {
        return MISMATCH;
    }
    else if (cursor.one.sequency[i] == '-')
    {
        return GAP;
    }
    else if (cursor.two.sequency[j] == '-')
    {
        return GAP;
    }

    return 0;
}

vector<vector<Point>> smith_waterman(Cursor cursor)
{
    int diagonal = 0;
    int deletion = 0;
    int insertion = 0;
    int temp_max = 0;

    for (int i = 1; i <= cursor.one.size; i++)
    {
        for (int j = 1; j <= cursor.two.size; j++)
        {
            diagonal = cursor.smith_waterman.matrix[i - 1][j - 1].value + mini_score(cursor, i, j);
            deletion = cursor.smith_waterman.matrix[i - 1][j].value - 1;
            insertion = cursor.smith_waterman.matrix[i][j - 1].value - 1;
            temp_max = max(deletion, max(diagonal, insertion));
            if (diagonal == temp_max){
                if (mini_score(cursor, i, j) == MATCH)
                {
                    cursor.smith_waterman.matrix[i][j].origin = ID_MATCH;
                }
                else if (mini_score(cursor, i, j) == MISMATCH)
                {
                    cursor.smith_waterman.matrix[i][j].origin = ID_MISMATCH;
                }
            }
            else if (deletion == temp_max)
            {
                cursor.smith_waterman.matrix[i][j].origin = ID_DELETION;
            }
            else
            {
                cursor.smith_waterman.matrix[i][j].origin = ID_INSERTION;
            }
            if (temp_max < 0)
            {
                temp_max = 0;
            }
            cursor.smith_waterman.matrix[i][j].value = temp_max;
        }
    }

    return cursor.smith_waterman.matrix;
}

int score(Cursor cursor)
{
    int max = 0;
    for (int i = 0; i <= cursor.one.size; i++)
    {
        for (int j = 0; j <= cursor.two.size; j++)
        {
            if (cursor.smith_waterman.matrix[i][j].value > max)
            {
                max = cursor.smith_waterman.matrix[i][j].value;
            }
        }
    }
    return max;
}

string result(Cursor cursor)
{
    int score_ = score(cursor);
    string return_ = "";
    int last_i = 0;
    int last_j = 0;

    for (int i = 0; i <= cursor.one.size; i++)
    {
        for (int j = 0; j <= cursor.two.size; j++)
        {
            if (cursor.smith_waterman.matrix[i][j].value == score_)
            {
                last_i = i;
                last_j = j;
            }
        }
    }
    cout << "max i: " << last_i << cursor.one.sequency[last_i] << endl;
    cout << "max j: " << last_j << cursor.two.sequency[last_j] << endl;
    cout << cursor.smith_waterman.matrix[last_i][last_j].value << endl; 
    
    bool flag = true;
    while (flag)
    {
        if (cursor.smith_waterman.matrix[last_i][last_j].value == 2)
        {
            flag = false;
        }
        if (cursor.smith_waterman.matrix[last_i][last_j].origin == ID_MATCH)
        {
            return_ += '*';
            last_i -= 1;
            last_j -= 1;
        }
        else if (cursor.smith_waterman.matrix[last_i][last_j].origin == ID_MISMATCH)
        {
            return_ += '|';
            last_i -= 1;
            last_j -= 1;
        }
        else {
            return_ += ' ';
            // Deletion é para cima
            if (cursor.smith_waterman.matrix[last_i][last_j].origin == ID_DELETION)
            {
                last_i -= 1;
            }
            else
            {
                last_j -= 1;
            } 
        }
    }
    
    string tmp = "";
    for (int i = return_.length(); i >= 0; i--)
    {
        tmp += return_[i];
    }

    return tmp;
}

int main()
{
    // reading .txt file that contains the both sequencies. Create the cursor. 
    Cursor cursor = init();
    
    cursor.smith_waterman.matrix = create_matrix(cursor.one, cursor.two);

    cursor.smith_waterman.matrix = smith_waterman(cursor);

    cursor.smith_waterman.score = score(cursor);

    cout << "Score: " << cursor.smith_waterman.score << '\n';
    
    return 0;
} 