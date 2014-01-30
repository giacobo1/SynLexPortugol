#include "SynLexPortugol.h"



int main(int argc, char const *argv[])
{

	setlocale(LC_CTYPE, "");

	if(argc == 2)
	{
		printf("Ok!");
	}
	else
	{
		printf("Erro na passagem de arquivos.\n");
		exit(1);
	}

	return EXIT_SUCCESS;
}