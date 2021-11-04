#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "jschnee.h"



char* strCondense(char *input, unsigned short inSz, unsigned short *outSz) {
    char *nStr = calloc(inSz, sizeof (char));
    char *token = strtok(input, DELIM);
    unsigned short count = 0;
    unsigned short innerCount = 0;
    while (token != NULL) {
        while (*(token + innerCount) != '\0') {
            if (innerCount == 0 && count != 0)
                nStr[count++] = ' ';
            nStr[count++] = *(token + innerCount++);
        }
        innerCount = 0;
        token = strtok(NULL, DELIM);
    }
    nStr[count] = '\0';
    if (nStr[count - 1] != '\n') count++;
    *outSz = count;
    return nStr;
}

unsigned short findFlag(char *input, unsigned size) {
    //A return value of 1 signals that the first non white space character is not a sufficient operator
    if ((*(input) != '+') && (*(input) != '-') && (*(input) != '*') && (*(input) != '/') && (*(input) != '^')) return 1;
    char op = *(input);
    char *token = strtok(input, DELIM2);
    //A return value of 8 signals that only a operator was input
    if (*(token +1) == '\0' || *(token + 2) == '\0') return 8;
    token = strtok(NULL, DELIM2);
    //A return value of 6 signals that there is no space between the number arguments and there is more than 2 digits
    if (token == NULL && size > 5) return 6;
    //A return value of 7 signals that there is no space between arguments but there is only 2 digits
    if (token == NULL && size == 4 && input[size - 1] == '\0') return 7;
    //A return value of 7 signals that there is no space between arguments but there is only 2 digits
    if (token == NULL && size == 5 && input[size - 1] == '\n') return 7;

    unsigned short tokenCount = 1;
    unsigned short count;

    for (unsigned short i = 0; token != NULL; i++) {
        //A return value of 5 signals that there was too many arguments that were provided
        if (i >= 2) return 5;
        count = 0;
        while (*(token + count) != '\0') {
            if ((i == 0) && (!(isdigit(*(token + count)))) && *(token) != '-') {
                //A return value of 2 signals that the argument for the first integer cannot be read as such
                return 2;
            }
            if (i == 1 && !(isdigit(*(token + count))) && *(token) != '-') {
                //A return value of 3 signals that the argument for the second integer cannot be read as such
                return 3;
            }
            if (i == 1 && op == '/' && *(token) == '0' && *(token + 1) == '\0') {
                //A return value of 9 signals that the argument for the second integer cannot be read as such
                return 9;
            }
            count++;
        }
        token = strtok(NULL, DELIM2);
        tokenCount++;
    }

    //A return value of 4 signals that there was only one integer argument
    if (tokenCount == 2) return 4;
    return 0;
}

void announceFlag(unsigned short flag, unsigned short lnNum, FILE *aHandler, char *newLn) {
    switch (flag) {
        case 0:
            handleExpression(newLn, aHandler);
            break;
        case 1:
            fprintf(aHandler, "You have input an invalid prefix operator on line %u:\n", lnNum);
            break;
        case 2:
            fprintf(aHandler, "You have input an invalid argument for the first integer on line %u:\n", lnNum);
            break;
        case 3:
            fprintf(aHandler, "You have input an invalid argument for the second integer on line %u:\n", lnNum);
            break;
        case 4:
            fprintf(aHandler, "You have input an invalid number of arguments. You need two integers instead of only one on line %u:\n", lnNum);
            break;
        case 5:
            fprintf(aHandler, "You have input an invalid number of arguments. You typed more than two integers on line %u:\n", lnNum);
            break;
        case 6:
            fprintf(aHandler, "You have no spaces in between your operator and two arguments on line %u:\n", lnNum);
            break;
        case 7:
            fprintf(aHandler, "You have no spaces in between your operator and two arguments on line %u:\n", lnNum);
            break;
        case 8:
            fprintf(aHandler, "You have no integers after your prefix operator. You need two integer arguments on line %u:\n", lnNum);
            break;
        case 9:
            fprintf(aHandler, "You cannot divide by zero. You need to change your second integer argument to a non-zero value on line %u:\n", lnNum);
            break;
    }
}

void handleExpression(char *newLn, FILE *aHandler) {
    switch (*(newLn)) {
        case '+':
            addHandler(newLn, aHandler);
            break;
        case '-':
            subHandler(newLn, aHandler);
            break;
        case '*':
            mulHandler(newLn, aHandler);
            break;
        case '/':
            divHandler(newLn, aHandler);
            break;
        case '^':
            expHandler(newLn, aHandler);
            break;
    }
}

void addHandler(char *newLn, FILE *aHandler) {
    char z;
    int x;
    int y;
    sscanf(newLn, "%c %d %d", &z, &x, &y);
    fprintf(aHandler, "%d = %d %c %d\n", (x + y), x, z, y);
}

void subHandler(char *newLn, FILE *aHandler) {
    char z;
    int x;
    int y;
    sscanf(newLn, "%c %d %d", &z, &x, &y);
    fprintf(aHandler, "%d = %d %c %d\n", (x - y), x, z, y);
}

void mulHandler(char *newLn, FILE *aHandler) {
    char z;
    int x;
    int y;
    sscanf(newLn, "%c %d %d", &z, &x, &y);
    fprintf(aHandler, "%d = %d %c %d\n", (x * y), x, z, y);
}

void divHandler(char *newLn, FILE *aHandler) {
    char z;
    int x;
    int y;
    sscanf(newLn, "%c %d %d", &z, &x, &y);
    fprintf(aHandler, "%d = %d %c %d\n", (x / y), x, z, y);
}

void expHandler(char *newLn, FILE *aHandler) {
    char z;
    int x;
    int y;
    sscanf(newLn, "%c %d %d", &z, &x, &y);
    fprintf(aHandler, "%d = %d %c %d\n", (int) pow(x, y), x, z, y);
}
