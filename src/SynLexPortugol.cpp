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
		printf("Erro Sintatico na linha [%d] coluna [%d].\n",lines,columns);
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

	

	system("clear");
	printf(
		"%s\n\n\t\t\t\t\t\t\tAnalise Sintatica realizada com sucesso!!!\n%s\n",
			"________________________________________________________________________________________________________________________________________________",
			"________________________________________________________________________________________________________________________________________________"
		);
}


bool SynLexPortugol::dec(void)
{
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
	currentToken = readToken();
	
	if(currentToken == _id_)
	{
		if(!lValue())
		{
			printf("Erro Sintatico na linha [%d] coluna [%d].\n",lines,columns);
			exit(1);
		}
		
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
	if(currentToken == _senao_)
	{
		return comand();
	}
	else
		return true;
}

bool SynLexPortugol::e0(void)
{
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

bool SynLexPortugol::e2(void)
{
	if(currentToken == _NOTlogic_)
	{
		currentToken = readToken();
		
		return e3();
	}
	if(currentToken == _uneg_)
	{
		currentToken = readToken();
		
		return e3();
	}
	else
		return e3();

}

bool SynLexPortugol::e3(void)
{
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
	if (currentToken == _id_)
	{
		currentToken = readToken();
		return b();
	}
	else if (currentToken == _const_)
	{
		currentToken = readToken();
		return true;
	}
	else if (currentToken == _falso_)
	{
		currentToken = readToken();
		return true;
	}
	else if (currentToken == _verdadeiro_)
	{
		currentToken = readToken();
		return true;
	}
	else if (currentToken == _ap_)
	{
		currentToken = readToken();
		if(!e0())
		{
			printf("Erro Sintatico na linha [%d] coluna [%d]:: Expressao invalida\n",lines,columns);
			exit(1);
		}

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
	else return false;
}

bool SynLexPortugol::b(void)
{
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