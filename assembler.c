#include "Headers/header.h"


void assembler(sourceFiles *files, BinaryArray *binaryArray, LabelArray *labelArray, RowArray *rowArray , int len) {
    int i;
    for (i = 0; i < len ; i++) {
        fileName = copyString(files[i].name);
        preAssembler(&(files[i]));
        if(!(files[i]).isValid){
            continue;
        }
        firstPass(&(files[i]), binaryArray , labelArray , rowArray);

        secondPass(&(files[i]), binaryArray, labelArray, rowArray);

        freeRowArray(rowArray);
        freeLabelsName(labelArray);
        freePointers(3,(*labelArray).labels, fileName , binaryArray->array);
    }
}



