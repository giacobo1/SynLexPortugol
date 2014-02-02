// TODO: mais além, arrumar tratamento de erros....
// TODO: verificar no manual todos so tipos possiveis de matrizes

// TODO: problema com contagem de colunas.. axo q qnd reconhece o token no sintatico tem
// q zerar 
// TODO: arrumar uneg.. e testar mais

// TODO: nao ta pegando alguns erros lexicos.. nao ta pegando caracter estranho no meio de IDS


#include "SynLexPortugol.h"

void SynLexPortugol::analise(void)
{
	prog();
}
void SynLexPortugol::prog(void)
{
	
	if(readToken() != _algo_)
	{
		printf("Erro Sintatico na linha [%d] coluna [%d]:: Token - <algo> faltando.\n",lines,columns);
		exit(1);
	}

	
	if(readToken() != _id_)
	{
		printf("Erro Sintatico na linha [%d] coluna [%d]:: Token - <id> faltando.\n",lines,columns);
		exit(1);
	}

	
	if(readToken() != _pv_)
	{
		printf("Erro Sintatico na linha [%d] coluna [%d]:: Token - <pv> faltando.\n",lines,columns);
		exit(1);
	}

	
	if(!dec())
	{
		//printf("Erro Sintatico na linha [%d] coluna [%d].\n",lines,columns);
		exit(1);
	}

	
	if(currentToken != _inicio_)
	{
		printf("Erro Sintatico na linha [%d] coluna [%d]:: Token - <inicio> faltando.\n",lines,columns);
		exit(1);
	}	
	
	
	if(!comand())
	{
		printf("Erro Sintatico na linha [%d] coluna [%d].\n",lines,columns);
		exit(1);
	}

	
	if(currentToken != _fim_)
	{
		printf("Erro Sintatico na linha [%d] coluna [%d]:: Token - <fim> faltando.\n",lines,columns);
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
				printf("Erro Sintatico na linha [%d] coluna [%d].\n",lines,columns);
				exit(1);
			}
		}
		else
		{
			printf("Erro Sintatico na linha [%d] coluna [%d]:: Token <id> faltando.\n",lines,columns);
			exit(1);
		}

		if(currentToken == _pp_)
		{
			if(!tipo())
			{
				printf("Erro Sintatico na linha [%d] coluna [%d]:: Token tipo incorreto.\n",lines,columns);
				exit(1);
			}
		}
		else
		{
			printf("Erro Sintatico na linha [%d] coluna [%d]:: Token <pp> faltando.\n",lines,columns);
			exit(1);
		}

		if(!decList())
		{
			printf("Erro Sintatico na linha [%d] coluna [%d].\n",lines,columns);
			exit(1);
		}

		if(currentToken == _fimvar_)
		{
			currentToken = readToken();
			return true;
		}	
		else
		{
			printf("Erro Sintatico na linha [%d] coluna [%d]:: Token <fimvar> faltando.\n",lines,columns);	
			exit(1);
		}	
			
	}
	else
		return true;
 
}
bool SynLexPortugol::decList(void)
{
	printf("decList\n" );
	currentToken = readToken();
	
	if(currentToken == _id_)
	{
		if(!idList())
		{
			printf("Erro Sintatico na linha [%d] coluna [%d].\n",lines,columns);
			exit(1);
		}
		if(currentToken == _pp_)
		{
			if(!tipo())
			{
				printf("Erro Sintatico na linha [%d] coluna [%d]:: Token tipo incorreto.\n",lines,columns);
				exit(1);
			}
		}
		return decList();
	}
	else
		return true;
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
		else
		{
			printf("Erro Sintatico na linha [%d] coluna [%d]:: Token <id> faltando.\n",lines,columns);
			exit(1);
		}
	}
	else
		return true;
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
		{
			printf("Erro Sintatico na linha [%d] coluna [%d]:: Token <pv> faltando.\n",lines,columns);
			exit(1);
		}
	}
	else if(currentToken == _real_)
	{
		currentToken = readToken();
		if(currentToken == _pv_)
			return true;
		else
		{
			printf("Erro Sintatico na linha [%d] coluna [%d]:: Token <pv> faltando.\n",lines,columns);
			exit(1);
		}
	}
	else if(currentToken == _char_)
	{
		currentToken = readToken();
		if(currentToken == _pv_)
			return true;
		else
		{
			printf("Erro Sintatico na linha [%d] coluna [%d]:: Token <pv> faltando.\n",lines,columns);
			exit(1);
		}
	}
	else if(currentToken == _string_)
	{
		currentToken = readToken();
		if(currentToken == _pv_)
			return true;
		else
		{
			printf("Erro Sintatico na linha [%d] coluna [%d]:: Token <pv> faltando.\n",lines,columns);
			exit(1);
		}
	}
	else if(currentToken == _bool_)
	{
		currentToken = readToken();
		if(currentToken == _pv_)
			return true;
		else
		{
			printf("Erro Sintatico na linha [%d] coluna [%d]:: Token <pv> faltando.\n",lines,columns);
			exit(1);
		}
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
		{
			printf("Erro Sintatico na linha [%d] coluna [%d]:: Token <pv> faltando.\n",lines,columns);
			exit(1);
		}
	}
	else if(currentToken == _realcomp_)
	{
		currentToken = readToken();
		if(currentToken == _pv_)
			return true;
		else
		{
			printf("Erro Sintatico na linha [%d] coluna [%d]:: Token <pv> faltando.\n",lines,columns);
			exit(1);
		}
	}
	else if(currentToken == _stringcomp_)
	{
		currentToken = readToken();
		if(currentToken == _pv_)
			return true;
		else
		{
			printf("Erro Sintatico na linha [%d] coluna [%d]:: Token <pv> faltando.\n",lines,columns);
			exit(1);
		}
	}
	else if(currentToken == _boolcomp_)
	{
		currentToken = readToken();
		if(currentToken == _pv_)
			return true;
		else
		{
			printf("Erro Sintatico na linha [%d] coluna [%d]:: Token <pv> faltando.\n",lines,columns);
			exit(1);
		}
	}	

	return false;
}


