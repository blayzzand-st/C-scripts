#include <stdio.h>
#include <math.h>
#include <string.h>

int prime(int n) {
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

int main() {
    char command[100];

    printf("Please enter the command: \n");
    gets(command);

    if (strcmp(command, "prime numbers") == 0) {
        // Prime numbers
        int n;
        scanf("%i", &n);
        for (int i = 2; i <= n; i++) {
            if (prime(i) == 1)
                printf("%i \n", i);
        }

        gets(command);
        if (strcmp(command, "exit") == 0)
            return 0;
    }
    else if (strcmp(command, "bank account") == 0) {
        // Bank account
        double startSum;
        double rate;
        int months;

        scanf("%lf", &startSum);
        scanf("%lf", &rate);
        scanf("%i", &months);

        double bankStatus = startSum;

        for (int i = 1; i <= months; i++) {
            bankStatus += (0.01 * (rate / 12)) * bankStatus;
            printf("%lf \n", bankStatus);
        }

        gets(command);
        if (strcmp(command, "exit") == 0)
            return 0;
    }
    else
        return 0;
    return 0;
}