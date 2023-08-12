extern char* operationCode[16];
extern char* guidance[4];
extern int rowNumber;
extern char* fileName;

#define COLOR_RED     "\x1b[31m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_RESET   "\x1b[0m"

#define INVALID_MCRO -1
#define EXTRA_TEXT -1
#define LINE_MAX_LEN  80
#define LABEL_MAX_LEN 31

#define MIN_VAL -256
#define MAX_VAL 255
#define MAX_VAL_DATA 511
#define MIN_VAL_DATA -512

#define BASE_10_BITES 1023
#define BASE_12_BITES 4095

#define MCRO_ERRORS -1
#define LABEL_ERROR -1
#define UNDEFINED_OPERATION -1
#define INVALID_NUMBER -1000
#define NOT_GUIDANCE -1
#define EXTERN 0
#define ENTRY 1
#define DATA 3
#define STRING 2

#define MOV 0
#define CMP 1
#define ADD 2
#define SUB 3
#define NOT 4
#define CLR 5
#define LEA 6
#define INC 7
#define DEC 8
#define JMP 9
#define BNE 10
#define RED 11
#define PRN 12
#define JSR 13
#define RTS 14
#define STOP 15

#define TRUE  1
#define FALSE 0

#define DESTINATION_LOCATION 2
#define OPCODE_LOCATION 5
#define ORIGIN_LOCATION 9




typedef struct files{
  char *name;
  FILE *fileBeforeMcro;
  FILE *fileAfterMcro;
  int isValid;
  int isWarnings;
  int isMcroValid;
} sourceFiles;

typedef struct Row{
    char *text;
} Row;

typedef struct RowArray{
    Row *row;
    int length;
} RowArray;

typedef struct mcro{
    char *name;
    RowArray rowSpan;
} Mcro;

typedef struct McroNode {
    Mcro current;
    struct McroNode* next;
} McroNode;

typedef struct Label{
    char *name;
    int isEntry;
    int isExtern;
    short binaryRowNumber;
} Label;


typedef struct LabelArray{
    Label *labels;
    int length;
    int IC;
    int DC;
} LabelArray;

typedef struct Extern{
    char* name;
    short rowNumber;
} Extern;

typedef struct ExternArray{
    Extern *externs;
    int length;
} ExternArray;


typedef struct BinaryArray{
    short* array;
    int length;
} BinaryArray;
