/*
 * File:   main.c
 * Author: Joshua Schnee
 *
 * Created on October 27, 2020, 11:55 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "jschnee.c"
#include "jschnee.h"




int main() {
    FILE *rHandler, *aHandler;
    char buffer[BUFF_MAX] = {0};
    char tempLine[BUFF_MAX] = {0};
    unsigned short lnLen;
    unsigned short condLnLen = 0;
    unsigned short flag;
    unsigned short lnNum = 1;
    char *newLn = NULL;

    if ((rHandler = fopen("input.txt", "r")) == NULL) {
        printf("Error in opening input.txt");
        return (EXIT_FAILURE);
    }

    if ((aHandler = fopen("output.txt", "a")) == NULL) {
        printf("Error in creating output.txt");
        return (EXIT_FAILURE);
    }

    while ((fgets(buffer, BUFF_MAX, rHandler)) != NULL) {
        lnLen = strlen(buffer);
        newLn = strCondense(buffer, lnLen, &condLnLen);
        strcpy(tempLine, newLn);
        flag = findFlag(tempLine, condLnLen);
        announceFlag(flag, lnNum, aHandler, newLn);
        for (int i = 0; i < BUFF_MAX; i++) {
            buffer[i] = '\0';
            tempLine[i] = '\0';
        }
        free(newLn);
        newLn = NULL;
        lnNum++;
    }
    return (EXIT_SUCCESS);
}
