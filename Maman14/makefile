main:ObjectFiles/main.o ObjectFiles/preAssembler.o ObjectFiles/builder.o ObjectFiles/firstPass.o ObjectFiles/free.o ObjectFiles/binaryCalc.o ObjectFiles/guidance.o ObjectFiles/label.o ObjectFiles/mcro.o ObjectFiles/syntaxFirstPass.o ObjectFiles/utils.o ObjectFiles/secondPass.o ObjectFiles/operation.o ObjectFiles/syntaxSecondPass.o ObjectFiles/stdout.o ObjectFiles/outputFiles.o ObjectFiles/assembler.o
	gcc -g -Wall -ansi -pedantic ObjectFiles/main.o ObjectFiles/secondPass.o ObjectFiles/operation.o ObjectFiles/stdout.o ObjectFiles/outputFiles.o ObjectFiles/preAssembler.o ObjectFiles/builder.o ObjectFiles/firstPass.o ObjectFiles/free.o ObjectFiles/binaryCalc.o ObjectFiles/guidance.o ObjectFiles/label.o ObjectFiles/mcro.o ObjectFiles/syntaxFirstPass.o ObjectFiles/utils.o ObjectFiles/assembler.o ObjectFiles/syntaxSecondPass.o -o main -lm
ObjectFiles/main.o:main.c Headers/header.h
	gcc -c -Wall -ansi -pedantic main.c -o ObjectFiles/main.o -lm

ObjectFiles/preAssembler.o: preAssembler.c Headers/header.h
	gcc -c -Wall -ansi -pedantic preAssembler.c -o ObjectFiles/preAssembler.o -lm

ObjectFiles/builder.o:builder.c Headers/header.h
	gcc -c -Wall -ansi -pedantic builder.c -o ObjectFiles/builder.o -lm

ObjectFiles/firstPass.o:firstPass.c Headers/header.h
	gcc -c -Wall -ansi -pedantic firstPass.c -o ObjectFiles/firstPass.o -lm

ObjectFiles/binaryCalc.o:binaryCalc.c Headers/header.h
	gcc -c -Wall -ansi -pedantic binaryCalc.c -o ObjectFiles/binaryCalc.o -lm

ObjectFiles/guidance.o:guidance.c Headers/header.h
	gcc -c -Wall -ansi -pedantic guidance.c -o ObjectFiles/guidance.o -lm


ObjectFiles/label.o:label.c Headers/header.h
	gcc -c -Wall -ansi -pedantic label.c -o ObjectFiles/label.o -lm

ObjectFiles/mcro.o:mcro.c Headers/header.h
	gcc -c -Wall -ansi -pedantic mcro.c -o ObjectFiles/mcro.o -lm

ObjectFiles/syntaxFirstPass.o:syntaxFirstPass.c Headers/header.h
	gcc -c -Wall -ansi -pedantic syntaxFirstPass.c -o ObjectFiles/syntaxFirstPass.o -lm

ObjectFiles/utils.o:utils.c Headers/header.h
	gcc -c -Wall -ansi -pedantic utils.c -o ObjectFiles/utils.o -lm

ObjectFiles/secondPass.o:secondPass.c Headers/header.h
	gcc -c -Wall -ansi -pedantic secondPass.c -o ObjectFiles/secondPass.o -lm

ObjectFiles/operation.o:operation.c Headers/header.h
	gcc -c -Wall -ansi -pedantic operation.c -o ObjectFiles/operation.o -lm
ObjectFiles/syntaxSecondPass.o:syntaxSecondPass.c Headers/header.h
	gcc -c -Wall -ansi -pedantic syntaxSecondPass.c -o ObjectFiles/syntaxSecondPass.o -lm

ObjectFiles/free.o:free.c Headers/header.h
	gcc -c -Wall -ansi -pedantic free.c -o ObjectFiles/free.o -lm

ObjectFiles/outputFiles.o:outputFiles.c Headers/header.h
	gcc -c -Wall -ansi -pedantic outputFiles.c -o ObjectFiles/outputFiles.o -lm

ObjectFiles/stdout.o:stdout.c Headers/header.h
	gcc -c -Wall -ansi -pedantic stdout.c -o ObjectFiles/stdout.o -lm

ObjectFiles/assembler.o:assembler.c Headers/header.h
	gcc -c -Wall -ansi -pedantic assembler.c -o ObjectFiles/assembler.o -lm

