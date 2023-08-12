#include "Headers/header.h"

/*
 *The file contains methods that convert the values to binary according to the assembler
 */

/**
 * this method get row from the file after checking if this row valid,
 * and insert the row to binary values
 * @param length the binary length
 * @param add th data counter
 * @param row the full row
 * @param binaryArray the binary array
 */
void insertIntoBinaryArray(int length, int add, char *row, short *binaryArray) {
    short opCode = getOperationCodeValue(row);
    int locationInTable = length - add;
    switch (opCode) {
        case MOV:
        case CMP:
        case ADD:
        case SUB:
        case LEA:
            getTwoOperand(row, binaryArray, locationInTable);
            break;
        case CLR:
        case INC:
        case DEC:
        case JMP:
        case BNE:
        case RED:
        case PRN:
        case JSR:
            getOneOperand(row, binaryArray, locationInTable);
            break;
        case RTS:
        case STOP:
            getZeroOperand(row, binaryArray, locationInTable);
            break;
    }
}

/**
 * this method get rows with operations without operand (stop, rts), and calculate binary value of the row.
 * @param row get the full row
 * @param binaryArray the binary array
 * @param locationInTable the location to add
 */
void getZeroOperand(char *row, short *binaryArray, int locationInTable) {
    short opCode = getOperationCodeValue(row);
    addOPCode(opCode, &(binaryArray[locationInTable]));
}

/**
 * this method get rows with operations that get one operand,
 * such as- MOV, CMP, ADD, SUB, LEA
 * and calculate binary value of the row
 * @param row get the full row
 * @param binaryArray the binary array
 * @param locationInTable the location to add
 */
void getOneOperand(char *row, short *binaryArray, int locationInTable) {
    char *copyChar = copyString(row), *currPart;
    short opCode = getOperationCodeValue(row), addressCode;

    addOPCode(opCode, &(binaryArray[locationInTable]));
    removeUntilChar(copyChar, ' ');
    currPart = copyToFirstFormat(copyChar, " ");
    addressCode = addressCodeNum(currPart);
    addDestination(addressCode, &(binaryArray[locationInTable]));

    switch (addressCode) {
        case 1:
            addNumberToBinaryArray(currPart, &(binaryArray[locationInTable + 1]));
            break;
        case 5:
            addRegisterToBinaryArray(currPart, &(binaryArray[locationInTable + 1]), 2);
            break;
        default:
            break;
    }
    freePointers(2, copyChar, currPart);
}

/**
 * this method get rows with operations that get two operand,
 * such as- CLR, INC, DEC, JMP, BNE, RED, PRN, JSR
 * and calculate binary value of the row.
 * @param row the full row
 * @param binaryArray the binary array
 * @param locationInTable the location to add
 */
void getTwoOperand(char *row, short *binaryArray, int locationInTable) {
    char *output, *input;
    short opCode = getOperationCodeValue(row), addressCodeInput, addressCodeOutput;

    addOPCode(opCode, &(binaryArray[locationInTable]));


    getInputAndOutputFromRow(row , &input , &output);
    addressCodeInput = addressCodeNum(input);
    addressCodeOutput = addressCodeNum(output);


    addOrigin(addressCodeInput, &(binaryArray[locationInTable]));
    addDestination(addressCodeOutput, &(binaryArray[locationInTable]));

    if (addressCodeInput == 5 && addressCodeOutput == 5) {
        addRegisterToBinaryArray(output, &(binaryArray[locationInTable + 1]), 2);
        addRegisterToBinaryArray(input, &(binaryArray[locationInTable + 1]), 7);
        freePointers(2, input,  output);
        return;
    }

    switch (addressCodeInput) {
        case 1:
            addNumberToBinaryArray(input, &(binaryArray[locationInTable + 1]));
            break;
        case 5:
            addRegisterToBinaryArray(input, &(binaryArray[locationInTable + 1]), 7);
            break;
        default:
            break;
    }

    switch (addressCodeOutput) {
        case 1:
            addNumberToBinaryArray(output, &(binaryArray[locationInTable + 2]));
            break;
        case 5:
            addRegisterToBinaryArray(output, &(binaryArray[locationInTable + 2]), 2);
            break;
        default:
            break;
    }
    freePointers(2, input,  output);

}

/**
 * this method get operand with address five(register), and put him in the right position of the row
 * @param Register - the register part in the row
 * @param binaryArray the array of binary values
 * @param shiftAmount how much to move the binary value
 */
