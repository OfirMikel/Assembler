#include "Headers/header.h"

/**
 * The method give the amount of lines in the binary table needed for a row
 * @param row the row text
 * @return the number of lines that need to be added to binary table
 */
int getAmountOfBinaryRowsNeeded(char *row) {
    char* text = copyString(row);
    int opCode = getOperationCodeValue(text);
    char *input = NULL , *output = NULL;

    getInputAndOutputFromRow(row , &input ,&output);

    switch (opCode) {
        case MOV:
        case ADD:
        case SUB:
        case CMP:
            if(fiveValidate(input) && fiveValidate(output)){
                freePointers(3, text , input ,output);
                return 2;
            }
            freePointers(3, text , input,output);
            return 3;
            break;
        case NOT:
        case CLR:
        case INC:
        case DEC:
        case JMP:
        case BNE:
        case RED:
        case JSR:
        case LEA:
        case PRN:
            freePointers(3,text, input, output);
            return 2;
            break;
        case RTS:
        case STOP:
            freePointers(3, text , input, output);
            return 1;
            break;

    }
    freePointers(3, text , input,output);
    return FALSE;
}
