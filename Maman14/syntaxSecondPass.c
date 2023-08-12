#include "Headers/header.h"
/**
 * The file contain all the method relent for syntax validation of the second pass of the assembler
 */

/**
 * The method checks if the syntax is valid | only second pass validation |
 * the method call all print errors relevant for second pass
 * @param labelNode the node of the label linked list that contain all the current file labels
 * @param row | char* | the current row text
 * @return TRUE(1) if text is valid otherwise FALSE(1)
 */
int isSyntaxValidSecondPass(LabelArray *labelNode, char *row , int *isWarning) {
    char *input = NULL, *output = NULL;
    LabelArray labelArray;
    int isLabelNameExistsOutput, isLabelNameExistsInput;
    if ((isGuidance(row) == ENTRY) && !isEntryValidSecondPass(row, labelNode)) {
        return FALSE;
    }

    if (getOperationCodeValue(row) != UNDEFINED_OPERATION) {
        getInputAndOutputFromRow(row, &input, &output);
        labelArray = (*labelNode);
        isLabelNameExistsInput = isLabelNameUsedInCurrentFile(labelArray.labels, labelArray.length, input) != NULL;
        isLabelNameExistsOutput = isLabelNameUsedInCurrentFile(labelArray.labels, labelArray.length, output) != NULL;

        if (mightBeMcroOrLabel(input) && !isLabelNameExistsInput) {
            freePointers(2, input , output);
            printError(24);
            return FALSE;
        }
        if (mightBeMcroOrLabel(output) && !isLabelNameExistsOutput) {
            freePointers(2, input , output);
            printError(24);
            return FALSE;
        }

        freePointers(2, input ,output);

    }

    if(isGuidance(row) == EXTERN && !isExternValidSecondPass(row, labelNode , isWarning)){
        return FALSE;
    }

    return TRUE;
}

/**
 * The method checks if the label that is extern is valid | only second pass validation |
 * the method is an helper method of isSyntaxValidSecondPass
 * @param row | char* | the current row text
 * @param labelNode the node of the label linked list that contain all the current file labels
 * @param isWarning is the file have warning or not
 * @return TRUE(1) if label is valid otherwise FALSE(1)
 */
int isExternValidSecondPass(char *row, LabelArray *labelNode , int *isWarnings) {
    char *labelName= copyString(row);
    removeLeadingAndTrailingSpaces(row);
    removeUntilChar(labelName, ' ');
    deleteSpaces(labelName);

    if(isLabelExternButDeclaredInFile((*labelNode), labelName , isWarnings)){
        printError(25);
        free(labelName);
        return FALSE;
    }
    free(labelName);
    return TRUE;
}

/**
 * The method checks if a label declared as extern but also declared as regular label
 * the method also print warning in case a method declared as label multiple times
 * the method is an helper method of isSyntaxValidSecondPass
 * @param labelArray the label array of the current file
 * @param name the label name
 * @param isWarning is the file have warning or not
 * @return TRUE(1) if the label is extern but declared in file otherwise FALSE(0)
 */
int isLabelExternButDeclaredInFile(LabelArray labelArray, char *name , int *isWarning) {
    int length = labelArray.length,  i , counter = 0 ,counterExtern = 0;
    Label currentLabel;
    char* currName;

    for (i = 0; i < length; i++) {
        currentLabel = labelArray.labels[i];
        currName = currentLabel.name;
        if(isStringEqual(name , currName) && !currentLabel.isExtern){
            counter++;
        }
        if(isStringEqual(name , currName) && currentLabel.isExtern){
            counterExtern++;
        }
    }

    if(counter > 1){
        return TRUE;
    }
    if(counterExtern >= 1 && counter == 1){
        return TRUE;
    }
    if (counterExtern > 1){
        (*isWarning) = 1;
        printWarning(0);
    }
    return FALSE;
}

/**
 * The method checks if a label that is declared as entry is valid | only second pass validation |
 * the method is an helper method of isSyntaxValidSecondPass
 * @param text the text input (text of the row)
 * @param labelNode the node of the label linked list that contain all the current file labels
 * @return TRUE(1) if the entry is valid otherwise FALSE(1)
 */
int isEntryValidSecondPass(char *text, LabelArray *labelNode) {
    char *labelName = copyString(text);
    removeLeadingAndTrailingSpaces(text);
    removeUntilChar(labelName, ' ');
    deleteSpaces(labelName);
    if(isEntryDeclaredAlsoAsExtern(labelNode, labelName)){
        printError(28);
        free(labelName);
        return FALSE;
    }
    if (isEntryDeclaredWithoutInitialization(labelNode, labelName)) {
        printError(23);
        free(labelName);
        return FALSE;
    }
    free(labelName);
    return TRUE;
}

/**
 * The method checks if a label that is declared as entry also called as extern
 * the method is an helper method of isEntryValidSecondPass
 * @param labelNode the node of the label linked list that contain all the current file labels
 * @param name the label name
 * @return TRUE(1) if the entry declared also as extern otherwise FALSE(1)
 */
int isEntryDeclaredAlsoAsExtern(LabelArray *labelNode, char *name) {
    Label *label = isLabelNameUsedInCurrentFile((*labelNode).labels, (*labelNode).length, name);
    if (label != NULL && (*label).isEntry && (*label).isExtern ) {
        return TRUE;
    }
    return FALSE;
}

/**
 * The method checks if a label declared without Initialization in the same file
 * the method is an helper method of isEntryValidSecondPass
 * @param labelNode the node of the label linked list that contain all the current file labels
 * @param labelName the label name
 * @return TRUE(1) if the entry declared in file but didnt initialized otherwise FALSE(1)
 */
int isEntryDeclaredWithoutInitialization(LabelArray *labelNode, char *labelName) {
    Label *label = isLabelNameUsedInCurrentFile((*labelNode).labels, (*labelNode).length, labelName);
    if (label != NULL && (*label).binaryRowNumber == 0) {
        return TRUE;
    }
    return FALSE;
}
