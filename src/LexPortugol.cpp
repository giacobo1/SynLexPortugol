
#include "LexPortugol.h"


LexPortugol::LexPortugol(char *file)
{
	lines = 1;
	columns = 0;

	if((_file = fopen(file,"r")) == NULL)
	{
		printf("Erro ao abrir o arquivo.\n");
		exit(1);
	}

	filename = file;

	reservedWords.insert(pair<string,string>("algoritmo","<algo>"));
	reservedWords.insert(pair<string,string>("início","<inicio> "));
	reservedWords.insert(pair<string,string>("fim","<fim> "));
	reservedWords.insert(pair<string,string>("variáveis","<vars> "));
	reservedWords.insert(pair<string,string>("fimvariáveis","<fimvar> "));
	reservedWords.insert(pair<string,string>("se","<se> "));
	reservedWords.insert(pair<string,string>("senão","<senao> "));
	reservedWords.insert(pair<string,string>("então","<entao> "));
	reservedWords.insert(pair<string,string>("fimse","<fimse> "));
	reservedWords.insert(pair<string,string>("enquanto","<enquanto> "));
	reservedWords.insert(pair<string,string>("fimenquanto","<fimenquanto> "));
	reservedWords.insert(pair<string,string>("leia","<read> "));
	reservedWords.insert(pair<string,string>("imprima","<print> "));
	reservedWords.insert(pair<string,string>("inteiro","<int> "));
	reservedWords.insert(pair<string,string>("caractere","<char> "));
	reservedWords.insert(pair<string,string>("real","<real> "));
	reservedWords.insert(pair<string,string>("literal","<string> "));
	reservedWords.insert(pair<string,string>("lógico","<bool> "));
	reservedWords.insert(pair<string,string>("inteiros","<intcomp> "));
	reservedWords.insert(pair<string,string>("reais","<realcomp> "));
	reservedWords.insert(pair<string,string>("literais","<stringcomp> "));
	reservedWords.insert(pair<string,string>("lógicos","<boolcomp> "));
	reservedWords.insert(pair<string,string>("verdadeiro","<true> "));
	reservedWords.insert(pair<string,string>("falso","<false> "));
	reservedWords.insert(pair<string,string>("e","<Elogic> "));
	reservedWords.insert(pair<string,string>("ou","<OUlogic> "));
	reservedWords.insert(pair<string,string>("não","<NOTlogic> "));
	reservedWords.insert(pair<string,string>("faça","<faca> "));
	reservedWords.insert(pair<string,string>("função","<function> "));

}	
LexPortugol::~LexPortugol()
{
	fclose(_file);
}


string LexPortugol::convertWstring(wstring ws)
{
  //std::setlocale(LC_ALL, "");
  const std::locale locale("");
  typedef std::codecvt<wchar_t, char, std::mbstate_t> converter_type;
  const converter_type& converter = std::use_facet<converter_type>(locale);
  std::vector<char> to(ws.length() * converter.max_length());
  std::mbstate_t state;
  const wchar_t* from_next;
  char* to_next;
  converter.out(state, ws.data(), ws.data() + ws.length(), from_next, &to[0], &to[0] + to.size(), to_next);
 
  string X(&to[0], to_next);

  return X;

}


