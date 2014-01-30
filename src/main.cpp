#include "SynLexPortugol.h"


int main(int argc, char *argv[])
{

	setlocale(LC_CTYPE, "");

	if(argc == 2)
	{
		LexPortugol lex(argv[1]);

		printf("%d\n ",lex.readToken() );
		printf("%d\n ",lex.readToken() );
		printf("%d\n ",lex.readToken() );
		printf("%d\n ",lex.readToken() );
		printf("%d\n ",lex.readToken() );
		printf("%d\n ",lex.readToken() );
		printf("%d\n ",lex.readToken() );
		printf("%d\n ",lex.readToken() );
		printf("%d\n ",lex.readToken() );
		printf("%d\n ",lex.readToken() );
		//if(x != _error_)printf("%d ",x );
		
	}
	else
	{
		printf("Erro na passagem de arquivos.\n");
		exit(1);
	}

	return EXIT_SUCCESS;
}