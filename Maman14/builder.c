#include "Headers/header.h"

/**
 * this file building all our struct
 */

/**
 * get the current file and build the rowArray struct
 * @param file current file
 * @return rowArray struct
 */
RowArray rowArrayBuilder(FILE *file ,  int *isValid) {
    int counter = 0;
    RowArray rowArray;
    Row *row = NULL;
    char *currentRow = getRow(file , isValid);

    while (currentRow != NULL) {
        counter++;
        row = (Row *) realloc(row, (counter + 1) * sizeof(Row));
        if(row == NULL){
            printAllocationFailure();
            exit(1);
        }

        if (row == NULL) {
            printError(8);
            exit(1);
        }
        row[counter - 1].text = currentRow;
        currentRow = getRow(file , isValid);
    }
    rowArray.row = row;
    rowArray.length = counter;

    return rowArray;
}

/**
 * this method get a file and make every row in file to char *row struct.
 * @param file the current file we work on.
 * @return
 */
char *getRow(FILE *file , int *isValid) {
    int c = -1 , counter = 0;
    char *currentRow = (char *) malloc(LINE_MAX_LEN * sizeof(char));
    if (currentRow == NULL){
        printAllocationFailure();
    }
    while ((c = fgetc(file)) != EOF) {
        if (counter > 79) {
            printError(0);
            (*isValid) = 0;
            free(currentRow);
            return NULL;
        }
        if ((c == '\n' || c == '\t' || c == ' ' || c == '\v' || c == '\r') && counter == 0) {
            continue;
        }
        if (c == '\n') {
            currentRow[counter] = '\0';
            return currentRow;
        }
        if (c == '\r') {
            continue;
        }
        currentRow[counter] = c;
        counter++;
    }

    if (counter > 0) {
        currentRow[counter] = '\0';
        return currentRow;
    }

    free(currentRow);
    return NULL;
}

/**
 * build the binary table
 * @param oldLength the old length
 * @param newLength the new length
 * @param binaryTable the binary table
 * @return true - 1
 */
int createEmptyBinaryRows(int oldLength, int newLength, short **binaryTable) {
    int length = oldLength + newLength;
    *binaryTable = (short *) realloc(*binaryTable, (length) * sizeof(short *));
    if (*binaryTable == NULL) {
        printAllocationFailure();
    }
    initializeRowsToZero(binaryTable, length, oldLength);
    return TRUE;
}

/**
 * initialize every row to zero value
 * @param array the array
 * @param length
 * @param startIndex the index that we need to start initialize
 * @return
 */
int initializeRowsToZero(short **array, int length, int startIndex) {
    int i;
    for (i = startIndex; i < length; i++) {
        (*array)[i] = 0;
    }
    return TRUE;
}

/**
 * initialize the file name and open new file in this name
 * @param argv the name of argument
 * @param argc the counter of argument
 * @param files struct of files
 * @return TRUE - 1
 */
int openFiles(char **argv, int argc, sourceFiles *files) {
    int i;
    for (i = 1; i < argc; i++) {
        files[i - 1].fileBeforeMcro = fopen(argv[i], "r");
        files[i - 1].name = strtok(argv[i], ".");
        files[i - 1].isValid = TRUE;
        files[i - 1].isWarnings = FALSE;
        files[i - 1].isMcroValid = TRUE;

        if (files[i - 1].fileBeforeMcro == NULL) {
            printFileMissing(files[i - 1].name);
        }
    }
    return TRUE;
}

/**
 * this method get a struct tf rows
 * and initialize the text part in the struct to the rowToAdd
 * @param rows array of struct of rows
 * @param rowToAdd struct of rows to add to the struct rows
 * @param amount its the length of struct rows
 * @return TRUE - 1
 */
int addLineToRowArray(Row **rows, Row rowToAdd, int amount) {
    reallocRows(rows, amount + 1);
    (*rows)[amount].text = rowToAdd.text;
    return TRUE;
}

/**
 * this function allocated memory for struct Row
 * @param rows the struct we want to allocate
 * @param amount how much we want allocate
 * @return TRUE - 1
 */
int reallocRows(Row **rows, int amount) {
    *rows = (Row *) realloc(*rows, amount * sizeof(Row));
    if (*rows == NULL) {
        printAllocationFailure();
    }
    return TRUE;
}


