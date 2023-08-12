#include "Headers/header.h"
/**
 * The util file contains helper methods for other files in the project
 * The file improve code organization efficiency
 */

/**
 * The method check if a multiple void* allocated successfully
 * @param length
 * @param ... all void* to test if thier allocation succeed
 */
void isAllocationSuccessful(int length , ...){
    va_list list;
    int i;
    va_start(list, length);
    for(i=0; i < length; i++){
        if (va_arg(list, void*) == NULL){
            printAllocationFailure();
        }
    }
    va_end(list);
}

/**
 * The method checks if a text given contains a comma
 * @param text the text input
 * @return TRUE(1) if the the text contain comma otherwise FALSE(0)
 */
int isContainComma(char *text) {
    if(strstr(text, ",")){
        return TRUE;
    }
    return FALSE;
}

/**
 * The method checks if a text given contains a space
 * @param text the text input
 * @return TRUE(1) if the the text contain space otherwise FALSE(0)
 */
int isContainSpace(char *text) {
    if(strstr(text, " ")){
        return TRUE;
    }
    return FALSE;
}

/**
 * The method checks if a text given is empty being empty is either being null or only spaces
 * @param text the text input
 * @return TRUE(1) if the the text is empty otherwise FALSE(0)
 */
int isEmpty(char* text){
    int i;
    if(text == NULL){
        return TRUE;
    }
    if(strlen(text) == 0){
        return TRUE;
    }
    for (i = 0; i < strlen(text); ++i) {
        if(text[i] != ' '){
            return FALSE;
        }
    }
    return TRUE;
}

/**
 * The method checks if a given text is a number
 * @param text the text input
 * @return the number as integer otherwise INVALID_NUMBER(-1000)
 */
int getNumber(char *text){
    long ret;
    char *ptr;
    if(text == NULL){
        return INVALID_NUMBER;
    }
    if(text[strlen(text) - 1] == '+'){
        return INVALID_NUMBER;
    }
    ret = strtol(text, &ptr, 10);
    if(!isEmpty(ptr)){
        return INVALID_NUMBER;
    }
    return ret;
}

/**
 * removing ALL spaces from the text given
 * @param text the text input
 */
void deleteSpaces(char* text) {
    int i, j;
    i = j = 0;
    if(text == NULL){
        return;
    }
    while (text[i]) {
        if (text[i] != ' ') {
            text[j] = text[i];
            j++;
        }
        i++;
    }
    text[j] = '\0';
}

/**
 * The method remove unneeded spaces - unneeded is all the places space used more then once
 * @param text the text input
 */
void deleteUnNeededSpaces(char *text) {
    char textWithoutSpaces[LINE_MAX_LEN] = "";
    char space[] = " ";

    char *token = strtok(text, space);

    while (token != NULL) {
        strcat(textWithoutSpaces, token);
        strcat(textWithoutSpaces, " ");
        token = strtok(NULL, space);
    }
    strcpy(text, textWithoutSpaces);
}

/**
 * The method checks if one of the given operation code contain inside a text given
 * @param text the text input
 * @return returns the index of the operation code in the array otherwise UNDEFINED_OPERATION(-1)
 */
int getOperationCodeValue(char *text) {
    int i;
    if(text == NULL){
        return UNDEFINED_OPERATION;
    }
    for (i = 0; i < 16; ++i) {
        if (strstr(text, operationCode[i]) != NULL) {
            return i;
        }
    }
    return UNDEFINED_OPERATION;
}

/**
 * The method remove the part of the text until a given char
 * @param text the text input
 * @param c the char to remove until it
 */
void removeUntilChar(char *text, char c) {
    char *position = strchr(text, c);
    if(text == NULL){
        return;
    }
    if (position != NULL) {
        memmove(text, position + 1, strlen(position));
    }
}

/**
 * The method create a copy of a string
 * -- NEED TO FREE ALLOCATED MEMORY WHEN USING THE METHOD --
 * @param text the text input
 * @return char* copy of the text given
 */
