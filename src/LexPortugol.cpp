#include "LexPortugol.h"

LexPortugol::LexPortugol(char *file)
{
	lines = 1;
	columns = 1;

	if((_file = fopen(file,"r")) == NULL)
	{
		printf("Erro ao abrir o arquivo.\n");
		exit(1);
	}

	reservedWords.insert(pair<string,token_t>( "algoritmo"		, _algo_			));
	reservedWords.insert(pair<string,token_t>( "inicio"     	, _inicio_			));
	reservedWords.insert(pair<string,token_t>( "fim"        	, _fim_ 			));
	reservedWords.insert(pair<string,token_t>( "variaveis"      , _vars_ 			));
	reservedWords.insert(pair<string,token_t>( "fimvariaveis"   , _fimvar_ 			));
	reservedWords.insert(pair<string,token_t>( "se"             , _se_ 				));
	reservedWords.insert(pair<string,token_t>( "senao"          , _senao_ 			));
	reservedWords.insert(pair<string,token_t>( "entao"          , _entao_ 			));
	reservedWords.insert(pair<string,token_t>( "fimse"          , _fimse_ 			));
	reservedWords.insert(pair<string,token_t>( "enquanto"       , _enquanto_		));
	reservedWords.insert(pair<string,token_t>( "fimenquanto"    , _fimenquanto_		));
	reservedWords.insert(pair<string,token_t>( "leia"           , _read_			));
	reservedWords.insert(pair<string,token_t>( "imprima"        , _print_			));
	reservedWords.insert(pair<string,token_t>( "inteiro"        , _int_				));
	reservedWords.insert(pair<string,token_t>( "caractere"      , _char_			));
	reservedWords.insert(pair<string,token_t>( "real"           , _real_			));
	reservedWords.insert(pair<string,token_t>( "literal"        , _string_			));
	reservedWords.insert(pair<string,token_t>( "logico"         , _bool_			));
	reservedWords.insert(pair<string,token_t>( "inteiros"       , _intcomp_			));
	reservedWords.insert(pair<string,token_t>( "reais"          , _realcomp_		));
	reservedWords.insert(pair<string,token_t>( "literais"       , _stringcomp_		));
	reservedWords.insert(pair<string,token_t>( "logicos"        , _boolcomp_		));
	reservedWords.insert(pair<string,token_t>( "verdadeiro"     , _verdadeiro_		));
	reservedWords.insert(pair<string,token_t>( "falso"          , _falso_			));
	reservedWords.insert(pair<string,token_t>( "e"             	, _Elogic_			));
	reservedWords.insert(pair<string,token_t>( "ou"             , _OUlogic_			));
	reservedWords.insert(pair<string,token_t>( "nao"            , _NOTlogic_		));
	reservedWords.insert(pair<string,token_t>( "faca"           , _faca_			));
}	
LexPortugol::~LexPortugol()
{
	fclose(_file);
}

