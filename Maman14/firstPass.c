#include "Headers/header.h"

/**
 * The first pass of the assembler - validation and creation of binary array and label array etc...
 * @param file the current file
 * @param pLabelHead the headNode of the label linked list
 * @param pBinaryHead the headNode of the binary linked list
 * @param isFileValid is the file valid flag
 * @return TRUE(1) if the first pass finish successfully otherwise FALSE(0)
 */
int firstPass(sourceFiles *file, BinaryArray *binaryMachineCodeTable, LabelArray *labelArray, RowArray *textTable) {
    int i;
    Label *labels = malloc(1 * sizeof(Label));
    short *binaryArray = (short *) malloc(1 * sizeof(short));

    rewind((*file).fileAfterMcro);
    (*textTable) = rowArrayBuilder((*file).fileAfterMcro , &((*file).isValid));
    isAllocationSuccessful(2 , binaryArray , labels);

    (*binaryMachineCodeTable).length = 0;
    (*labelArray).length = 0;
    (*labelArray).DC = 0;
    (*labelArray).IC = 0;


    for (i = 0; i < (*textTable).length; i++) {
        rowNumber = i;
        firstPassHelper((*textTable).row[i], &binaryArray,
                        &(*binaryMachineCodeTable).length, &labels,
                        labelArray , &((*file).isValid), &((*file).isWarnings));
    }

    (*labelArray).labels = labels;
    (*binaryMachineCodeTable).array = binaryArray;

    return TRUE;
}

/**
 * The method is helper method of first pass helper
 * @param row the current row
 * @param BinaryTable the binary array
 * @param arrayLength the length of the array
 * @param labels pointer to the labels array of the file
 * @param labelArray the label array that contain labels and array length
 * @param isFileValid is the file valid flag
 * @return TRUE(1) if the row finish successfully otherwise FALSE(0) or LABEL_ERRORS(-1)
 */
int firstPassHelper(Row row, short **BinaryTable, int *arrayLength, Label **labels,
                    LabelArray *labelArray, int *isFileValid , int* isWarning) {
    Label currentLabel;
    Label *labelEntryRewrite;
    int label = FALSE, guid, labelRewriteFlag = FALSE, amountOfBinaryRows;
    char *rowCopy = copyString(row.text), *nameOfLabel = NULL;
    if (isLabelDeclaration(row)) {
        nameOfLabel = copyToFirstFormat(rowCopy, ":");
        if (!isLabelValid(nameOfLabel, *labels, labelArray->length)) {
            printError(14);
            (*isFileValid) = FALSE;
            freePointers(2 , nameOfLabel, rowCopy);
            return LABEL_ERROR;
        }
        labelEntryRewrite = isLabelNameUsedInCurrentFile(*labels, labelArray->length, nameOfLabel);
        if (labelEntryRewrite != NULL && labelEntryRewrite->isExtern == FALSE) {
            labelRewriteFlag = TRUE;
        }
        label = TRUE;
        removeUntilChar(rowCopy, ' ');
    }

    if (!isSyntaxValidFirstPass(rowCopy)) {
        (*isFileValid) = FALSE;
        if(nameOfLabel != NULL){
            free(nameOfLabel);
        }
        free(rowCopy);
        return FALSE;
    }

    amountOfBinaryRows = getAmountOfBinaryRowsNeeded(rowCopy);
    labelArray->IC += amountOfBinaryRows;

    guid = isGuidance(rowCopy);

    if (guid != NOT_GUIDANCE) {
        amountOfBinaryRows = labelArray->DC;
        guidanceAnalyze(rowCopy, guid, &labelArray->DC, &nameOfLabel);
        amountOfBinaryRows = labelArray->DC - amountOfBinaryRows;
    }

    if (guid == ENTRY) {
        if(label){
            (*isWarning) = TRUE;
            printWarning(2);
        }
        if (entryValidation(labels, labelArray->length, nameOfLabel , isWarning)) {
            freePointers(2 , rowCopy , nameOfLabel);
            return TRUE;
        }
        currentLabel = initializeLabel(nameOfLabel, 0, TRUE, FALSE);
        addToLabelArray(labels, currentLabel, &(labelArray->length));
        freePointers(2 , rowCopy , nameOfLabel);
        return TRUE;
    }

    if (guid == EXTERN) {
        if(label){
            (*isWarning) = TRUE;
            printWarning(3);
        }
        if(!isContainComma(nameOfLabel)){
            currentLabel = initializeLabel(nameOfLabel, 0, FALSE, TRUE);
            addToLabelArray(labels, currentLabel, &(labelArray->length));
            freePointers(2 , rowCopy , nameOfLabel);
            return TRUE;
        }
        createExternLabels(nameOfLabel, labels , &(labelArray->length));
        freePointers(2 , rowCopy , nameOfLabel);
        return TRUE;
    }

    if (label == TRUE && labelRewriteFlag == FALSE) {
        currentLabel = initializeLabel(nameOfLabel, labelArray->IC + labelArray->DC + 100 - amountOfBinaryRows, FALSE,
                                       FALSE);
        addToLabelArray(labels, currentLabel, &(labelArray->length));
    }

    if (labelRewriteFlag == TRUE) {
        (*labelEntryRewrite).binaryRowNumber = labelArray->IC + labelArray->DC + 100 - amountOfBinaryRows;
    }
    amountOfBinaryRows = labelArray->IC + labelArray->DC - (*arrayLength);
    createEmptyBinaryRows(*arrayLength, amountOfBinaryRows, BinaryTable);

    if (getOperationCodeValue(rowCopy) != UNDEFINED_OPERATION) {
        insertIntoBinaryArray(*arrayLength + amountOfBinaryRows - labelArray->DC, amountOfBinaryRows, rowCopy,
                              *BinaryTable);
    }
    *arrayLength += amountOfBinaryRows;
    if (nameOfLabel != NULL){
        free(nameOfLabel);
    }
    free(rowCopy);
    return TRUE;
}











