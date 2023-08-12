void secondPassHelper(sourceFiles *file, LabelArray *pLabels, BinaryArray *pBinary, Extern **externArray,
                      int *length, RowArray *rowArray);
void secondPass(sourceFiles *files, BinaryArray *binaryArray, LabelArray *labelArray, RowArray *rowArray);
Label* isLabelNameUsedInCurrentFile(Label *label,  int length , char* name);
int isGuidanceValidHelper(char *text);
void addNumberToBinaryArray(char *number, short *binaryArray);
void addRegisterToBinaryArray(char *Register, short *binaryArray , int shiftAmount);
void returnNumToTenBits(short *pInt);
int isSyntaxValidSecondPass(LabelArray *labelNode, char *row , int *isWarning);
int isEntryValidSecondPass(char *text, LabelArray *labelNode);
int isEntryDeclaredWithoutInitialization(LabelArray *labelNode, char *labelName);
void getInputAndOutputFromRow(char* row , char **input ,char **output);
void createExternLabels(char *label, Label **pLabel, int *length);
void addDataToBinaryTable(char *dataPart, BinaryArray *binaryTable, int *pDc, int DC);
void addDataNumberToBinaryArray(char *dataValues, short *binaryArray);
void returnNumToTwelveBits(short *num);
void addLabelToBinaryTable(char *row, BinaryArray *binaryTable, LabelArray *labelArray, int *ic, Extern **pExternArray , int *lengthExtern);
void addLabelVelToBinaryArray(short *valInBinaryArray, short number, int i);
void outputFiles(LabelArray labelArray, BinaryArray binaryArray, ExternArray arrayExtern);
int isLabelExternButDeclaredInFile(LabelArray labelArray, char *name , int* warnings);
int isEntryDeclaredAlsoAsExtern(LabelArray *labelNode, char *name);
char *binaryToBase64(short binaryNum);
void validateRow(Row row, BinaryArray *pBinary, LabelArray *pLabel, sourceFiles *file, int *currentDC,
                 int *currentIC, Extern **pExternArray, int *length);
int isExternValidSecondPass(char *row, LabelArray *labelNode , int *isWarnings);
void addStringToBinaryTable(char *stringPart, BinaryArray *binaryTable, int *pDc, int DC);
void freeLabelsName(LabelArray *pArray);