#include "Headers/header.h"

/**
 * this file contain method helpers to the guidance command.
 */

/**
 * check if the row contain guidance command
 * @param row the cuurent row in the file
 * @return the value of guidance, NOT_GUIDANCE - 1, EXTERN - 0, ENTRY - 1, DATA - 2, STRING - 3
 */
int isGuidance(char *row) {
    int i;
    for (i = 0; i < 4; i++) {
        if (strstr(row, guidance[i]) != NULL) {
            return i;
        }
    }
    return NOT_GUIDANCE;
}

/**
 * analyze the guidance command, if the command is valid.
 * @param row the row with guidance command
 * @param guid the number of command,  EXTERN - 0, ENTRY - 1, DATA - 2, STRING - 3
 * @param Dc the data counter
 * @param name the label name, if its extern or entry guidance.
 */
void guidanceAnalyze(char *row, int guid, int *Dc, char **name) {
    char *copy = copyString(row);
    switch (guid) {
        case EXTERN:
            *name = copyString(getLabelName(copy));
            break;
        case ENTRY:
            *name = copyString(getLabelName(copy));
            break;
        case DATA:
            (*Dc) += analyzeDataGuidance(row);
            break;
        case STRING:
            (*Dc) += analyzeStringLength(row);
            break;
    }
    free(copy);
}

/**
 * check if entry command is valid
 * @param pLabels the struct of all labels
 * @param length the length of labels
 * @param name the name of this entry label
 * @param isWarning the flag for warnings
 * @return TRUE - 1 if this label entry valid, else return FALSE - 0
 */
int entryValidation(Label **pLabels, int length, char *name , int* isWarning) {
    Label *label = isLabelNameUsedInCurrentFile(*pLabels, length, name);
    if(label != NULL && (*label).isEntry){
        (*isWarning) = TRUE;
        printWarning(4);
    }
    if (label != NULL) {
        (*label).isEntry = TRUE;
        return TRUE;
    }
    return FALSE;
}

/**
 * get new label, create and adding him to the label struct
 * @param name name of the new label
 * @param pLabel pointer to the label array struct
 * @param length pointer to length of label struct
 */
void createExternLabels(char *name, Label **pLabel, int *length) {
    Label currentLabel;
    char *comma = ",";
    removeLeadingAndTrailingSpaces(name);
    name = strtok(name , comma);
    while(name != NULL){
        removeLeadingAndTrailingSpaces(name);
        currentLabel = initializeLabel(name, 0, FALSE, TRUE);
        addToLabelArray(pLabel, currentLabel, length);
        name = strtok(NULL , comma);
    }
}