char *copyString(char* text) {
    char *rowCopy;
    if(text == NULL){
        return NULL;
    }
    rowCopy = malloc((strlen(text) + 1) * sizeof(char));
    if (rowCopy == NULL){
        printAllocationFailure();
    }
    strcpy(rowCopy, text);
    return rowCopy;
}

/**
 * The method check if a given text ends with colon (':')
 * @param text the text input
 * @return TRUE(1) if the the text ends with colon otherwise FALSE(0)
 */
int isEndingWithColon(char *text) {
    int length = strlen(text);
    if (text[length - 1] == ':') {
        return TRUE;
    }
    return FALSE;
}

/**
 * The method create a copy of a string until a text format given
 * -- NEED TO FREE ALLOCATED MEMORY WHEN USING THE METHOD --
 * @param text the text input
 * @param format the format to copy until
 * @return char* copy of the text given until format
 */
char *copyToFirstFormat(char *text, char *format) {
    char *rowCopy = copyString(text);
    char *token = strtok(rowCopy, format);
    char *tokenCopy = copyString(token);
    free(rowCopy);
    return tokenCopy;
}

/**
 * The method check if a given Row is begging with comma
 * @param row | "Row" type | the row input that contain the text
 * @return TRUE(1) if the row beginning with comma otherwise FALSE(0)
 */
int isRowBeginningWithComma(Row row) {
    if (row.text[0] == ';') {
        return TRUE;
    }
    return FALSE;
}

/**
 * The method checks if two texts are equal
 * @param text1 the first text input
 * @param text2 the second text input
 * @return TRUE(1) if equal otherwise FALSE(0)
 */
int isStringEqual(char *text1 , char *text2){
    if(text1 == NULL && text2 == NULL){
        return TRUE;
    }
    if(text1 == NULL){
        return FALSE;
    }
    if(text2 == NULL){
        return FALSE;
    }
    if(strcmp(text1, text2) == 0){
        return TRUE;
    }
    return FALSE;
}

/**
 * The method remove leading and trailing spaces from a text given
 * @param text the first input
 */
void removeLeadingAndTrailingSpaces(char *text) {
    int start = 0;
    int i, j;
    int end = strlen(text) - 1;

    while (text[start] == ' ')
        start++;

    while (end >= 0 && text[end] == ' ')
        end--;

    for (i = 0, j = start; j <= end; i++, j++)
        text[i] = text[j];

    text[i] = '\0';
}

/**
 * The method sets input and output to be the input and output from a given row
 * @param row the text input representing a row
 * @param input a pointer to char* that need to be input
 * @param output a pointer to char* that need to be output
 */
void getInputAndOutputFromRow(char* row , char **input ,char **output){
    char* copy = copyString(row);
    removeUntilChar(copy,' ');

    if(copy[0] != ','){
        (*input) = copyToFirstFormat(copy, ",");
    }
    if (isContainComma(copy)) {
        removeUntilChar(copy, ',');
        (*output) = copyString(copy);
    }

    deleteSpaces(*input);
    deleteSpaces(*output);
    free(copy);
}

/**
 * The method checks if a text given starts with a letter
 * @param text
 * @return TRUE(1) if starts with a letter otherwise FALSE(0)
 */
int isBeggingWithLetter(char *text) {
    if(text != NULL && ((text[0] >= 'A' && text[0] <= 'Z') || (text[0] >= 'a' && text[0] <= 'z'))){
        return TRUE;
    }
    return FALSE;
}

/**
 * The method checks if a string contain only letters or numbers
 * @param text
 * @return TRUE(1) if contain only letter or numbers otherwise FALSE(0)
 */
int isStringContainOnlyLettersOrNumbers(char *text) {
    int i;
    for (i = 0; i < strlen(text); i++) {
        char c = text[i];
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))) {
            return FALSE;
        }
    }
    return TRUE;
}

void changeNameOfFile(char **pText) {
   strcat(*pText,".am\0");
}
