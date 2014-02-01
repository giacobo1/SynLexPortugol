// TODO: mais além, arrumar tratamento de erros....
// TODO: verificar no manual todos so tipos possiveis de matrizes

#include "SynLexPortugol.h"

void SynLexPortugol::analise(void)
{

}
void SynLexPortugol::prog(void)
{
	
	if(readToken() != _algo_)
	{
		printf("Erro Sintatico\n");
		exit(1);
	}

	if(readToken() != _id_)
	{
		printf("Erro Sintatico\n");
		exit(1);
	}

	if(readToken() != _pv_)
	{
		printf("Erro Sintatico\n");
		exit(1);
	}


	if(!dec())
	{
		printf("Erro Sintatico\n");
		exit(1);
	}


	//printf("%d\n",currentToken );
	
	if(currentToken != _inicio_)
	{
		printf("Erro Sintatico\n");
		exit(1);
	}


	/*
	
	if(!comand())
	{
		printf("Erro Sintatico\n");
		exit(1);
	}

	if(currentToken != _fim_)
	{
		printf("Erro Sintatico\n");
		exit(1);
	}*/

	printf("Analise realizada com sucesso!!!\n");
}


bool SynLexPortugol::dec(void)
{
	printf("dec\n" );
	currentToken = readToken();

	if(currentToken == _vars_)
	{
		currentToken = readToken();

		if(currentToken == _id_)
		{
			if(!idList())
			{
				printf("Erro Sintatico\n");
				exit(1);
			}
		}

		if(currentToken == _pp_)
		{
			if(!tipo())
			{
				printf("Erro Sintatico\n");
				exit(1);
			}
		}

		if(!decList())
		{
			printf("Erro Sintatico\n");
			exit(1);
		}

		if(currentToken == _fimvar_)
		{
			currentToken = readToken();
			return true;
		}	
		else
			return false;
	}
	else
		return true;

	return false; 
}
bool SynLexPortugol::decList(void)
{
	printf("decList\n" );
	currentToken = readToken();

	if(currentToken == _id_)
	{
		if(!idList())
		{
			printf("Erro Sintatico\n");
			exit(1);
		}

		if(currentToken == _pp_)
		{
			if(!tipo())
			{
				printf("Erro Sintatico\n");
				exit(1);
			}
		}

		return decList();
	}
	else
		return true;

	return false;


}
bool SynLexPortugol::idList(void)
{
	printf("idList\n" );
	currentToken = readToken();

	if(currentToken == _v_)
	{
		currentToken = readToken();

		if(currentToken == _id_)
		
		return idList();
	}
	else
		return true;

	return false;

}	
bool SynLexPortugol::tipo(void)
{
	printf("tipo\n" );
	currentToken = readToken();

	if(currentToken == _int_)
	{
		currentToken = readToken();

		if(currentToken == _pv_)
			return true;
		else
			return false;
	}
	else if(currentToken == _real_)
	{
		currentToken = readToken();

		if(currentToken == _pv_)
			return true;
		else
			return false;
	}
	else if(currentToken == _char_)
	{
		currentToken = readToken();

		if(currentToken == _pv_)
			return true;
		else
			return false;
	}
	else if(currentToken == _string_)
	{
		currentToken = readToken();

		if(currentToken == _pv_)
			return true;
		else
			return false;
	}
	else if(currentToken == _bool_)
	{
		currentToken = readToken();

		if(currentToken == _pv_)
			return true;
		else
			return false;
	}
	else if(currentToken == _dimension_)
	{
		return compTipo();		
	}

	return false;
}	
bool SynLexPortugol::compTipo(void)
{
	printf("compTipo\n" );
	currentToken = readToken();

	if(currentToken == _intcomp_)
	{
		currentToken = readToken();

		if(currentToken == _pv_)
			return true;
		else
			return false;
	}
	else if(currentToken == _realcomp_)
	{
		currentToken = readToken();

		if(currentToken == _pv_)
			return true;
		else
			return false;
	}
	else if(currentToken == _stringcomp_)
	{
		currentToken = readToken();

		if(currentToken == _pv_)
			return true;
		else
			return false;
	}
	else if(currentToken == _boolcomp_)
	{
		currentToken = readToken();

		if(currentToken == _pv_)
			return true;
		else
			return false;
	}	
}