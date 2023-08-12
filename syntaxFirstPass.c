#include "Headers/header.h"
/**
 * The method checks if the syntax is valid | only first pass validation |
 * the method call all print errors method relevant for first pass
 * @param row | char* | the current row text
 * @return TRUE(1) if text is valid otherwise FALSE(1)
 */
int isSyntaxValidFirstPass(char *row) {
    int opcValue;
    char *input = NULL , *output = NULL, *copyToFirstSpace;
    char *copy = copyString(row);

    copyToFirstSpace = copyToFirstFormat(copy ," ");
    if ((opcValue = getOperationCodeValue(copyToFirstSpace)) == UNDEFINED_OPERATION &&
        isGuidance(copyToFirstSpace) == NOT_GUIDANCE) {
        printError(1);
        freePointers(2, copy, copyToFirstSpace);
        return FALSE;
    }
    if(isGuidance(copyToFirstSpace) != NOT_GUIDANCE && isGuidanceValid(copy)){
        freePointers(2, copy , copyToFirstSpace);
        return TRUE;
    }
    freePointers(1 , copyToFirstSpace);
    getInputAndOutputFromRow(copy , &input , &output);

    if (getOperationCodeValue(copy) == STOP){
        removeUntilChar(copy,'p');
        if (!isEmpty(copy)){
            printError(30);
            return FALSE;
        }
        freePointers(3, input, output ,copy);
        return TRUE;
    }

    if (!isOperationSyntaxValidFirstPass(opcValue, input, output)) {
        freePointers(3, input, output ,copy);
        return FALSE;
    }
    freePointers(3, input, output , copy);
    return TRUE;
}

/**
 * The method checks if a given row that seems to be a guidance is a valid guidance
 * the method is an helper method of isSyntaxValidFirstPass();
 * @param row | char* | the current row text
 * @return TRUE(1) if guidance is valid otherwise FALSE(1)
 */
int isGuidanceValid(char *row) {
    char* copy = copyString(row) , *copyToFirstSpace = copyToFirstFormat(copy, " ");
    int isGuid = isGuidanceValidHelper(copyToFirstSpace);
    if(isGuid == NOT_GUIDANCE){
        freePointers(2, copy, copyToFirstSpace);
        printError(1);
        return FALSE;
    }
    if(!isContainSpace(copy)){
        freePointers(2, copy, copyToFirstSpace);
        printError(29);
        return FALSE;
    }

    removeUntilChar(copy, ' ');
    if(isGuid != ENTRY && isGuid != EXTERN){
        deleteSpaces(copy);
    }

    switch (isGuid) {
        case STRING:
            if(!isStringValid(copy)){
                freePointers(2, copy, copyToFirstSpace);
                return FALSE;
            }
            break;
        case DATA:
            if(!isDataValid(copy)){
                freePointers(2, copy, copyToFirstSpace);
                return FALSE;
            }
            break;
        case ENTRY:
            if(!isEntryValid(copy)){
                freePointers(2, copy, copyToFirstSpace);
                return FALSE;
            }
            break;
        case EXTERN:
            if(!isExternValid(copy)){
                freePointers(2, copy, copyToFirstSpace);
                return FALSE;
            }
            break;
    }
    freePointers(2, copy, copyToFirstSpace);
    return TRUE;
}

/**
 * The method checks if a given entry is a valid entry
 * the method is an helper method of isGuidanceValid();
 * @param row | char* | the current row text
 * @return TRUE(1) if entry is valid otherwise FALSE(1)
 */
int isEntryValid(char *text) {
    removeLeadingAndTrailingSpaces(text);
    if(!mightBeMcroOrLabel(text)){
        printError(21);
        return FALSE;
    }
    return TRUE;
}

/**
 * The method checks if a given extern is a valid extern
 * the method is an helper method of isGuidanceValid();
 * @param row | char* | the current row text
 * @return TRUE(1) if extern is valid otherwise FALSE(1)
 */
int isExternValid(char *text) {
    char* copy = copyString(text) , *comma = "," , *token;
    token = strtok(copy , comma);
    while(token != NULL){
        removeLeadingAndTrailingSpaces(copy);
        if(!mightBeMcroOrLabel(copy)){
            printError(22);
            free(copy);
            return FALSE;
        }
        token = strtok(NULL , comma);
    }
    free(copy);
    return TRUE;
}

/**
 * The method checks if a given data is a valid data
 * the method is an helper method of isGuidanceValid();
 * @param row | char* | the current row text
 * @return TRUE(1) if data is valid otherwise FALSE(1)
 */
int isDataValid(char *text) {
    char* copy = copyString(text) , *comma = "," , *token;

    int currentVal;
    token = strtok(copy , comma);
    while(token != NULL){
        currentVal = getNumber(token);
        if(currentVal == INVALID_NUMBER){
            printError(18);
            free(copy);
            return FALSE;
        }
        if(currentVal > MAX_VAL_DATA ){
            printError(19);
            free(copy);
            return FALSE;
        }
        if(currentVal < MIN_VAL_DATA ){
            printError(20);
            free(copy);
            return FALSE;
        }
        token = strtok(NULL , comma);
    }
    free(copy);
    return TRUE;
}

/**
 * the method is an helper method of isGuidanceValid();
 * @param text the current row text
 * @return TRUE(1) if thier is possibility of the row to be guidance otherwise FALSE(1)
 */
