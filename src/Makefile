SynAnalizer: main.o SynLexPortugol.o
	g++ -Wall -O0 main.o SynLexPortugol.o -o SynAnalizer


SynLexPortugol.o: SynLexPortugol.h SynLexPortugol.cpp
	g++ -c SynLexPortugol.cpp

main.o: SynLexPortugol.h main.cpp
	g++ -c main.cpp


clear:
	rm *o SynAnalizer

clear_obj:
	rm *o

clear_exe:
	rm SynAnalizer

