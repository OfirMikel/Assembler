#include "Headers/header.h"

/**
 * this file contain free memorise method helper
 */

/**
 * this method free allocated mamory in the pointers on the files and close the files
 * @param filesBeforeAm the file with the ending .as
 * @param lengthBeforeAm the length of the argument files with the ending of .as
 * @param filesAfterAm the files after the spending macro
 * @param lengthAfterAm the length of files after mcro
 */
void closeAndFreeFiles(sourceFiles *files, int length) {
    int i;

    for (i = 0; i < length; i++) {
        fclose(files[i].fileBeforeMcro);
    }
    for (i = 0; i < length; i++) {
        if(files[i].isMcroValid){
            fclose(files[i].fileAfterMcro);
        }
    }
    freePointers(1 , files);
}

/**
 * this method get void * arguments, and free them all
 * @param sum the sum of the arguments that was sending
 * @param ... the arguments names
 */
void freePointers(int sum , ...){
        va_list list;
        int i;
        void *curr;
        va_start(list, sum);
        for(i=0; i < sum; i++){
            curr = va_arg(list, void*);
            if (curr != NULL){
                free(curr);
            }
        }
        va_end(list);
}

/**
 * this method free the struct of rows array
 * @param array struct of rows
 * @return TRUE - 1
 */
void freeRowArray(RowArray *array) {
    int i;
    for (i = 0; i < array->length; i++) {
        free(array->row[i].text);
    }
    free(array->row);
}

/**
 * free mcro nodes list struct
 * * @param node mcro nodes list struct
 * @return TRUE - 1
 */
int freeLinkedList(McroNode *node) {
    McroNode* current = node;
    McroNode* next;
    while(current != NULL){
        next = current->next;
        free(current);
        current = next;
    }
    return TRUE;
}
/**
 * free the Label array name
 * @param pArray label array pointer
 */
void freeLabelsName(LabelArray *pArray) {
    int i;
    for ( i = 0; i < (*pArray).length; ++i) {
        free(pArray->labels[i].name);
    }
}