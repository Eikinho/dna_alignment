/*===========================================================
# Author:       Eiki Yamashiro
# Github:       github.com/Eikinho/smith_waterman
# FileName:     algoritmo_local.cpp
# Email:        eikisantos@outlook.com
# Version:      0.0.1
===========================================================*/

// INCLUDES
#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include<random>
#include<fstream>

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

int score(vector<char> sa, vector<char> sb)
{
    int result = 0;

    for (int i = 0; i < int(sa.size()); i++){
        if (sa[i] == sb[i]){
            result += 2;
        } else {
            result -= 1;
        }
    }

    return result;
}

int main()
{

    Cursor cursor = init();

    // A entrada two sempre é a maior
    int seed = 404;
    random_device device;
    default_random_engine generator(seed);
    uniform_int_distribution<int> distribution(1, cursor.two.size);

    // Gerar k, sabendo que k + j <= cursor.two.size
    int k = distribution(generator);

    // Gerar j
    uniform_int_distribution<int> j_distribution(0, cursor.two.size - k);
    int j = j_distribution(generator);
    
    // Gerar cursor.two.sequency[j: k+j]
    vector<char> sub_two;
    for (int l = j; l<= j+k; l++)
    {
        sub_two.push_back(cursor.two.sequency[l]);
    }

    // Gerar um p inteiro aleatorio
    int p = distribution(generator);
    vector<char> sub_one;
    int max = 0;

    for (int l = 0; l <= p; l++)
    {
        uniform_int_distribution<int> i_distribution(0, cursor.one.size - k);
        int i = i_distribution(generator);
        sub_one.clear();
        for (int o = i; o <= i+k; o++)
        {
            sub_one.push_back(cursor.one.sequency[o]);
        }

        int score_ = score(sub_one, sub_two);
        if (score_ > max)
        {
            max = score_;
        }

    }

    cout << max << endl;

    return 0;
}