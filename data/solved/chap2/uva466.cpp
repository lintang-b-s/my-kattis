#include <bits/stdc++.h>
using namespace std;

bool preserve(const vector<vector<char>> &matrix,
              const vector<vector<char>> &transformedMatrix)
{
    int N = matrix.size();
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (transformedMatrix[i][j] != matrix[i][j])
            {
                return false;
            }
        }
    }

    return true;
}

// O(N^2)
bool rotateBang(int degree, const vector<vector<char>> &matrix,
                const vector<vector<char>> &transformedMatrix)
{
    int N = matrix.size();
    if (degree == 90)
    {

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (transformedMatrix[j][N - 1 - i] != matrix[i][j])
                {
                    return false;
                }
            }
        }
    }
    else if (degree == 180)
    {

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (transformedMatrix[N - 1 - i][N - 1 - j] != matrix[i][j])
                {
                    return false;
                }
            }
        }
    }
    else if (degree == 270)
    {

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (transformedMatrix[N - 1 - j][i] != matrix[i][j])
                {
                    return false;
                }
            }
        }
    }

    return true;
}

bool reflect(const vector<vector<char>> &matrix,
             const vector<vector<char>> &transformedMatrix)
{
    int N = matrix.size();

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (transformedMatrix[N - 1 - i][j] != matrix[i][j])
            {
                return false;
            }
        }
    }

    return true;
}

vector<vector<char>> melakukanReflect(const vector<vector<char>> &matrix)
{
    int N = matrix.size();
    vector<vector<char>> terreflect(N, vector<char>(N));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            terreflect[N - 1 - i][j] = matrix[i][j];
        }
    }

    return terreflect;
}

int main()
{

    int pattern = 1;
    int dim;
    while (cin >> dim)
    {
        vector<vector<char>> matrix(dim, vector<char>(dim)), transformedMatrix(dim, vector<char>(dim));

        for (int i = 0; i < dim; i++)
        {
            string original, transformed;
            cin >> original >> transformed;

            for (int j = 0; j < dim; j++)
            {
                matrix[i][j] = original[j];
                transformedMatrix[i][j] = transformed[j];
            }
        }

        if (preserve(matrix, transformedMatrix))
        {
            cout << "Pattern " << pattern << " was preserved." << endl;
        }
        else if (rotateBang(90, matrix, transformedMatrix))
        {
            cout << "Pattern " << pattern << " was rotated 90 degrees." << endl;
        }
        else if (rotateBang(180, matrix, transformedMatrix))
        {
            cout << "Pattern " << pattern << " was rotated 180 degrees." << endl;
        }
        else if (rotateBang(270, matrix, transformedMatrix))
        {
            cout << "Pattern " << pattern << " was rotated 270 degrees." << endl;
        }
        else if (reflect(matrix, transformedMatrix))
        {
            cout << "Pattern " << pattern << " was reflected vertically." << endl;
        }
        else
        {

            vector<vector<char>> terreflect = melakukanReflect(matrix);
            if (rotateBang(90, terreflect, transformedMatrix))
            {
                cout << "Pattern " << pattern << " was reflected vertically and rotated 90 degrees." << endl;
            }
            else if (rotateBang(180, terreflect, transformedMatrix))
            {
                cout << "Pattern " << pattern << " was reflected vertically and rotated 180 degrees." << endl;
            }
            else if (rotateBang(270, terreflect, transformedMatrix))
            {
                cout << "Pattern " << pattern << " was reflected vertically and rotated 270 degrees." << endl;
            }
            else
            {
                cout << "Pattern " << pattern << " was improperly transformed." << endl;
            }
        }

        pattern++;
    }

    return 0;
}