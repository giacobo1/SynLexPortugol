#include "SynLexPortugol.h"


int main(int argc, char *argv[])
{
	if(argc == 2)
	{
		SynLexPortugol A(argv[1]);

		A.analise();		
	}
	else
	{
		printf("Erro na passagem de arquivos.\n");
		exit(1);
	}

	return EXIT_SUCCESS;
}