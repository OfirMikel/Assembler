#include "Headers/header.h"

/**
 * The method is the second pass of the assembler
 * @param file a pointer to source file
 * @param pHeadLabel the head of the label linked list
 * @param pHeadBinary the head of the binary table linked list
 */
void secondPass(sourceFiles *files, BinaryArray *binaryArray, LabelArray *labelArray, RowArray *rowArray) {
    int externLength = 0;
    ExternArray externArrayStruct;
    Extern *externArray = malloc(sizeof(Extern));
    isAllocationSuccessful(1, externArray);

    secondPassHelper(files,labelArray ,  binaryArray, &externArray, &externLength ,rowArray);

    externArrayStruct.length = externLength;
    externArrayStruct.externs = externArray;
    if ((*files).isValid){
        outputFiles((*labelArray), (*binaryArray),externArrayStruct);
    }


    freePointers(1,externArray);
}

/**
 * The method is an helper method of secondPass
 * @param file the current source file
 * @param pLabelNode a pointer to the current node of label
 * @param pBinaryNode a pointer to the current node of binary
 * @param externArray the current extern array
 * @param length the extern array length
 */
void secondPassHelper(sourceFiles *file, LabelArray *labelArray, BinaryArray *pBinary, Extern **externArray,
                      int *length, RowArray *rowArray) {
    int i, currentDC = (*labelArray).DC, currentIC = (*labelArray).IC;

    for (i = 0; i < (*rowArray).length; i++) {
        rowNumber = i;
        validateRow((*rowArray).row[i], pBinary, labelArray, file, &currentDC, &currentIC, externArray, length);
    }
}

/**
 * The method is an helper of secondPass that validate every row
 * @param row the current row
 * @param pBinary a pointer to the current node of binary
 * @param pLabel a pointer to the current node of label
 * @param file the current source file
 * @param currentDC the current DC
 * @param currentIC the current IC
 * @param pExternArray the Extern Array
 * @param length the extern array length
 */

void validateRow(Row row, BinaryArray *pBinary, LabelArray *labelArray, sourceFiles *file, int *currentDC,
                 int *currentIC, Extern **pExternArray, int *length) {
    char *textCopy = copyString(row.text);

    if (isLabelDeclaration(row)) {
        removeUntilChar(textCopy, ':');
        removeLeadingAndTrailingSpaces(textCopy);
    }

    if (!isSyntaxValidSecondPass(labelArray, textCopy, &((*file).isWarnings)) || (*file).isValid == FALSE) {
        (*file).isValid = FALSE;
        free(textCopy);
        return;
    }

    if (isGuidance(textCopy) == DATA) {
        addDataToBinaryTable(textCopy, pBinary, currentDC, (*labelArray).DC);
        free(textCopy);
        return;
    }

    if (isGuidance(textCopy) == STRING) {
        addStringToBinaryTable(textCopy, pBinary, currentDC,(*labelArray).DC);
        free(textCopy);
        return;
    }

    addLabelToBinaryTable(textCopy, pBinary, labelArray, currentIC, pExternArray, length);
    free(textCopy);
}
