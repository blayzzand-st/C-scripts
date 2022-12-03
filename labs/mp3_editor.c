#include <stdio.h>

int main() {
    FILE *file = NULL;
    char testFile_name[] = "C:/Users/flame/CLionProjects/labs/test.txt";
    char file_name[] = "C:/Users/flame/CLionProjects/labs/Kansas_Karry_on.mp3";
    unsigned char symbol = 0;

    file = fopen(file_name, "r");
    for (int i = 0; i < 10; i++) {
        symbol = fgetc(file);
        printf("%x", symbol);
    }
//    while (symbol != EOF) {
//        for (int i = 0; i < 1; i++) {
//            symbol = fgetc(file);
//            printf("%c", symbol);
//        }
//    }
    fclose(file);

    return 0;
}