bool SynLexPortugol::comand(void)
{
	printf("comand\n");
	currentToken = readToken();
	
	if(currentToken == _id_)
	{
		if(!lValue())
		{
			printf("Erro Sintatico na linha [%d] coluna [%d].\n",lines,columns);
			exit(1);
		}
		
		printf("%d\n",currentToken );

		if(currentToken == _pv_)
		{
			return comand();
		}
		else
		{
			printf("Erro Sintatico na linha [%d] coluna [%d]:: Token <pv> faltando.\n",lines,columns);
			exit(1);
		}
	}
	else if(currentToken == _print_)
	{
		currentToken = readToken();
		
		if(currentToken == _ap_)
		{			
			if(!args())
			{
				printf("Erro Sintatico na linha [%d] coluna [%d].\n",lines,columns);
				exit(1);
			}
		}
		else
		{
			printf("Erro Sintatico na linha [%d] coluna [%d]:: Token <ap> faltando.\n",lines,columns);
			exit(1);
		}

		if(currentToken == _fp_)
		{
			currentToken = readToken();
			if(currentToken == _pv_)
			{
				return comand();
			}
			else
			{
				printf("Erro Sintatico na linha [%d] coluna [%d]:: Token <pv> faltando.\n",lines,columns);
				exit(1);
			}
		}
		else
		{
			printf("Erro Sintatico na linha [%d] coluna [%d]:: Token <fp> faltando.\n",lines,columns);
			exit(1);
		}
	}
	else if(currentToken == _enquanto_)
	{
		currentToken = readToken();
		if(!e0())
		{
			printf("Erro Sintatico na linha [%d] coluna [%d]:: Expressao invalida.\n",lines,columns);
			exit(1);
		}

		if(currentToken == _faca_)
		{
			if(!comand())
			{
				printf("Erro Sintatico na linha [%d] coluna [%d].\n",lines,columns);
				exit(1);
			}

			if(currentToken == _fimenquanto_)
			{
				return comand();
			}
			else
			{
				printf("Erro Sintatico na linha [%d] coluna [%d]:: Token <fimenquanto> faltando.\n",lines,columns);
				exit(1);
			}
		}
		else
		{
			printf("Erro Sintatico na linha [%d] coluna [%d]:: Token <faca> faltando.\n",lines,columns);
			exit(1);
		}

	}
	else if(currentToken == _se_)
	{
		currentToken = readToken();
		if(!e0())
		{
			printf("Erro Sintatico na linha [%d] coluna [%d]:: Expressao invalida\n",lines,columns);
			exit(1);
		}

		if(currentToken == _entao_)
		{
			if(!comand())
			{
				printf("Erro Sintatico na linha [%d] coluna [%d].\n",lines,columns);
				exit(1);
			}

			if(!Else())
			{
				printf("Erro Sintatico na linha [%d] coluna [%d].\n",lines,columns);
				exit(1);
			}
		}
		else
		{
			printf("Erro Sintatico na linha [%d] coluna [%d]:: Token <entao> faltando.\n",lines,columns);
			exit(1);
		}		
		

		if(currentToken == _fimse_)
		{
			printf("li um fimse\n");
			return comand();
		}
		else
		{
			printf("Erro Sintatico na linha [%d] coluna [%d]:: Token <fimse> faltando.\n",lines,columns);
			exit(1);
		}
	}
	else 
		return true;
}
bool SynLexPortugol::lValue(void)
{

	printf("lValue\n");

	currentToken = readToken();
	
	if(currentToken == _ac_)
	{
		currentToken = readToken();
		if(!e0())
		{
			printf("Erro Sintatico na linha [%d] coluna [%d]:: Expressao invalida\n",lines,columns);
			exit(1);
		}

		if(currentToken == _fc_)
		{
			return lValue();
		}
		else
		{
			printf("Erro Sintatico na linha [%d] coluna [%d]:: Token <fc> faltando.\n",lines,columns);
			exit(1);
		}
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
			if(currentToken == _fp_)
			{
				currentToken = readToken();
				return true;
			}
			else
			{
				printf("Erro Sintatico na linha [%d] coluna [%d]:: Token <fp> faltando.\n",lines,columns);
				exit(1);
			}
		}
		else
		{
			printf("Erro Sintatico na linha [%d] coluna [%d]:: Token <ap> faltando.\n",lines,columns);
			exit(1);
		}
	}
	else
		return e0();	
}

