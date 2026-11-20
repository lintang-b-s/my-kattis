#include <bits/stdc++.h>
using namespace std;

int main()
{

    int pattern = 1;
    int T, N;
    cin >> T;
    for (int c = 0; c < T; c++)
    {
        cin >> N;
        int matrix[N][N];
        for (int i = 0; i < N; i++)
        {
            string row;
            cin >> row;
            for (int j = 0; j < N; j++)
            {
                matrix[i][j] = row[j] - '0';
            }
        }

        int M;
        cin >> M;
        int transformed[N][N];
        for (int i = 0; i < N; i++)
        {

            for (int j = 0; j < N; j++)
            {
                transformed[i][j] = matrix[i][j];
            }
        }

        // O(M*N^2)
        for (int i = 0; i < M; i++)
        {
            string command;
            cin >> command;

            if (command == "transpose")
            {
                for (int i = 0; i < N; i++)
                {

                    for (int j = 0; j < N; j++)
                    {
                        matrix[i][j] = transformed[i][j];
                    }
                }

                for (int i = 0; i < N; i++)
                {

                    for (int j = 0; j < N; j++)
                    {
                        transformed[j][i] = matrix[i][j];
                    }
                }
            }
            else if (command == "inc")
            {
                for (int i = 0; i < N; i++)
                {

                    for (int j = 0; j < N; j++)
                    {
                        transformed[i][j] = (transformed[i][j] + 1) % 10;
                    }
                }
            }
            else if (command == "dec")
            {
                for (int i = 0; i < N; i++)
                {

                    for (int j = 0; j < N; j++)
                    {
                        transformed[i][j] = (transformed[i][j] - 1);
                        if (transformed[i][j] == -1)
                        {
                            transformed[i][j] = 9;
                        }
                    }
                }
            }
            else
            {
                int a, b;
                cin >> a >> b;
                a -= 1;
                b -= 1;
                if (command == "row")
                {
                    int temp[N];
                    for (int j = 0; j < N; j++)
                    {
                        temp[j] = transformed[a][j];
                    }

                    for (int j = 0; j < N; j++)
                    {
                        transformed[a][j] = transformed[b][j];
                    }

                    for (int j = 0; j < N; j++)
                    {
                        transformed[b][j] = temp[j];
                    }
                }
                else if (command == "col")
                {
                    int temp[N];
                    for (int i = 0; i < N; i++)
                    {
                        temp[i] = transformed[i][a];
                    }

                    for (int i = 0; i < N; i++)
                    {
                        transformed[i][a] = transformed[i][b];
                    }

                    for (int i = 0; i < N; i++)
                    {
                        transformed[i][b] = temp[i];
                    }
                }
            }
        }

        cout << "Case #" << c + 1 << endl;
        for (int i = 0; i < N; i++)
        {

            for (int j = 0; j < N; j++)
            {
                cout << transformed[i][j];
            }
            cout << endl;
        }
        cout << endl;
    }
}