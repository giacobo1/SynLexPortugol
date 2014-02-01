// TODO: mais além, arrumar tratamento de erros....
// TODO: verificar no manual todos so tipos possiveis de matrizes

// aparentemento o e0 ( e, logo, as exps) sempre começam com o token ja lido...

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
	
	if(!comand())
	{
		printf("Erro Sintatico\n");
		exit(1);
	}

	if(currentToken != _fim_)
	{
		printf("Erro Sintatico\n");
		exit(1);
	}

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


bool SynLexPortugol::comand(void)
{
	printf("comand\n");
	currentToken = readToken();

	if(currentToken == _id_)
	{
		if(!lValue())
		{
			printf("Erro Sintatico\n");
			exit(1);
		}
		// talvez o lvalue retorne sem lser o proximo token
		currentToken = readToken();
		if(currentToken == _pv_)
		{
			return comand();
		}
		else
			return false;
	}
	else if(currentToken == _print_)
	{
		currentToken = readToken();

		if(currentToken == _ap_)
		{
			if(!args())
			{
				printf("Erro Sintatico\n");
				exit(1);
			}
		}
		else
			return false;
		// talvez saindo do args n leia o nextoken.. mas axo q n
		if(currentToken == _fp_)
		{
			currentToken = readToken();
			if(currentToken == _pv_)
			{
				return comand();
			}
			else
				return false;

		}
	}
	else if(currentToken == _enquanto_)
	{
		// se der godo posso ler o token aqui
		if(!e0())
		{
			printf("Erro Sintatico\n");
			exit(1);
		}

		// verificar tb se dps de sair de e0 tem q ler o nextoken..
		if(currentToken == _faca_)
		{
			if(!comand())
			{
				printf("Erro Sintatico\n");
				exit(1);
			}

			if(currentToken == _fimenquanto_)
			{
				return comand();
			}
			else
				return false;

		}

	}
	else if(currentToken == _se_)
	{
		// se der godo posso ler o token aqui
		if(!e0())
		{
			printf("Erro Sintatico\n");
			exit(1);
		}

		if(currentToken == _entao_)
		{
			return comand();
		}
		else
			return false;

		if(!Else())
		{
			printf("Erro Sintatico\n");
			exit(1);
		}

		if(currentToken == _fimse_)
		{
			return comand();
		}
		else
			return false;
	}
	else 
		return true;

	return false;
}
bool SynLexPortugol::lValue(void)
{

	printf("lValue\n");

	currentToken = readToken();

	if(currentToken == _ac_)
	{
		if(!e0())
		{
			printf("Erro Sintatico\n");
			exit(1);
		}

		if(currentToken == _fc_)
		{
			return lValue();
		}
		else
			return false;
	}
	else if(currentToken == _atrib_)
	{
		return rValue();
	}
	
	return false;
	

}

bool SynLexPortugol::rValue(void)
{

	printf("rValue\n");
	currentToken = readToken();

	if(currentToken == _read_)
	{
		currentToken = readToken();

		if(currentToken == _ap_)
		{
			currentToken = readToken();

			if(currentToken == _fp_)return true;
			else
				return false;
		}
		else 
			return false;
	}
	// cuidar aqui aqui ja leu um token...
	else
		return e0();	
}
bool SynLexPortugol::args(void)
{
	if(!e0())
	{
		printf("Erro Sintatico\n");
		exit(1);
	}
	else
		return argList();

	return false;

}
bool SynLexPortugol::argList(void)
{
	currentToken = readToken();

	if(currentToken == _v_)
	{
		return args();
	}
	else
		return true;

	return false;

}
bool SynLexPortugol::Else(void)
{

}


bool SynLexPortugol::e0(void)
{

}