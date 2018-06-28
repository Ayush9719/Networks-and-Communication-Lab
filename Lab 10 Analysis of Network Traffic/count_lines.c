#include<stdio.h>
#include<stdlib.h>

int main() {
char str1[20];
printf("Enter file name to check number of line: ");
scanf("%s",str1);
    unsigned int number_of_lines = 0;
    FILE *infile = fopen(str1, "r");
    int ch;

    while (EOF != (ch=getc(infile)))
        if ('\n' == ch)
            ++number_of_lines;
    printf("%u\n", number_of_lines);
    return 0;
}