bool SynLexPortugol::args(void)
{
	currentToken = readToken();
	if(!e0())
	{
		printf("Erro Sintatico na linha [%d] coluna [%d]:: Expressao invalida\n",lines,columns);
		exit(1);
	}
	return argList();
}
bool SynLexPortugol::argList(void)
{
	if(currentToken == _v_)
	{
		return args();
	}
	else
		return true;

}
bool SynLexPortugol::Else(void)
{
	printf("to no else b1tch\n");

	if(currentToken == _senao_)
	{
		return comand();
	}
	else
		return true;
}

// ============================

bool SynLexPortugol::e0(void)
{
	printf("e0 - %d\n",currentToken );
	if(!e1())
	{
		printf("Erro Sintatico na linha [%d] coluna [%d]:: Expressao invalida\n",lines,columns);
		exit(1);
	}
	
	return x();
}

bool SynLexPortugol::x(void)
{
	
	if(currentToken == _eq_)
	{
		printf("Entrei no operador igual.\n");
		currentToken = readToken();
		if(!e1())
		{
			printf("Erro Sintatico na linha [%d] coluna [%d]:: Expressao invalida\n",lines,columns);
			exit(1);
		}
		else return x();
	}
	else if(currentToken == _neq_)
	{

		printf("Entrei no operador diferente.\n");
		currentToken = readToken();
		if(!e1())
		{
			printf("Erro Sintatico na linha [%d] coluna [%d].\n",lines,columns);
			exit(1);
		}
		else return x();
		
	}
	else if(currentToken == _lt_)
	{

		printf("Entrei no operador menor que.\n");
		currentToken = readToken();
		if(!e1())
		{
			printf("Erro Sintatico na linha [%d] coluna [%d]:: Expressao invalida\n",lines,columns);
			exit(1);
		}
		else return x();
		
	}
	else if(currentToken == _gt_)
	{

		printf("Entrei no operador maior que.\n");
		currentToken = readToken();
		if(!e1())
		{
			printf("Erro Sintatico na linha [%d] coluna [%d]:: Expressao invalida\n",lines,columns);
			exit(1);
		}
		else return x();		
	}
	else if(currentToken == _leq_)
	{

		printf("Entrei no operador menor igual.\n");
		currentToken = readToken();
		if(!e1())
		{
			printf("Erro Sintatico na linha [%d] coluna [%d]:: Expressao invalida\n",lines,columns);
			exit(1);
		}
		else return x();		
	}
	else if(currentToken == _geq_)
	{

		printf("Entrei no operador maior igual.\n");
		currentToken = readToken();
		if(!e1())
		{
			printf("Erro Sintatico na linha [%d] coluna [%d]:: Expressao invalida\n",lines,columns);
			exit(1);
		}
		else return x();
		
	}
	else 
		return true;
}

bool SynLexPortugol::e1(void)
{
	printf("e1 - %d\n",currentToken );
	if(!e2())
	{
		printf("Erro Sintatico na linha [%d] coluna [%d]:: Expressao invalida\n",lines,columns);
		exit(1);
	}
	

	return y();
}

bool SynLexPortugol::y(void)
{
	if(currentToken == _Elogic_)
	{

		printf("Entrei no operador AND logico.\n");
		currentToken = readToken();
		
		if(!e2())
		{			
			printf("Erro Sintatico na linha [%d] coluna [%d]:: Expressao invalida\n",lines,columns);
			exit(1);
		}
		else return y();		
	}
	else if(currentToken == _OUlogic_)
	{

		printf("Entrei no operador OU logico.\n");
		currentToken = readToken();
		
		if(!e2())
		{
			printf("Erro Sintatico na linha [%d] coluna [%d]:: Expressao invalida\n",lines,columns);
			exit(1);
		}
		else return y();		
	}
	else return true;
}