void addRegisterToBinaryArray(char *Register, short *binaryArray, int shiftAmount) {
    int num;
    char *copy = copyString(Register);
    removeUntilChar(copy, 'r');
    num = getNumber(copy);
    num = num << shiftAmount;
    *binaryArray |= num;
    free(copy);
}

/**
 * this method get operand with address one, and insert him to the right location in the binary table
 * @param number the char part with the number
 * @param binaryArray the array of binary values
 */
void addNumberToBinaryArray(char *number, short *binaryArray) {
    short num;
    num = getNumber(number);
    if (num < 0) {
        returnNumToTenBits(&num);
    }
    num = num << 2;
    *binaryArray |= num;
}

/**
 * this method get the string part of data operation,
 * and insert every value to the separate index in the array
 * @param dataValues the string part with the data values
 * @param binaryArray the binary array
 */
void addDataNumberToBinaryArray(char *dataValues, short *binaryArray) {
    short num;
    num = getNumber(dataValues);
    if (num < 0) {
        returnNumToTwelveBits(&num);
    }
    *binaryArray |= num;
}

/**
 * this method get string from string operation
 * and insert every character to separate index in the array
 * @param stringPart the part with the string value
 * @param binaryArray the binary array
 */
void addStringNumberToBinaryArray(unsigned char stringPart, short *binaryArray) {
    short num = (short) stringPart;
    if (num < 0) {
        returnNumToTwelveBits(&num);
    }
    *binaryArray |= num;
}

/**
 * this method get each number from operations that not data and insert him to Twelve bits
 * @param num the number that put in operations
 */
void returnNumToTenBits(short *num) {
    *num *= -1;
    *num ^= BASE_10_BITES;
    *num += 1;
}

/**
 * this method get each number from data operation and insert him to Twelve bits
 * @param num the number that put in data operation
 */
void returnNumToTwelveBits(short *num) {
    *num *= -1;
    *num ^= BASE_12_BITES;
    *num += 1;
}

/**
 * this method get string part of operand
 * and use the helpers method to classify what address value of the operand.
 * @param operand the string part with operand (input/output)
 * @return the address value of the operand
 */
short addressCodeNum(char *operand) {
    char *copy = copyString(operand);
    deleteSpaces(copy);
    if (oneValidate(copy)) {
        free(copy);
        return 1;
    }
    if (fiveValidate(copy)) {
        free(copy);
        return 5;
    }
    if (mightBeMcroOrLabel(copy)) {
        free(copy);
        return 3;
    }

    return FALSE;
}

/**
 *this method get the value of operation,
 * and insert this value to the binary array in his position
 * @param OPCode the opcode value (according  to the operation table)
 * @param binaryArray the binary array
 */
void addOPCode(short OPCode, short *binaryArray) {
    short temp = OPCode;
    temp = temp << OPCODE_LOCATION;

    *binaryArray = *binaryArray | temp;
}

/**
 * get source operand value and insert him to binary array in his position
 * @param origin source operand value
 * @param binaryArray the binary array
 */
void addOrigin(short origin, short *binaryArray) {
    short temp = origin;
    temp = temp << ORIGIN_LOCATION;

    *binaryArray |= temp;

}

/**
 * get destination operand value and insert him to binary array in his position
 * @param dest destination operand value
 * @param binaryArray the binary array
 */
void addDestination(short dest, short *binaryArray) {
    short temp = dest;
    temp = temp << DESTINATION_LOCATION;

    *binaryArray |= temp;
}

/**
 * this method add every data to the binary array
 * @param dataPart the data values in the string
 * @param binaryTable the binary table
 * @param pDc pointer to the current dc
 * @param DC the data counter
 */
void addDataToBinaryTable(char *dataPart, BinaryArray *binaryTable, int *pDc, int DC) {
    char *copy = copyString(dataPart), *comma = "," , *token;
    short *binaryArray = (*binaryTable).array;
    int IC = (*binaryTable).length - DC;
    removeLeadingAndTrailingSpaces(copy);
    removeUntilChar(copy, ' ');
    token = strtok(copy, comma);
    while (token != NULL) {
        addDataNumberToBinaryArray(token, &(binaryArray[IC + DC - (*pDc)]));
        token = strtok(NULL, comma);
        (*pDc)--;
    }
    free(copy);

}

/**
 * this method add every character in the string, and add him to the binary array
 * @param stringPart the string part in the row
 * @param binaryTable the binary table
 * @param pDc pointer to the current dc
 * @param DC the data counter
 */
