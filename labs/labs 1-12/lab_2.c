#include <stdio.h>
#include <string.h>
#define MAX 100

void sumDigits(int n, int sum) {
    if (n / 10 > 0) {
        sum += n % 10;
        sumDigits(n / 10, sum);
    }
    else {
        sum += n % 10;
        printf("%i", sum);
        return;
    }
}

void deleteSpaces(char *str, int index, int counter) {
    if (index == MAX - 1) {
        printf("%s", str);
        return;
    }
    if (str[index] == '"') {
//        printf("%i \n", counter);
        if (counter == 0)
            counter = 1;
        else
            counter = 0;
    }
    if (((str[index] == ' ') & (str[index - 1] == ' ') & (str[index - 2] == ' ')) ||
        (str[index] == ' ' & (str[index - 1] == '(' || str[index - 1] == '[' || str[index - 1] == '{')) || (str[index] == ' ' & str[index - 1] == '"' & counter == 1)) {
        char leftStr[MAX];
        char rightStr[MAX];

        for (int i = 0; i < MAX; i++) {
            leftStr[i] = 0;
            rightStr[i] = 0;
        }

        for (int i = 0; i < index; i++) {
            leftStr[i] = str[i];
        }
        for (int i = index + 1; i < MAX; i++) {
            rightStr[i - index - 1] = str[i];
        }

        deleteSpaces(strcat(leftStr, rightStr), index, counter);
    }
    else {
        deleteSpaces(str, index += 1, counter);
    }
}

int main() {
////    Recursive sum of digits
//    int n;
//    int sum = 0;
//
//    scanf("%i", &0
//1
//2
//3n);
//    sumDigits(n, sum);

// Delete spaces
    char string[MAX];
    gets(string);

    deleteSpaces(string, 0, 0);

    int i = strlen(string);
    if (string[i - 2] == ' ')
        string[i - 2] = '\0';
    return 0;
}