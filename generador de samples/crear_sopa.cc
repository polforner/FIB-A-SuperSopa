#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

typedef vector<vector<char>> Matrix;

void llenar_tablero_rand(Matrix &m)
{

    for (auto &v : m)
    {

        for (char &c : v)
            if (c == '.')
                c = 'a' + (rand() % ('z' - 'a' + 1));
    }
}

void print(Matrix &m)
{

    for (auto &v : m)
    {

        for (char c : v)
            cout << c << ' ';

        cout << endl;
    }
}

inline bool valid(Matrix &m, int i, int j)
{

    return i >= 0 and i < m.size() and j >= 0 and j < m[0].size();
}

pair<int, int> pos(int i, int j, int k)
{

    pair<int, int> p;

    switch (k)
    {

    case 0:
        p.first = i;
        p.second = j + 1;
        break;

    case 1:
        p.first = i;
        p.second = j - 1;
        break;

    case 2:
        p.first = i + 1;
        p.second = j;
        break;

    case 3:
        p.first = i - 1;
        p.second = j;
        break;

    case 4:
        p.first = i + 1;
        p.second = j + 1;
        break;

    case 5:
        p.first = i + 1;
        p.second = j - 1;
        break;

    case 6:
        p.first = i - 1;
        p.second = j - 1;
        break;

    case 7:
        p.first = i - 1;
        p.second = j + 1;
        break;
    }

    return p;
}

bool dfs(const string &s, int i, int j, Matrix &m, int k, vector<vector<bool>> &mb)
{

    if (k == s.length())
        return true;

    if (not valid(m, i, j) or mb[i][j] or (m[i][j] != s[k] and m[i][j] != '.'))
        return false;

    else
    {

        vector<bool> vb(8, false);

        bool b = m[i][j] == '.';

        if (b)
            m[i][j] = s[k];

        int cuenta = 0;

        int rd = rand() % 8;

        while (cuenta < 8)
        {

            if (not vb[rd])
            {

                vb[rd] = true;
                ++cuenta;
                pair<int, int> p = pos(i, j, rd);
                mb[i][j] = true;

                if (dfs(s, p.first, p.second, m, k + 1, mb))
                    return true;
            }

            rd = rand() % 8;
        }

        if (b)
        {
            m[i][j] = '.';
            mb[i][j] = false;
        }

        return false;
    }
}

Matrix crear_sopa(vector<string> &dic, int n)
{

    srand(time(NULL));
    vector<vector<bool>> mb(n, vector<bool>(n, false));
    Matrix m(n, vector<char>(n, '.'));

    for (string &s : dic)
    {

        int i = rand() % m.size();
        int j = rand() % m[0].size();

        while (not dfs(s, i, j, m, 0, mb))
        {
            i = rand() % m.size();
            j = rand() % m[0].size();
        }
    }

    llenar_tablero_rand(m);

    return m;
}
