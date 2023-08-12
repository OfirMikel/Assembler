#include "Headers/header.h"

/**
 * this file contain function with output to the stdout
 */

/**
 * this function print errors output to the user
 * @param errorValue the number of error in the array error.
 */
void printError(int errorValue){
    char *errors[31] = {"line with More Then 80 characters", "Method does not exist", "Macro has been used before declared",
                        "Operand error", "Label does not exist", "Register does not exist", "Label already exist",
                        "Macro already exist", "No available memory allocation", "Macro can't have a name of command",
                        "Macro can't have a name that use for other mcro", "There isn't file with the name:",
                        "two different command must be new line", "external text in mcro declare", "Label name isn't valid",
                        "Invalid input", "Invalid output", "Invalid string declaration", "Invalid data declaration",
                        "Invalid data value bigger then 255", "Invalid data value lower then -256",
                        "Invalid Entry declaration", "Invalid Extern declaration",
                        "Label entry declared but label didn't initialized", "Invalid Label",
                        "Label called as Extern but declared in the same file" ,"Macro can't have a name with special character"
            , "Extra Operand" , "Label declared as Extern and Entry", "invalid guidance declaration" ,"Extra argument"};

    printRedError();
    printf("File:%s.txt Row:%d " COLOR_RED "%s\n" COLOR_RESET, fileName, rowNumber + 1, errors[errorValue]);
}

/**
 * this method print warning output to the user
 * @param warningValue the number of warning
 */
void printWarning(int warningValue){
    char *warnings[10] = {"Extern declared more then once", "data without value"
            , "Entry inside a label declaration"  , "Extern inside a label declaration" ,"Entry declared more then once"};
    printYellowWarning();
    printf("File:%s.txt Row:%d " COLOR_YELLOW "%s\n" COLOR_RESET, fileName, rowNumber + 1, warnings[warningValue]);
}

/**
 * if allocation for pointer fail this method print error and exit the code.
 */
void printAllocationFailure(){
    printf(COLOR_BLUE "--- ALLOCATION FAILURE TRY AGAIN ---\n" COLOR_RESET);
    exit(1);
}

/**
 * if the pointer to file is NULL,
 * its mean that open file fail
 * this method print error and exit the code.
 */
void printFileOpenError(){
    printf(COLOR_BLUE "--- CAN'T OPEN FILE ---\n" COLOR_RESET);
    exit(1);
}

/**
 * if the user didn't put any argument in the command run of the program
 * its mean that any file doesn't input
 * this print error and exit the code.
 */
void printArgumentMissing(){
    printf(COLOR_YELLOW "--- NO ARGUMENT ENTERED ---\n" COLOR_RESET);
    exit (1);
}

/**
 * if file input but with name incorrect / the name doesn't exist
 * this will print error
 * @param name
 */
void printFileMissing(char* name){
    printRedError();
    printf(COLOR_YELLOW "There isn't file with the name: %s.as \n" COLOR_RESET , name);
}

/**
 * this change the message of error to red color
 */
void printRedError(){
    printf(COLOR_RED "-- ERROR -- " COLOR_RESET);
}

/**
 * this change the message of warning to yellow color
 */
void printYellowWarning(){
    printf(COLOR_YELLOW "-- WARNING -- " COLOR_RESET);
}

/**
 * if there isn't errors in the file this method print that the files create success
 * @param name the file name
 */
void printFileIsValid(char *name){
    printf( "--" COLOR_GREEN " FILE ASSEMBLED " COLOR_RESET "THE FILES: %s .ob / .ext / .ent " COLOR_GREEN " CREATED SUCCESSFULLY " COLOR_RESET "-- \n"  , name);
}

/**
 * if there was errors in the file this method print that the files create not success
 * @param name the file name
 */
void printFileIsNotValid(char *name){
    printf( "--" COLOR_RED " DUE TO ERRORS" COLOR_RESET " THE FILES: %s .ob / .ext / .ent " COLOR_RED " WASN'T CREATED " COLOR_RESET "-- \n"  , name);
}

/**
 *  if there was only warnings in the file this method print that the files create
 * @param name the file name
 */
void printFileHasWarnings(char *name){
    printf( "--" COLOR_YELLOW " FILE ASSEMBLED BUT HAVE WARNINGS " COLOR_RESET "THE FILES: %s .ob / .ext / .ent " COLOR_YELLOW " CREATED " COLOR_RESET "-- \n"  , name);

}

/**
 * check if file is without error and if so print that the files create successful
 * @param pFiles the struct of files
 * @param length the length of the struct.
 */
void printAssembledFiles(sourceFiles *pFiles, int length) {
    int i;
    printf("\n\n");
    for (i = 0; i < length; i++) {
        if(pFiles[i].isValid && pFiles[i].isWarnings){
            printFileHasWarnings(pFiles[i].name);
            continue;
        }
        if(pFiles[i].isValid){
            printFileIsValid(pFiles[i].name);
            continue;
        }
        printFileIsNotValid(pFiles[i].name);
    }
    printf("\n");
}