token_t LexPortugol::readToken(void)
{
	char fita;
	
	states_t q = q0;
	
	string reserved;

	map<string,token_t>::iterator _r;
	
	reserved.clear();
				
	while(true)
	{
		if(q == q0)
		{
			fita = fgetc(_file);

			if(fita == EOF)break;

			if(fita == ' ')
			{
				columns++;				
			}
			else if(fita == '\n')
			{
				lines++;
				columns = 0;
			}
			else if(fita == '\t')
			{
				columns+= 4;				
			}
			else if(fita == ';')
			{
				columns++;
				q = q1;
			}
			else if(fita == ',')
			{
				columns++;
				q = q2;
			}
			else if(fita == ':')
			{
				columns++;
				q = q3;
			}
			else if(fita == '(')
			{
				columns++;
				q = q5;
			}
			else if(fita == ')')
			{
				columns++;
				q = q6;
			}
			else if(fita == '\"')
			{
				columns++;
				q = q7;
			}
			else if(fita == '\'')
			{
				columns++;
				q = q9;
			}
			else if(fita == '=')
			{
				columns++;
				q = q13;
			}
			else if(fita == '>')
			{
				columns++;
				q = q14;	
			}
			else if(fita == '<')
			{
				columns++;
				q = q16;	
			}
			else if(fita == '/')
			{
				columns++;
				q = q19;	
			}
			else if(fita == '*')
			{
				columns++;
				q = q20;	
			}
			else if(fita == '%')
			{
				columns++;
				q = q21;	
			}
			else if(fita == '+')
			{
				columns++;
				q = q22;	
			}
			else if(fita == '-')
			{
				columns++;
				q = q23;	
			}
			else if(fita >= '1' && fita <= '9')
			{
				columns++;
				q = q24;	
			}
			else if(fita == '0')
			{
				columns++;
				q = q27;	
			}
			else if(fita == '[')
			{
				columns++;
				q = q35;	
			}
			else if(fita == ']')
			{						
				columns++;
				q = q36;
			}
			else if(fita == 'm')
			{								
				columns++;
				reserved+=fita;
				q = q37;
			}

			else if((isalpha(fita) || fita == '_') && fita != 'm')
			{
				reserved+=fita;
				columns++;
				q = q34;	
			}
			else
			{
				cout << "\nErro léxico na linha [" \
					 << lines << "] coluna [" \
					 << columns << "] caractere ( ";
					 cout << fita;cout << " ) inválido.\n";
				exit(1);
			}

		}

		else if(q == q1)
		{
			return _pv_;			
		}
		else if(q == q2)
		{
			return _v_;			
		}
		else if(q == q3)
		{
			fita = fgetc(_file);
			
			if(fita == '=')
			{
				columns++;
				q = q4;
			}
			else
			{	
				
				ungetc(fita,_file);
				return _pp_;
			}	

		}
		else if(q == q4)
		{
			return _atrib_;
		}
		else if(q == q5)
		{
			return _ap_;
		}
		else if(q == q6)
		{
			return _fp_;
		}
		else if(q == q7)
		{
			fita = fgetc(_file);

			columns++;

			if(fita == '\"')
			{
				q = q8;	
			}
			else if(fita == EOF)
			{
				cout << "\nErro léxico na linha ["\
					 << lines << "] coluna ["\
					 << columns << "] caracter (" ;cout << fita;cout << ") inválido em contantes.\n";

				exit(1);	  	
			}
			else
				q = q7;

		}
		else if(q == q8)
		{
			return _const_;
		}
		else if(q == q9)
		{
			fita = fgetc(_file);
			columns++;

			if(fita == '\\')
			{
				q = q11;

			}else if(fita == '\'')
			{
				q = q12;
			}
			else
				q = q10;
		}
		else if(q == q10)
		{				
			fita = fgetc(_file);
			columns++;
			if(fita == '\'')
			{
				q = q12;
			}
			else
			{

				cout << "\nErro léxico na linha ["\
					 << lines << "] coluna [" \
					 << columns << "] caractere (";cout << fita;cout << ") inválido ou multi-constante.\n";

				exit(1);
			}	

		}
		else if(q == q11)
		{
			fita = fgetc(_file);
			columns++;
			if(fita == 'r' || fita == 'n' || fita == '\\')
			{
				q = q39;
			}
			else
			{

				cout << "\nErro léxico na linha ["\
					 << lines << "] coluna [" \
					 << columns << "] caractere (";cout << fita;cout << ") não compõe caractere especial.\n";

				exit(1);
			}	


		}
		else if(q == q39)
		{				
			fita = fgetc(_file);
			columns++;
			if(fita == '\'')
			{
				q = q12;
			}
			else
			{

				cout << "\nErro léxico na linha ["\
					 << lines << "] coluna [" \
					 << columns << "] caractere (" ;cout<< fita;cout << ") não compõe caractere especial.\n";

				exit(1);
			}	

		}
		else if(q == q12)
		{
			return _const_;
		}
		else if(q == q13)
		{
			return _eq_;
		}
		else if(q == q14)
		{
			fita = fgetc(_file);
			if(fita == '=')
			{
				q = q15;
				columns++;
			}
			else
			{
								
				ungetc(fita,_file);
				return _gt_;
			}		

		}
		else if(q == q15)
		{
			return _geq_;
		}
		else if(q == q16)
		{
			fita = fgetc(_file);
			if(fita == '=')
			{
				q = q17;
				columns++;
			}
			else if(fita == '>')
			{
				q = q18;
			}
			else
			{
				
				ungetc(fita,_file);
				return _lt_;
			}
		}
		else if(q == q17)
		{	
			return _leq_;
		}
		else if(q == q18)
		{
			return _neq_;
		}
		else if(q == q19)
		{
			return _div_;
		}	
		else if(q == q20)
		{				
			return _mult_;
		}
		else if(q == q21)
		{				
			return _mod_;
		}

		else if(q == q22)
		{
			fita = fgetc(_file);

			if(fita >= '1' && fita <= '9')
			{
				q = q24;
				columns++;
			}
			else
			{
				
				ungetc(fita,_file);
				return _sum_;
			}		
			
		}
		else if(q == q23)
		{
			fita = fgetc(_file);

			if(fita >= '1' && fita <= '9')
			{
				q = q24;
				columns++;
			}
			else if(fita == '(')
			{
				
				ungetc(fita,_file);
				return _uneg_;
			}
			else
			{
				
				ungetc(fita,_file);
				return _sub_;
			}
		}

		else if(q == q24)
		{
			fita = fgetc(_file);

			if(fita >= '0' && fita <= '9')
			{
				q = q24;
				columns++;
			}
			else if(fita == '.')
			{
				q = q25;
				columns++;
			}
			else
			{
				
				ungetc(fita,_file);
				return _const_;
			}
		}
		else if(q == q25)
		{
			fita = fgetc(_file);

			if(fita >= '0' && fita <= '9')
			{
				q = q24;
				columns++;
			}
			else
			{
				cout << "\nErro léxico na linha ["\
					 << lines << "] coluna [" \
					 << columns << "] caractere (";cout << fita;cout << ") não compõe número real.\n";
				
				exit(1);
			}
			
		}
		else if(q == q27)
		{
			fita = fgetc(_file);

			if(fita == 'x' || fita == 'X')
			{
				columns++;
				q = q28;
			}
			else if(fita == 'c' || fita == 'C')
			{
				columns++;
				q = q29;

			}
			else if(fita == 'b' || fita == 'B')
			{
				columns++;
				q = q30;
			}
			else 
			{
				
				ungetc(fita,_file);
				return _const_;
			}

		}
		else if(q == q28)
		{
			fita = fgetc(_file);
			columns++;

			if((fita >= '0' && fita <= '9') || (fita >= 'a' && fita <= 'f') || (fita >= 'A' && fita <= 'F'))
			{
				q = q32;
			}
			else
			{
				cout << "\nErro léxico na linha ["\
					 << lines << "] coluna [" \
					 << columns << "] caractere (";cout << fita;cout << ") não compõe constante hexadecimal.\n";

				exit(1);
			}	

		}
		else if(q == q29)
		{
			fita = fgetc(_file);

			if(fita >= '0' && fita <= '7')
			{
				columns++;
				q = q33;					
			}
			else
			{
				cout << "\nErro léxico na linha ["\
					 << lines << "] coluna [" \
					 << columns << "] caractere (" << fita << ") não compõe constante octal.\n";
			
				exit(1);
			}

		}
		else if(q == q30)
		{
			fita = fgetc(_file);

			if(fita == '0' || fita == '1')
			{
				columns++;
				q = q31;					
			}
			else
			{
				cout << "\nErro léxico na linha ["\
					 << lines << "] coluna [" \
					 << columns << "] caractere ("; cout << fita ;cout <<") não compõe constante binária.\n";

				exit(1);
			}
		}

		else if(q == q32)
		{
			fita = fgetc(_file);
			

			if((fita >= '0' && fita <= '9') || (fita >= 'a' && fita <= 'f') || (fita >= 'A' && fita <= 'F'))
			{
				columns++;
				q = q32;
			}
			else
			{
				
				ungetc(fita,_file);
				return _const_;
			}
		}

		else if(q == q33)
		{
			fita = fgetc(_file);

			if(fita >= '0' && fita <= '7')
			{
				columns++;
				q = q33;					
			}
			else
			{
				
				ungetc(fita,_file);
				return _const_;
			}
		}

		else if(q == q31)
		{
			fita = fgetc(_file);

			if(fita == '0' || fita == '1')
			{
				columns++;
				q = q31;					
			}
			else
			{
				
				ungetc(fita,_file);
				return _const_;
			}
		}

		else if(q == q35)
		{
			return _ac_;			
		}

		else if(q == q36)
		{				
			return _fc_;				
		}
		
		else if(q == q37)
		{
			fita = fgetc(_file);

			if(fita == 'a')
			{
				columns++;
				q = q38;
			}
			else if(isalnum(fita) ||fita == '_' )
			{
				reserved+=fita;

				columns++;
				q = q34;
			}
			else
			{
				cout << "\nErro léxico na linha ["\
					 << lines << "] coluna [" \
					 << columns << "] caractere (";cout << fita;cout << ") inválido na declaração de matriz.\n";
			
				exit(1);
			}					
		}
		else if(q == q38)
		{
			fita = fgetc(_file);

			if(fita == 't')
			{
				columns++;
				q = q40;
			}
			else if(isalnum(fita) || fita == '_')
			{
				reserved+=fita;

				columns++;
				q = q34;
			}
			else
			{
				cout << "\nErro léxico na linha ["\
					 << lines << "] coluna [" \
					 << columns << "] caractere (";cout << fita;cout << ") inválido na declaração de matriz.\n";
			
				exit(1);
			}
		}
		else if(q == q40)
		{
			fita = fgetc(_file);

			if(fita == 'r')
			{
				columns++;
				q = q41;
			}
			else if(isalnum(fita)  ||fita == '_' )
			{
				reserved+=fita;

				columns++;
				q = q34;
			}
			else
			{
				cout << "\nErro léxico na linha ["\
					 << lines << "] coluna [" \
					 << columns << "] caractere (";cout << fita;cout << ") inválido na declaração de matriz.\n";
			
				exit(1);
			}
		}
		else if(q == q41)
		{
			fita = fgetc(_file);

			if(fita == 'i')
			{
				columns++;
				q = q42;
			}
			else if(isalnum(fita) ||fita == '_' )
			{
				reserved+=fita;

				columns++;
				q = q34;
			}
			else
			{
				cout << "\nErro éxico na linha ["\
					 << lines << "] coluna [" \
					 << columns << "] caractere (";cout << fita;cout << ") inválido na declaração de matriz.\n";
			
				exit(1);
			}
		}
		else if(q == q42)
		{
			fita = fgetc(_file);

			if(fita == 'z')
			{
				columns++;
				q = q43;
			}
			else if(isalnum(fita)|| fita == '_' )
			{
				reserved+=fita;

				columns++;
				q = q34;
			}
			else
			{
				cout << "\nErro léxico na linha ["\
					 << lines << "] coluna [" \
					 << columns << "] caractere (";cout << fita;cout << ") inválido na declaração de matriz.\n";
			
				exit(1);
			}
		}
		else if(q == q43)
		{
			fita = fgetc(_file);

			if(fita == '[')
			{
				columns++;
				q = q44;
			}
			else if(isalnum(fita) || fita == '_' )
			{
				reserved+=fita;

				columns++;
				q = q34;
			}
			else
			{
				cout << "\nErro léxico na linha ["\
					 << lines << "] coluna [" \
					 << columns << "] caractere (";cout << fita;cout << ") inválido na declaração de matriz.\n";
			
				exit(1);
			}
		}

		else if(q == q44)
		{
			fita = fgetc(_file);

			if(isdigit(fita) && fita != '0')
			{
				columns++;
				q = q45;
			}
			else
			{
				cout << "\nErro léxico na linha ["\
					 << lines << "] coluna [" \
					 << columns << "] caractere (";cout << fita;cout << ") inválido na declaração de matriz.\n";
			
				exit(1);
			}
		}
		else if(q == q45)
		{
			fita = fgetc(_file);

			if(fita >= '0' && fita <= '9')
			{
				columns++;
				q = q45;
			}
			else if(fita == ']')
			{
				columns++;
				q = q46;
			}
			else
			{
				cout << "\nErro léxico na linha ["\
					 << lines << "] coluna [" \
					 << columns << "] caractere (";cout << fita;cout << ") inválido na declaração de matriz.\n";
			
				exit(1);
			}
		}
		else if(q == q46)
		{
			fita = fgetc(_file);

			if(fita == '[')
			{
				columns++;
				q = q44;					
			}
			else if(fita == ' ')
			{
				columns++;
				q = q46;	
			}
			else if(fita == 'd')
			{
				columns++;
				q = q47;
			}
			else
			{
				cout << "\nErro léxico na linha ["\
					 << lines << "] coluna [" \
					 << columns << "] caractere (";cout << fita;cout << ") inválido na declaração de matriz.\n";
			
				exit(1);
			}
		}
		else if(q == q47)
		{
			fita = fgetc(_file);

			if(fita == 'e')
			{
				columns++;
				q = q48;					
			}
			else
			{
				cout << "\nErro léxico na linha ["\
					 << lines << "] coluna [" \
					 << columns << "] caractere (";cout << fita;cout << ") inválido na declaração de matriz.\n";
			
				exit(1);
			}
		}
		// resolver aqui n tem token dimention
		else if(q == q48)
		{			
			return _dimension_;
		}

		else if(q == q34)
		{
			fita = fgetc(_file);

			if(isalnum(fita) || fita == '_')	
			{
				q = q34;
				columns++;
				reserved+=fita;
			}
			else
			{				
				_r = reservedWords.find(reserved);

				if(_r != reservedWords.end())
				{
					
					ungetc(fita,_file);
					return _r->second;
				}
				else
				{
					
					ungetc(fita,_file);
					return _id_;
				}
			}				
		}			

	}// fim laço que le os tokens
	
	
	return _error_;
}