int isGuidanceValidHelper(char *text) {
    int i;
    if(text == NULL){
        return NOT_GUIDANCE;
    }
    deleteSpaces(text);
    for (i = 0; i < 4; i++) {
        if (strstr(text, guidance[i]) != NULL && strlen(guidance[i]) == strlen(text)) {
            return i;
        }
    }
    return NOT_GUIDANCE;
}
/**
 * The method checks if a given string is a valid string
 * the method is an helper method of isGuidanceValid();
 * @param text | char* | the guidance string text
 * @return TRUE(1) if data is valid otherwise FALSE(1)
 */
int isStringValid(char *text) {
    int length = strlen(text);
    if(text[length - 1] != '"' || text[0] != '"'){
        printError(17);
        return FALSE;
    }
    return TRUE;
}

/**
 * The method checks if thier is possibility of text to be address 1
 * @param text
 * @return TRUE(1) if text is a valid address 1 otherwise FALSE(1)
 */
int oneValidate(char *text) {
    int num;
    if (text == NULL){
        return FALSE;
    }
    num = getNumber(text);
    if (num == INVALID_NUMBER || (num > MAX_VAL || num < MIN_VAL)) {
        return FALSE;
    }
    return TRUE;
}

/**
 * The method checks if thier is possibility of text to be address 5
 * @param text
 * @return TRUE(1) if text is a valid address 5 otherwise FALSE(1)
 */
int fiveValidate(char *text) {
    int length;
    char *copy;
    if (text == NULL){
        return FALSE;
    }
    copy = copyString(text);
    length = strlen(copy);
    if (length > 3) {
        free(copy);
        return FALSE;
    }

    sscanf(copy, "%[^0-7]", copy);
    if (length != (strlen(copy) + 1)) {
        free(copy);
        return FALSE;
    }

    if (strstr(copy, "@r") == NULL) {
        free(copy);
        return FALSE;
    }
    free(copy);
    return TRUE;
}


/**
 * The method checks if thier is possibility of text to be address 3 (LABEL)
 * @param text
 * @return TRUE(1) if text is a might be address 3 otherwise FALSE(1)
 */
int mightBeMcroOrLabel(char *name) {
    if(name == NULL){
        return FALSE;
    }
    if(!isBeggingWithLetter(name)){
        return FALSE;
    }
    if (getOperationCodeValue(name) != UNDEFINED_OPERATION) {
        return FALSE;
    }
    if (!isStringContainOnlyLettersOrNumbers(name)) {
        return FALSE;
    }
    if (strlen(name) > LABEL_MAX_LEN) {
        return FALSE;
    }
    return TRUE;
}

/**
 * The method checks if an operation row is valid
 * @param opcValue the index of the operation in the operation array
 * @param input the input of the operation can be null
 * @param output the output of the operation can be null
 * @return TRUE(1) if text is a might be address 3 otherwise FALSE(1)
 */
int isOperationSyntaxValidFirstPass(int opcValue, char *input, char *output) {
    int flag = FALSE;
    if (opcValue == MOV || opcValue == ADD || opcValue == SUB) {
        if (!oneValidate(input) && !mightBeMcroOrLabel(input) && !fiveValidate(input)) {
            printError(15);
            flag++;
        }
        if (!mightBeMcroOrLabel(output) && !fiveValidate(output)) {
            printError(16);
            flag++;
        }
        if (flag != FALSE) {
            return FALSE;
        }
        return TRUE;
    }
    if (opcValue == CMP) {
        if (!oneValidate(input) && !mightBeMcroOrLabel(input) && !fiveValidate(input)) {
            printError(15);
            flag++;
        }
        if (!oneValidate(output) && !mightBeMcroOrLabel(output) && !fiveValidate(output)) {
            printError(16);
            flag++;
        }
        if (flag != FALSE) {
            return FALSE;
        }
        return TRUE;
    }
    if (opcValue == NOT || opcValue == CLR || opcValue == INC || opcValue == DEC || opcValue == JMP ||
        opcValue == BNE || opcValue == RED || opcValue == JSR) {
        if (output != NULL) {
            printError(15);
            flag++;
        }
        if (!mightBeMcroOrLabel(input) && !fiveValidate(input)) {
            printError(16);
            flag++;
        }
        if (flag != FALSE) {
            return FALSE;
        }
        return TRUE;
    }
    if (opcValue == LEA) {
        if (!mightBeMcroOrLabel(input)) {
            printError(15);
            flag++;
        }
        if (!mightBeMcroOrLabel(input) && !fiveValidate(input)) {
            printError(16);
            flag++;
        }
        if (flag != FALSE) {
            return FALSE;
        }
        return TRUE;

    }
    if (opcValue == PRN) {
        if (output != NULL) {
            printError(27);
            flag++;
        }
        if (!oneValidate(input) && !mightBeMcroOrLabel(input) && !fiveValidate(input)) {
            printError(16);
            flag++;
        }
        if (flag != FALSE) {
            return FALSE;
        }
        return TRUE;
    }
    if (opcValue == RTS || opcValue == STOP) {
        if (input != NULL) {
            printError(27);
            flag++;
        }
        if (output != NULL) {
            printError(27);
            flag++;
        }
        if (flag != FALSE) {
            return FALSE;
        }
        return TRUE;
    }
    return FALSE;
}