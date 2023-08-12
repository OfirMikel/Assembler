#include "Headers/header.h"

/**
 * The method analyze every row of the txt file and validate it for the pre assembler
 * the method is an helper method of preAssembler()
 * @param sourceFile the current file
 * @param fileAm the pointer to the files after mcro that the method creates
 * @return TRUE(1) if valid and if mcro is incorrect returns MCRO_ERRORS(-1)
 */
int preAssembler(sourceFiles *sourceFile) {
    RowArray rowArray = rowArrayBuilder((*sourceFile).fileBeforeMcro , &((*sourceFile).isValid));
    char *currentFileName = (*sourceFile).name;
    Row currentRow;
    Mcro currentMcro;
    int i, mcroRowsAmount;
    McroNode *head = NULL;

    if(!(*sourceFile).isValid){
        return FALSE;
    }
    changeNameOfFile(&(currentFileName));
    (*sourceFile).fileAfterMcro = fopen(currentFileName, "w+");

    if((*sourceFile).fileAfterMcro == NULL){
        printFileOpenError();
    }

    for (i = 0; i < rowArray.length; i++) {
        currentRow = rowArray.row[i];
        rowNumber = i;
        if (isRowBeginningWithComma(currentRow)) {
            continue;
        }
        deleteUnNeededSpaces(currentRow.text);

        if (isMcroCalledInLine(currentRow.text)) {
            mcroRowsAmount = analyzeMcro(rowArray, &head);
            if(mcroRowsAmount == MCRO_ERRORS){
                fclose((*sourceFile).fileAfterMcro);
                remove(currentFileName);
                freeRowArray(&rowArray);
                freeLinkedList(head);
                (*sourceFile).isValid = FALSE;
                (*sourceFile).isMcroValid = FALSE;
                return FALSE;
            }
            i = mcroRowsAmount + i + 1;
            continue;
        }

        if (isMcroCalled(currentRow, head)) {
            currentMcro = searchMcro(currentRow, head);
            spanMcroToFile((*sourceFile).fileAfterMcro, currentMcro);
            continue;
        }

        spanRowToFileAm((*sourceFile).fileAfterMcro, currentRow);
    }

    freeLinkedList(head);
    freeRowArray(&rowArray);
    return TRUE;
}

