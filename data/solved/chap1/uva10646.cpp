#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[])
{
  int pos, digits, alphas, vowels, consonants;
  char str[10010], *p;

  freopen("basic_string_in.txt", "r", stdin);

  strcpy(str, "");
  char line[110];
  fgets(line, 100, stdin);
  int num = stoi(line);

  char output[num][10];

  for (int i = 0; i < num; i++)
  {
    int y;
    char line[156];
    fgets(line, 156, stdin);
    int start = 156;

    for (int j = 0; j < 3; j++)
    {
      bool isDigit = isdigit(line[start]);
      bool isAlpha = isalpha(line[start]);
      int x;
      if (isDigit)
      {
        x = line[i] - '0';
      }
      else if (isAlpha)
      {
        x = 10;
      }
      int putAwayTop10Cards = 10 - x;
      y += x;
      if (putAwayTop10Cards > 0)
      {
        start = start - 3 * putAwayTop10Cards;
      }
    }

    output[i][0] = line[y];

    cout << "Case " << i + 1 << ": " << output[i][0] << endl;
  }
}