void addStringToBinaryTable(char *stringPart, BinaryArray *binaryTable, int *pDc, int DC) {
    char *copy = copyString(stringPart);
    short *binaryArray = (*binaryTable).array;
    int IC = (*binaryTable).length - DC, index = 0;

    removeLeadingAndTrailingSpaces(copy);
    removeUntilChar(copy, '"');
    while (copy[index] != '"') {
        addStringNumberToBinaryArray(copy[index], &(binaryArray[IC + DC - (*pDc)]));
        (*pDc)--;
        index++;
    }
    (*pDc)--;
    free(copy);
}

/**
 * this method adding the label value to the int that represent the row in binary value
 * @param valInBinaryArray this is pointer to the current int in binary array
 * @param num the value of the row that label in
 * @param isExt 1- its extern label, 0- its not a label extern
 */
void addLabelVelToBinaryArray(short *valInBinaryArray, short num, int isExt) {
    num = num << 2;
    (*valInBinaryArray) |= num;
    if (isExt) {
        (*valInBinaryArray) += 1;
        return;
    }
    (*valInBinaryArray) += 2;

}

/**
 * this method adding the label value to the int that represent the row in binary value
 * @param row - the part with the label name
 * @param binaryTable the binary table
 * @param labelArray the node of labels
 * @param ic the operation counter
 * @param pExternArray the node of extern label
 * @param lengthExtern the length of the node extern
 */
void addLabelToBinaryTable(char *row, BinaryArray *binaryTable, LabelArray *labelArray, int *ic, Extern **pExternArray,
                           int *lengthExtern) {
    char *copy = copyString(row), *input = NULL, *output = NULL, length = (*labelArray).length;
    int rowNeeded = getAmountOfBinaryRowsNeeded(copy);
    Label *inputLabel = NULL, *outputLabel = NULL;
    int currentRowBinary = (*labelArray).IC - *ic;
    if (isGuidance(copy) != NOT_GUIDANCE) {
        free(copy);
        return;
    }
    getInputAndOutputFromRow(copy, &input, &output);
    if (mightBeMcroOrLabel(input)) {
        inputLabel = isLabelNameUsedInCurrentFile((*labelArray).labels, length, input);
        if (inputLabel != NULL) {
            addLabelVelToBinaryArray(&((*binaryTable).array[currentRowBinary + 1]),
                                     inputLabel->binaryRowNumber, inputLabel->isExtern);
        }
    }
    if (mightBeMcroOrLabel(output)) {
        outputLabel = isLabelNameUsedInCurrentFile((*labelArray).labels, length, output);
        if (outputLabel != NULL) {
            addLabelVelToBinaryArray(&((*binaryTable).array[currentRowBinary + 2]),
                                     outputLabel->binaryRowNumber, outputLabel->isExtern);
        }
    }

    if (inputLabel != NULL && inputLabel->isExtern) {
        addToExternArray(pExternArray, inputLabel->name, currentRowBinary + 1 + 100, lengthExtern);
    }

    if (outputLabel != NULL && outputLabel->isExtern) {
        addToExternArray(pExternArray, outputLabel->name, currentRowBinary + 2 + 100, lengthExtern);
    }
    *ic = *ic - rowNeeded;
    freePointers(3,copy, input, output);

}

/**
 * this method get every row of the binary separate,
 * and converting each value to base 64.
 * @param binaryNum the practical row
 * @return string in base 64
 */
char *binaryToBase64(short binaryNum) {
    char base64Table[64] = {
            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
            'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
            'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
            'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
            'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7',
            '8', '9', '+', '/'
    };

    short leftNum, rightNum;
    char *base = (char *) malloc(3 * sizeof(char));
    if (base == NULL) {
        printAllocationFailure();

    }

    leftNum = binaryNum / 64;
    rightNum = binaryNum % 64;

    base[0] = base64Table[leftNum];
    base[1] = base64Table[rightNum];
    base[2] = '\0';

    return base;
}

/**
 * analyze how many shorts to add for string guidance, in binary array.
 * @param stringPart the part with the string guidance.
 * @return the length of string
 */
int analyzeStringLength(char *stringPart) {
    char *string = copyString(stringPart), space = ' ';
    int length;

    removeUntilChar(string , space);
    deleteSpaces(string);

    length = strlen(string) - 1;
    free(string);
    return length;
}

/**
 * analyze how many shorts to add for the data guidance, in binary array.
 * @param dataPart the part with the data guidance.
 * @return the amount of data in data guidance.
 */
int analyzeDataGuidance(char *dataPart) {
    int length = strlen(dataPart);
    int i, count = 0;
    for (i = 0; i < length; i++) {
        if (dataPart[i] == ',')
            count++;
    }
    return count + 1;
}
