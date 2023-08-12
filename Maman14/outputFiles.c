#include "Headers/header.h"

/**
 * this file contain method that print to the files we create during the pass
 */

/**
 * print to file with end .ext, all the uses in extern labels
 * @param fileExt file with end .ext
 * @param array all the uses in extern labels(row, and name of extern label)
 */
void printExternToFile(FILE *fileExt, ExternArray array) {
    int i , length = array.length;
    if(array.length == 0){
        return;
    }
    for (i = 0; i < length - 1; i++) {
        fprintf(fileExt, "%s\t%d\n" , array.externs[i].name , array.externs[i].rowNumber);
    }
    fprintf(fileExt, "%s\t%d" , array.externs[i].name , array.externs[i].rowNumber);
}

/**
 * print to file with end .ent, all the labels that announce as entry
 * @param file file with end .ent
 * @param Node all the labels, including entry labels
 */
void printEntryToFile(FILE *file, LabelArray labelArray) {
    int i , length = labelArray.length , isFirst = TRUE;
    Label currentLabel;
    for (i = 0; i < length; ++i) {
        currentLabel = labelArray.labels[i];
        if(currentLabel.isEntry && !isFirst){
            fprintf(file,"\n%s\t%d" ,currentLabel.name , currentLabel.binaryRowNumber );
        }

        if(currentLabel.isEntry && isFirst){
            fprintf(file,"%s\t%d" ,currentLabel.name , currentLabel.binaryRowNumber );
            isFirst = FALSE;
        }
    }
}

/**
 * this method take the binary value of any row and translating him to ascii in base 64
 * every binary value translate to two characters in base 64(6 bits each one)
 * and than print each row base 64 to a file with the end of .ob
 * @param file the file with ending .ob
 * @param pNode the binary values of the rows
 * @param IC the operation counter
 * @param DC the data counter
 */
void printBinaryArrayToFile(FILE *file, BinaryArray binaryArray, int IC, int DC) {
    int i , length = binaryArray.length;
    short *array = binaryArray.array;
    char* textBase64;
    fprintf(file,"%d\t%d\n" ,IC , DC);
    for (i = 0; i < length - 1; i++) {
        textBase64 = binaryToBase64(array[i]);
        fprintf(file,"%s\n" ,textBase64 );
        free(textBase64);
    }
    textBase64 = binaryToBase64(array[length - 1]);
    fprintf(file,"%s" ,textBase64);

    free(textBase64);
}

/**
 * this method take every row after analyze that this particular row isn't a mcro,
 * and span the row to the file (with .am ending)
 * @param File file with .am ending
 * @param row the rows struct
 * @return TRUE - 1
 */
int spanRowToFileAm(FILE *File, Row row) {
    fprintf(File, "%s\n", row.text);
    return TRUE;
}

/**
 * this method take every row after analyze the mcro valid,
 * and span the mcro to the file (with .am ending)
 * @param File file with .am ending
 * @param currentMcro the struct of node of particular mcro
 * @return
 */
int spanMcroToFile(FILE *File, Mcro currentMcro) {
    int i;
    for (i = 0; i < currentMcro.rowSpan.length; i++) {
        fprintf(File, "%s\n", currentMcro.rowSpan.row[i].text);
    }
    return TRUE;
}

/**
 * this program get the structs of- binary, label and extern
 * and this file uses in other methods to create the files with the ending- .ext, .ent, .ob
 * @param file the current file
 * @param labelNode the struct of all labels
 * @param binaryNode the struct of the binary rows after translate
 * @param arrayExtern the struct of uses in the extern labels on each files
 */
void outputFiles(LabelArray labelArray, BinaryArray binaryArray, ExternArray arrayExtern) {
    int length = strlen(fileName);
    char *fileNameObj = malloc((length + 3) * sizeof (char));
    char *fileNameExt = malloc((length + 4) * sizeof (char));
    char *fileNameEnt = malloc((length + 4) * sizeof (char));
    FILE *object, *external, *entry;

    strcpy(fileNameEnt, fileName);
    strcpy(fileNameExt, fileName);
    strcpy(fileNameObj, fileName);
    strcat(fileNameObj, ".ob\0");
    strcat(fileNameExt, ".ext\0");
    strcat(fileNameEnt, ".ent\0");


    object = fopen(fileNameObj , "w+");
    external = fopen(fileNameExt , "w+");
    entry = fopen(fileNameEnt , "w+");


    if (object == NULL || external == NULL || entry == NULL){
        printFileOpenError();
    }

    printBinaryArrayToFile(object, binaryArray, labelArray.IC, labelArray.DC);
    printEntryToFile (entry, labelArray);
    printExternToFile (external, arrayExtern);

    freePointers(3, fileNameObj , fileNameEnt , fileNameExt);
    fclose(object);
    fclose(external);
    fclose(entry);
}