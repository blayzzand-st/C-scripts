#include <stdio.h>
#include <string.h>
#define MAX 100

int main() {
    FILE *file;

    char Location[MAX] = "C:/Users/flame/CLionProjects/labs/";
    char expansion[10] = ".txt";
    char name[50];

    int number1;
    int number2;

    gets(name);
    scanf("%i", &number1);
    scanf("%i", &number2);

    strcat(Location, name);
    strcat(Location, expansion);
    printf("%s", Location);

    file = freopen(Location, "w + t", stdout);
    printf("%i", number1 + number2);
    return 0;
}