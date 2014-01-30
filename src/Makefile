SynAnalizer: main.o SynLexPortugol.o LexPortugol.o
	g++ -Wall -O0 main.o SynLexPortugol.o LexPortugol.o -o SynAnalizer

LexPortugol.o: LexPortugol.h LexPortugol.cpp
	g++ -c LexPortugol.cpp


SynLexPortugol.o: SynLexPortugol.h SynLexPortugol.cpp LexPortugol.h 
	g++ -c SynLexPortugol.cpp

main.o: SynLexPortugol.h main.cpp
	g++ -c main.cpp


clear:
	rm *o SynAnalizer teste

clear_obj:
	rm *o

clear_exe:
	rm SynAnalizer

clear_tests:
	rm teste

