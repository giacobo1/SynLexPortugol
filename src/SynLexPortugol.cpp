#include "SynLexPortugol.h"

void SynLexPortugol::analise(void)
{

}
void SynLexPortugol::prog(void)
{
	if(readToken() != _algo_)
	{
		printf("Erro Sintatico");
		exit(1);
	}

	if(readToken() != _id_)
	{
		printf("Erro Sintatico");
		exit(1);
	}

	if(readToken() != _pv_)
	{
		printf("Erro Sintatico");
		exit(1);
	}

	if(!Dec())
	{
		printf("Erro Sintatico");
		exit(1);
	}

	if(readToken() != _inicio_)
	{
		printf("Erro Sintatico");
		exit(1);
	}

	if(!Comand())
	{
		printf("Erro Sintatico");
		exit(1);
	}

	if(readToken() != _fim_)
	{
		printf("Erro Sintatico");
		exit(1);
	}

	printf("Analise realizada com sucesso!!!\n");
}