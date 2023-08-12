#include "Headers/header.h"

/**
 * this file contain method helpers to check and create labels.
 */

/**
 * check if the current label valid
 * @param name label name.
 * @param pLabel the array of label of struct.
 * @param length the length of label array struct.
 * @return
 */
int isLabelValid(char *name, Label *pLabel , int length) {
    Label *label;
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
    label = isLabelNameUsedInCurrentFile(pLabel,length,name);
    if(label != NULL  && (*label).binaryRowNumber != 0 ){
        return FALSE;
    }
    return TRUE;
}

/**
 * check if the first part of the row is label
 * @param row current row
 * @return TRUE - 1 if this row contain label, else FALSE - 0.
 */
int isLabelDeclaration(Row row) {
    char *rowToFirstSpace = copyToFirstFormat(row.text, " ");
    if (isEndingWithColon(rowToFirstSpace)) {
        free(rowToFirstSpace);
        return TRUE;
    }
    free(rowToFirstSpace);
    return FALSE;
}

/**
 * get label struct and initialize the values in the struct to current values label
 * @param name the current label name
 * @param rowNum the number of the row in the table of binary.
 * @param isEntry if entry command was in the row, than flag isEntry will initialize to TRUE - 1
 * @param isExtern if extern command was in the row, than flag isExtern will initialize to TRUE - 1
 * @return label struct
 */
Label initializeLabel(char* name , short rowNum , int isEntry , int isExtern){
    Label label;
    label.name = copyString(name);
    label.binaryRowNumber = rowNum;
    label.isEntry = isEntry;
    label.isExtern = isExtern;
    return label;
}

/**
 * get label struct and adding him to labelArray struct
 * @param pLabel a the array of struct label in the labelArray struct
 * @param label to add
 * @param length pointer to the length of label array
 */
void addToLabelArray(Label **pLabel, Label label , int *length) {
    (*length)++;
    *pLabel = (Label *)realloc(*pLabel, (*length + 1) * sizeof(Label));
    if (pLabel == NULL){
        printAllocationFailure();
    }
    (*pLabel)[*length - 1] = label;
}

/**
 * check if in our file was label name with the same name
 * @param label the label array struct
 * @param length the length of label array.
 * @param name the name of label we check if is exist.
 * @return pointer to the label array.
 */
Label* isLabelNameUsedInCurrentFile(Label *label,  int length , char* name){
    char *currentName = NULL;
    int i;
    if (label == NULL) {
        return NULL;
    }
    for (i = 0; i < length; i++) {
        currentName = copyString(label[i].name);
        if (currentName == NULL){
            continue;
        }
        if(isStringEqual(name,currentName)){
            free(currentName);
            return &label[i];
        }
        free(currentName);
    }
    return NULL;
}

/**
 * get part of label command and return is name
 * @param text the text until first space
 * @return the text until first space- label name.
 */
char* getLabelName(char *text) {
    removeUntilChar(text, ' ');
    deleteSpaces(text);
    return text;
}

/**
 * this method get uses in extern label and adding this uses
 * @param pExternArray the node with the extern labels
 * @param name of the label
 * @param rowNum the row number
 * @param length of the extern node
 */
void addToExternArray(Extern **pExternArray, char *name, short rowNum , int *length) {
    (*pExternArray)[(*length)].name = name;
    (*pExternArray)[(*length)].rowNumber = rowNum;
    (*length)++;

    *pExternArray = (Extern *)realloc(*pExternArray, ((*length) + 1) * sizeof(Extern));
    if (*pExternArray == NULL){
        printAllocationFailure();
    }
}