// axo q o uneg vem aqui..
bool SynLexPortugol::e2(void)
{
	printf("e2 - %d\n",currentToken );
	if(currentToken == _NOTlogic_)
	{
		printf("Entrei no operador NOT logico.\n");
		currentToken = readToken();
		
		return e3();
	}
	else
		return e3();

}

bool SynLexPortugol::e3(void)
{
	printf("e3 - %d\n",currentToken );
	if(!e4())
	{
		printf("Erro Sintatico na linha [%d] coluna [%d]:: Expressao invalida\n",lines,columns);
		exit(1);
	}


	return w();
}


bool SynLexPortugol::w(void)
{
	if(currentToken == _sum_)
	{

		printf("Entrei no operador soma.\n");
		currentToken = readToken();
		
		if(!e4())
		{
			printf("Erro Sintatico na linha [%d] coluna [%d]:: Expressao invalida\n",lines,columns);
			exit(1);
		}
		else return w();		
		
	}
	else if(currentToken == _sub_)
	{
		printf("Entrei no operador subtracao.\n");
		currentToken = readToken();
		
		if(!e4())
		{
			printf("Erro Sintatico na linha [%d] coluna [%d]:: Expressao invalida\n",lines,columns);
			exit(1);
		}
		else return w();		
	}
	else return true;
}

bool SynLexPortugol::e4(void)
{
	printf("e4 - %d\n",currentToken );
	if(!e5())
	{
		printf("Erro Sintatico na linha [%d] coluna [%d]:: Expressao invalida\n",lines,columns);
		exit(1);
	}
	
	return z();
}

bool SynLexPortugol::z(void)
{
	if(currentToken == _mult_)
	{
		printf("Entrei no operador multiplicacao.\n");
		currentToken = readToken();
		if(!e5())
		{
			printf("Erro Sintatico na linha [%d] coluna [%d]:: Expressao invalida\n",lines,columns);
			exit(1);
		}
		else return z();
	}
	else if(currentToken == _mod_)
	{
		printf("Entrei no operador modulo\n");
		currentToken = readToken();
		if(!e5())
		{
			printf("Erro Sintatico na linha [%d] coluna [%d]:: Expressao invalida\n",lines,columns);
			exit(1);
		}
		else return z();		
	}
	else if(currentToken == _div_)
	{
		printf("Entrei no operador divisao.\n");
		currentToken = readToken();
		if(!e5())
		{
			printf("Erro Sintatico na linha [%d] coluna [%d]:: Expressao invalida\n",lines,columns);
			exit(1);
		}
		else return z();		
	}
	else return true;
}

bool SynLexPortugol::e5(void)
{
	printf("e5 - %d\n",currentToken );
	if (currentToken == _id_)
	{
		printf("id.\n");
		currentToken = readToken();
		return b();
	}
	else if (currentToken == _const_)
	{
		printf("constante.\n");
		currentToken = readToken();
		return true;
	}
	else if (currentToken == _falso_)
	{
		printf("falso\n");
		currentToken = readToken();
		return true;
	}
	else if (currentToken == _verdadeiro_)
	{
		printf("verdadeiro\n");
		currentToken = readToken();
		return true;
	}
	else if (currentToken == _ap_)
	{
		currentToken = readToken();
		printf("abre parenteses\n");

		if(!e0())
		{
			printf("Erro Sintatico na linha [%d] coluna [%d]:: Expressao invalida\n",lines,columns);
			exit(1);
		}

		if(currentToken == _fp_)
		{
			printf("fexa parenteses\n");

			currentToken = readToken();
			return true;
		}
		else
		{
			printf("Erro Sintatico na linha [%d] coluna [%d]:: Token <fp> faltando.\n",lines,columns);
			exit(1);
		}
	}
	else return false;
}

bool SynLexPortugol::b(void)
{
	printf("b - %d\n",currentToken );
	if(currentToken == _ac_)
	{
		printf("abre colchete\n");
		currentToken = readToken();
		
		if(!e0())
		{
			printf("Erro Sintatico na linha [%d] coluna [%d]:: Expressao invalida\n",lines,columns);
			exit(1);
		}

		if(currentToken == _fc_)
		{
			printf("fexa colchete\n");
			currentToken = readToken();

			if(currentToken == _ac_)
				return b();
			else
				return true;
		}
		else
		{
			printf("Erro Sintatico na linha [%d] coluna [%d]:: Token <fc> faltando.\n",lines,columns);
			exit(1);
		}
	}
	else return true;	
}