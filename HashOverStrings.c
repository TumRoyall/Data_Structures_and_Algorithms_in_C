#include <stdio.h>
#include <string.h>

int n, m;

int hash(char *s)
{
    int sum = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        sum = (sum * 256 + s[i]) % m;
    }
    return sum ;
}

int main()
{
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
    {
        char s[300];
        scanf("%s", s);
        printf("%d \n", hash(s));
    }
    return 0;
}