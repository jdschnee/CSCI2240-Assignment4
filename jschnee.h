#ifndef JSCHNEE_H_INCLUDED
#define JSCHNEE_H_INCLUDED

#define BUFF_MAX 50
#define DELIM " "
#define DELIM2 " \n\r"

char* strCondense(char *input, unsigned short inSz, unsigned short *outSz);
unsigned short findFlag(char *input, unsigned size) ;
void announceFlag(unsigned short flag, unsigned short lnNum, FILE *aHandler, char *newLn);
void handleExpression(char *newLn, FILE *aHandler);
void addHandler(char *newLn, FILE *aHandler);
void subHandler(char *newLn, FILE *aHandler);
void mulHandler(char *newLn, FILE *aHandler);
void divHandler(char *newLn, FILE *aHandler);
void expHandler(char *newLn, FILE *aHandler);

#endif // JSCHNEE_H_INCLUDED
