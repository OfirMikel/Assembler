#include "Headers/header.h"

/**
 * this file contain method helper to the spend mcro and analyze him
 */

/**
 * get mcro node list and search in the node the mcro name
 * @param row current row
 * @param head the head of mcro node list
 * @return the mcro we search or the last mcro
 */
Mcro searchMcro(Row row, McroNode *head) {
    McroNode *current = head;
    while (current != NULL && current->current.name != NULL) {
        if (strstr(row.text, current->current.name) != NULL) {
            return current->current;
        }
        current = current->next;
    }
    return current->current;
}

/**
 * check if mcro called in the node.
 * @param row the current row.
 * @param head the head of the mcro.
 * @return TRUE - 1 if is calld, else FALSE - 0
 */
int isMcroCalled(Row row, McroNode *head) {
    McroNode *current = head;
    while (current != NULL && current->current.name != NULL) {
        if (strstr(row.text, current->current.name) != NULL) {
            return TRUE;
        }
        current = current->next;
    }
    return FALSE;
}

/**
 * search if the the command endmcro inside the current row
 * @param text the current row
 * @return TRUE - 1 if the row contain endmcro, else FALSE - 0.
 */
int isMcroEnded(char *text) {
    char endMacro[] = "endmcro";
    if (strstr(text, endMacro) != NULL) {
        deleteSpaces(text);
        if (strlen(endMacro) != strlen(text)) {
            return EXTRA_TEXT;
        }
        return TRUE;
    }

    return FALSE;
}

/**
 * search if the the command mcro inside the current row
 * @param text the current row
 * @return TRUE - 1 if the row contain mcro, else FALSE - 0.
 */
int isMcroCalledInLine(char *row) {
    char *mcro = "mcro";
    char *endMcro = "endmcro";

    if (strstr(row, mcro) != NULL && strstr(row, endMcro) == NULL) {
        return TRUE;
    }
    return FALSE;
}

/**
 * check if the mcro name is not operation name and the syntax is valid
 * @param row the current row
 * @param mcro the array of mcro struct
 * @param head pointer to the node of mcroNode struct
 * @return TRUE - 1 if mcro name valid, else FALSE - 0.
 */
int isMacroNameValid(char *row, Mcro *mcro, McroNode *head) {
    int i;
    char *nameToken, *nameCopy;
    McroNode *temp = head;

    for (i = 0; i < 16; i++) {
        if (strstr(row, operationCode[i]) != NULL) {
            printError(9);
            return INVALID_MCRO;
        }
    }


    while (temp != NULL && temp->current.name != NULL) {
        if (strstr(row, temp->current.name) != NULL) {
            printError(10);
            return INVALID_MCRO;
        }
        temp = temp->next;
    }

    nameToken = strtok(row, " ");
    if (strstr(nameToken, "mcro") == NULL) {
        printError(13);
        return INVALID_MCRO;
    }


    nameToken = strtok(NULL, " ");

    nameCopy = (char *)malloc(strlen(nameToken) * sizeof(char));
    strcpy(nameCopy, nameToken);

    if(!mightBeMcroOrLabel(nameCopy)){
        free(nameCopy);
        printError(26);
        return INVALID_MCRO;
    }

    nameToken = strtok(NULL, " ");
    if(nameToken != NULL){
        free(nameCopy);
        printError(13);
        return EXTRA_TEXT;
    }

    (*mcro).name = nameCopy;
    return TRUE;
}

/**
 * analyze the row text if there mcro its spend him
 * @param rowArray the struct that contain struct rows
 * @param head the struct of mcroNode list
 * @return if was a mcro with error MCRO_ERROR - -1, else length
 */
int analyzeMcro(RowArray rowArray, McroNode **head) {
    int index = rowNumber;
    Mcro mcro;
    int length = 0, mcroEnd;
    Row *currentMcroRows = NULL;
    Row currentRow;
    int isMacroValid = isMacroNameValid(rowArray.row[index].text, (&mcro), (*head));
    if (isMacroValid != TRUE) {
        return MCRO_ERRORS;
    }

    index++;
    while ((mcroEnd = isMcroEnded(rowArray.row[index].text)) == FALSE) {
        currentRow = rowArray.row[index];
        addLineToRowArray(&currentMcroRows, currentRow, length);
        length++;
        index++;
    }

    if (mcroEnd == EXTRA_TEXT) {
        printError(13);
        return MCRO_ERRORS;
    }

    mcro.rowSpan.row = currentMcroRows;
    mcro.rowSpan.length = length;
    insertMcroNode(head, mcro);


    return length;
}

/**
 * get mcro struct and insert him to the mcroNode struct
 * @param head the mcroNode struct
 * @param mcro current mcro to add
 * @return TRUE - 1.
 */
int insertMcroNode(McroNode **head, Mcro mcro) {
    McroNode *newNode = createMcroNode(mcro);
    McroNode *current;

    if (*head == NULL) {
        *head = newNode;
    } else {
        current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    return TRUE;
}

/**
 * add mcro to mcroNode.
 * @param mcro the new mcro.
 * @return mcroNode.
 */
McroNode *createMcroNode(Mcro mcro) {
    McroNode *newNode = (McroNode *) malloc(sizeof(McroNode));
    if (newNode == NULL){
        printAllocationFailure();
        exit(1);
    }
    if (newNode != NULL) {
        newNode->current = mcro;
        newNode->next = NULL;
    }
    return newNode;
}