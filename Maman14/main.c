#include "Headers/header.h"

char *operationCode[16] = {"mov", "cmp", "add", "sub", "not", "clr", "lea", "inc", "dec", "jmp",
                           "bne", "red", "prn", "jsr", "rts", "stop"};

char *guidance[4] = {".extern", ".entry", ".string", ".data"};

int rowNumber = 0;

char *fileName;

/**
  TODO FINAL MISSIONS:
   * 1 - adding api              status:
   *   | binaryCalc - Israel      | ✔
   *   | builder -  Israel        | ✔
   *   | firstPass - Mikel        | ✔
   *   | free - Israel            | ✔
   *   | guidance - Israel        | ✔
   *   | label- Israel            | ✔
   *   | main - Mikel             | ✔
   *   | mcro - Israel
   *   | operation - Mikel        | ✔
   *   | outputFiles - Israel     | ✔
   *   | preAssembler - Mikel     | ✔
   *   | secondPass - Mikel       | ✔
   *   | stdout - Israel          | ✔
   *   | syntaxFirstPass - Mikel  | ✔
   *   | syntaxSecondPass - Mikel | ✔
   *   | utils - Mikel            | ✔
   *
   * 2 - creating enums of errors instead of calling by number of errors
   * 3 - add warning in second pass of method that called as extern but never declared as entry in other files
   * 4 - add warning in second pass of method that called as extern but never declared as entry in other files

 **/


/**
 * main method - runs the program
 * @param argc the amount of arguments
 * @param argv the array of arguments
 * @return FALSE(0)
 */
int main(int argc, char *argv[]) {
    int amountOfFiles = (argc - 1);
    sourceFiles *files = malloc((argc - 1) * sizeof(sourceFiles));
    RowArray rowArray;

    LabelArray labelArray;
    BinaryArray binaryMachineCode;
    if (argc == 1){
        printArgumentMissing();
    }

    isAllocationSuccessful(1, files);

    openFiles(argv, argc, files);

    assembler(files , &binaryMachineCode , &labelArray , &rowArray , amountOfFiles);

    printAssembledFiles(files , amountOfFiles);

    closeAndFreeFiles(files, amountOfFiles);

    return FALSE;
}