token_t LexPortugol::readToken(void)
{
	//char ;
	wchar_t fita;
	int i = 0;

	states_t q;
	token_t t;

	wstring reserved;

	map<string,string>::iterator _r;


	printf("\n\t\t\t\t\t%s\n",filename.c_str());
	cout << "\n-------------------------------------------------------------------------------------------------------\n";
	cout << lines << "  | ";
	while(fita != WEOF)
	{
		q = q0;
		reserved.clear();
					
		while(true)
		{

			if(q == q0)
			{
				fita = getwc(_file);

				if(fita == WEOF)break;

				if(fita == L' ')
				{
				columns++;
					break;
				}
				else if(fita == L'\n')
				{

					lines++;
					columns = 0;
					cout << '\n';
					if(lines > 9)
						cout << lines << " | ";
					else
						cout << lines << "  | ";
					
					break;
				}
				else if(fita == L'\t')
				{
					columns+= 4;
					cout << '\t';	

					break;
				}
				else if(fita == L';')
				{
					columns++;
					q = q1;
				}
				else if(fita == L',')
				{
					columns++;
					q = q2;
				}
				else if(fita == L':')
				{
					columns++;
					q = q3;
				}
				else if(fita == L'(')
				{
					columns++;
					q = q5;
				}
				else if(fita == L')')
				{
					columns++;
					q = q6;
				}
				else if(fita == L'\"')
				{
					columns++;
					q = q7;
				}
				else if(fita == L'\'')
				{
					columns++;
					q = q9;
				}
				else if(fita == L'=')
				{
					columns++;
					q = q13;
				}
				else if(fita == L'>')
				{
					columns++;
					q = q14;	
				}
				else if(fita == L'<')
				{

					columns++;
					q = q16;	
				}
				else if(fita == L'/')
				{

					columns++;
					q = q19;	
				}
				else if(fita == L'*')
				{
					columns++;
					q = q20;	
				}
				else if(fita == L'%')
				{
					columns++;
					q = q21;	
				}
				else if(fita == L'+')
				{
					columns++;
					q = q22;	
				}
				else if(fita == L'-')
				{
					columns++;
					q = q23;	
				}
				else if(fita >= L'1' && fita <= L'9')
				{
					columns++;
					q = q24;	
				}
				else if(fita == L'0')
				{
					columns++;
					q = q27;	
				}
				else if(fita == L'[')
				{
					columns++;
					q = q35;	
				}
				else if(fita == L']')
				{						
					columns++;
					q = q36;
				}
				else if(fita == L'm')
				{								
					columns++;
					reserved+=fita;
					q = q37;
				}

				else if((isalpha(fita) || fita == L'_') && fita != L'm')

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
						 wcout << fita;cout << " ) inválido.\n";
					exit(1);
				}

			}

			else if(q == q1)
			{
				cout << "<pv> ";
				break;
			}
			else if(q == q2)
			{
				cout << "<v> ";
				break;
			}
			else if(q == q3)
			{
				fita = getwc(_file);
				
				if(fita == L'=')
				{
					columns++;
					q = q4;
				}
				else
				{
					ungetwc(fita,_file);
					cout << "<pp> ";
					break;
				}	

			}
			else if(q == q4)
			{
				cout << "<atrib> ";
				break;
			}
			else if(q == q5)
			{
				cout << "<ap> ";
				break;
			}
			else if(q == q6)
			{
				cout << "<fp> ";
				break;
			}
			else if(q == q7)
			{
				fita = getwc(_file);

				columns++;

				if(fita == L'\"')
				{
					q = q8;	
				}
				else if(fita == WEOF)
				{
					cout << "\nErro léxico na linha ["\
						 << lines << "] coluna ["\
						 << columns << "] caracter (" ;wcout << fita;cout << ") inválido em contantes.\n";

					exit(1);	  	
				}
				else
					q = q7;

			}
			else if(q == q8)
			{
				cout << "<const> ";
				break;
			}
			else if(q == q9)
			{
				fita = getwc(_file);
				columns++;

				if(fita == L'\\')
				{
					q = q11;

				}else if(fita == L'\'')
				{
					q = q12;
				}
				else
					q = q10;
			}
			else if(q == q10)
			{				
				fita = getwc(_file);
				columns++;
				if(fita == L'\'')
				{
					q = q12;
				}
				else
				{

					cout << "\nErro léxico na linha ["\
						 << lines << "] coluna [" \
						 << columns << "] caractere (";wcout << fita;cout << ") inválido ou multi-constante.\n";

					exit(1);
				}	

			}
			else if(q == q11)
			{
				fita = getwc(_file);
				columns++;
				if(fita == L'r' || fita == L'n' || fita == L'\\')
				{
					q = q39;
				}
				else
				{

					cout << "\nErro léxico na linha ["\
						 << lines << "] coluna [" \
						 << columns << "] caractere (";wcout << fita;cout << ") não compõe caractere especial.\n";

					exit(1);
				}	


			}
			else if(q == q39)
			{				
				fita = getwc(_file);
				columns++;
				if(fita == L'\'')
				{
					q = q12;
				}
				else
				{

					cout << "\nErro léxico na linha ["\
						 << lines << "] coluna [" \
						 << columns << "] caractere (" ;wcout<< fita;cout << ") não compõe caractere especial.\n";

					exit(1);
				}	

			}
			else if(q == q12)
			{
				cout << "<const> ";
				break;
			}
			else if(q == q13)
			{
				cout << "<eq> ";
				break;
			}
			else if(q == q14)
			{
				fita = getwc(_file);
				if(fita == L'=')
				{
					q = q15;
					columns++;
				}
				else
				{
					cout << "<gt> ";
					ungetwc(fita,_file);
					break;
				}		

			}
			else if(q == q15)
			{
				cout << "<geq> ";
				break;
			}
			else if(q == q16)
			{
				fita = getwc(_file);
				if(fita == L'=')
				{
					q = q17;
					columns++;
				}
				else if(fita == L'>')
				{
					q = q18;
				}
				else
				{
					cout << "<lt> ";
					ungetwc(fita,_file);
					break;
				}
			}
			else if(q == q17)
			{
				cout << "<leq> ";
				break;
			}
			else if(q == q18)
			{
				cout << "<neq> ";
				break;
			}
			else if(q == q19)
			{
				cout << "<div> ";
				break;
			}	
			else if(q == q20)
			{				
				cout << "<mult> ";
				break;
			}
			else if(q == q21)
			{				
				cout << "<mod> ";
				break;
			}

			else if(q == q22)
			{
				fita = getwc(_file);

				if(fita >= L'1' && fita <= L'9')
				{
					q = q24;
					columns++;
				}
				else
				{
					cout << "<sum> ";
					ungetwc(fita,_file);
					break;
				}		
				
			}
			else if(q == q23)
			{
				fita = getwc(_file);

				if(fita >= L'1' && fita <= L'9')
				{
					q = q24;
					columns++;
				}
				else if(fita == L'(')
				{
					cout << "<uneg> ";
					ungetwc(fita,_file);
					break;	
				}
				else
				{
					cout << "<sub> ";
					ungetwc(fita,_file);
					break;
				}
			}

			else if(q == q24)
			{
				fita = getwc(_file);

				if(fita >= L'0' && fita <= L'9')
				{
					q = q24;
					columns++;
				}
				else if(fita == L'.')
				{
					q = q25;
					columns++;
				}
				else
				{
					cout << "<const> ";
					ungetwc(fita,_file);
					break;
				}
			}
			else if(q == q25)
			{
				fita = getwc(_file);

				if(fita >= L'0' && fita <= L'9')
				{
					q = q24;
					columns++;
				}
				else
				{
					cout << "\nErro léxico na linha ["\
						 << lines << "] coluna [" \
						 << columns << "] caractere (";wcout << fita;cout << ") não compõe número real.\n";
					
					exit(1);
				}
				
			}
			else if(q == q27)
			{
				fita = getwc(_file);

				if(fita == L'x' || fita == L'X')
				{
					columns++;
					q = q28;
				}
				else if(fita == L'c' || fita == L'C')
				{
					columns++;
					q = q29;

				}
				else if(fita == L'b' || fita == L'B')
				{
					columns++;
					q = q30;
				}
				else 
				{
					cout << "<const> ";
					ungetwc(fita,_file);
					break;
				}

			}
			else if(q == q28)
			{
				fita = getwc(_file);
				columns++;

				if((fita >= L'0' && fita <= L'9') || (fita >= L'a' && fita <= L'f') || (fita >= L'A' && fita <= L'F'))
				{
					q = q32;
				}
				else
				{
					cout << "\nErro léxico na linha ["\
						 << lines << "] coluna [" \
						 << columns << "] caractere (";wcout << fita;cout << ") não compõe constante hexadecimal.\n";

					exit(1);
				}	

			}
			else if(q == q29)
			{
				fita = getwc(_file);

				if(fita >= L'0' && fita <= L'7')
				{
					columns++;
					q = q33;					
				}
				else
				{
					wcout << "\nErro léxico na linha ["\
						 << lines << "] coluna [" \
						 << columns << "] caractere (" << fita << ") não compõe constante octal.\n";
				
					exit(1);
				}

			}
			else if(q == q30)
			{
				fita = getwc(_file);

				if(fita == L'0' || fita == L'1')
				{
					columns++;
					q = q31;					
				}
				else
				{
					cout << "\nErro léxico na linha ["\
						 << lines << "] coluna [" \
						 << columns << "] caractere ("; wcout << fita ;cout <<") não compõe constante binária.\n";

					exit(1);
				}
			}

			else if(q == q32)
			{
				fita = getwc(_file);
				

				if((fita >= L'0' && fita <= L'9') || (fita >= L'a' && fita <= L'f') || (fita >= L'A' && fita <= L'F'))
				{
					columns++;
					q = q32;
				}
				else
				{
					cout << "<const> ";
					ungetwc(fita,_file);
					break;
				}
			}

			else if(q == q33)
			{
				fita = getwc(_file);

				if(fita >= L'0' && fita <= L'7')
				{
					columns++;
					q = q33;					
				}
				else
				{
					cout << "<const> ";
					ungetwc(fita,_file);
					break;
				}
			}

			else if(q == q31)
			{
				fita = getwc(_file);

				if(fita == L'0' || fita == L'1')
				{
					columns++;
					q = q31;					
				}
				else
				{

					cout << "<const> ";
					ungetwc(fita,_file);
					break;
				}
			}

			else if(q == q35)
			{
				cout << "<ac> ";
				break;				
			}

			else if(q == q36)
			{				
				cout << "<fc> ";
				break;					
			}
			
			else if(q == q37)
			{
				fita = getwc(_file);

				if(fita == L'a')
				{
					columns++;
					q = q38;
				}
				else if(isalnum(fita) || isalnum(fita) ||fita == L'_' || fita == L'á' || fita == L'í' || fita == L'ã' || fita == L'ç' || fita == L'ó')
				{
					reserved+=fita;

					columns++;
					q = q34;
				}
				else
				{
					cout << "\nErro léxico na linha ["\
						 << lines << "] coluna [" \
						 << columns << "] caractere (";wcout << fita;cout << ") inválido na declaração de matriz.\n";
				
					exit(1);
				}					
			}
			else if(q == q38)
			{
				fita = getwc(_file);

				if(fita == L't')
				{
					columns++;
					q = q40;
				}
				else if(isalnum(fita) || isalnum(fita)|| fita == L'_' || fita == L'á' || fita == L'í' || fita == L'ã' || fita == L'ç' || fita == L'ó')
				{
					reserved+=fita;

					columns++;
					q = q34;
				}
				else
				{
					cout << "\nErro léxico na linha ["\
						 << lines << "] coluna [" \
						 << columns << "] caractere (";wcout << fita;cout << ") inválido na declaração de matriz.\n";
				
					exit(1);
				}
			}
			else if(q == q40)
			{
				fita = getwc(_file);

				if(fita == L'r')
				{
					columns++;
					q = q41;
				}
				else if(isalnum(fita) || isalnum(fita) ||fita == L'_' || fita == L'á' || fita == L'í' || fita == L'ã' || fita == L'ç' || fita == L'ó')
				{
					reserved+=fita;

					columns++;
					q = q34;
				}
				else
				{
					cout << "\nErro léxico na linha ["\
						 << lines << "] coluna [" \
						 << columns << "] caractere (";wcout << fita;cout << ") inválido na declaração de matriz.\n";
				
					exit(1);
				}
			}
			else if(q == q41)
			{
				fita = getwc(_file);

				if(fita == L'i')
				{
					columns++;
					q = q42;
				}
				else if(isalnum(fita) || isalnum(fita) ||fita == L'_' || fita == L'á' || fita == L'í' || fita == L'ã' || fita == L'ç' || fita == L'ó')
				{
					reserved+=fita;

					columns++;
					q = q34;
				}
				else
				{
					cout << "\nErro léxico na linha ["\
						 << lines << "] coluna [" \
						 << columns << "] caractere (";wcout << fita;cout << ") inválido na declaração de matriz.\n";
				
					exit(1);
				}
			}
			else if(q == q42)
			{
				fita = getwc(_file);

				if(fita == L'z')
				{
					columns++;
					q = q43;
				}
				else if(isalnum(fita) || isalnum(fita) || fita == L'_' || fita == L'á' || fita == L'í' || fita == L'ã' || fita == L'ç' || fita == L'ó')
				{
					reserved+=fita;

					columns++;
					q = q34;
				}
				else
				{
					cout << "\nErro léxico na linha ["\
						 << lines << "] coluna [" \
						 << columns << "] caractere (";wcout << fita;cout << ") inválido na declaração de matriz.\n";
				
					exit(1);
				}
			}
			else if(q == q43)
			{
				fita = getwc(_file);

				if(fita == L'[')
				{
					columns++;
					q = q44;
				}
				else if(isalnum(fita) || isalnum(fita) || fita == L'_' || fita == L'á' || fita == L'í' || fita == L'ã' || fita == L'ç' || fita == L'ó')
				{
					reserved+=fita;

					columns++;
					q = q34;
				}
				else
				{
					cout << "\nErro léxico na linha ["\
						 << lines << "] coluna [" \
						 << columns << "] caractere (";wcout << fita;cout << ") inválido na declaração de matriz.\n";
				
					exit(1);
				}
			}

			else if(q == q44)
			{
				fita = getwc(_file);

				//if(fita >= L'1' && fita <= L'9')
				if(isdigit(fita) && fita != L'0')
				{
					columns++;
					q = q45;
				}
				else
				{
					cout << "\nErro léxico na linha ["\
						 << lines << "] coluna [" \
						 << columns << "] caractere (";wcout << fita;cout << ") inválido na declaração de matriz.\n";
				
					exit(1);
				}
			}
			else if(q == q45)
			{
				fita = getwc(_file);

				if(fita >= L'0' && fita <= L'9')
				{
					columns++;
					q = q45;
				}
				else if(fita == L']')
				{
					columns++;
					q = q46;
				}
				else
				{
					cout << "\nErro léxico na linha ["\
						 << lines << "] coluna [" \
						 << columns << "] caractere (";wcout << fita;cout << ") inválido na declaração de matriz.\n";
				
					exit(1);
				}
			}
			else if(q == q46)
			{
				fita = getwc(_file);

				if(fita == L'[')
				{
					columns++;
					q = q44;					
				}
				else if(fita == L' ')
				{
					columns++;
					q = q46;	
				}
				else if(fita == L'd')
				{
					columns++;
					q = q47;
				}
				else
				{
					cout << "\nErro léxico na linha ["\
						 << lines << "] coluna [" \
						 << columns << "] caractere (";wcout << fita;cout << ") inválido na declaração de matriz.\n";
				
					exit(1);
				}
			}
			else if(q == q47)
			{
				fita = getwc(_file);

				if(fita == L'e')
				{
					columns++;
					q = q48;					
				}
				else
				{
					cout << "\nErro léxico na linha ["\
						 << lines << "] coluna [" \
						 << columns << "] caractere (";wcout << fita;cout << ") inválido na declaração de matriz.\n";
				
					exit(1);
				}
			}
			else if(q == q48)
			{
				cout << "<dimension> ";
				break;
			}



			else if(q == q34)
			{
				fita = getwc(_file);


				// resolver acentos aqui....
				if(isalnum(fita) || fita == L'_' || fita == L'á' || fita == L'í' || fita == L'ã' || fita == L'ç' || fita == L'ó'  )		

				{
					q = q34;
					columns++;
					reserved+=fita;
				}
				else
				{
					
					_r = reservedWords.find(convertWstring(reserved));


					if(_r != reservedWords.end())
					{
						cout << _r->second;
						ungetwc(fita,_file);
						break;
					}
					else
					{
						cout << "<id> ";
						ungetwc(fita,_file);
						break; 
					}
				}				
			}			

		}// fim laço que le os tokens
	}// fim laço que le arquivo

	printf("\n-------------------------------------------------------------------------------------------------------\n \t\t\t\t\tAnalise terminada com sucesso!\n\n");

	return t;
}