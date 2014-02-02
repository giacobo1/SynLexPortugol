/*
	Universidade Federal de Pelotas
	Bacharelado em Ciência da Computação
	Disciplina de Linguagens Formais.

	Analizador Sintetico para linguavem portugol.

	Bruno Giacobo Pinto - 11107588 - bgpinto@inf.ufpel.edu.br;
	Évero Signorini - 11108253;
*/

#ifndef SYNLEXPORTUGOL_H
#define SYNLEXPORTUGOL_H
#include "LexPortugol.h"

class SynLexPortugol : public LexPortugol
{
	
public:
	SynLexPortugol(char *file):LexPortugol(file)
	{
		currentToken = _error_;
	}

	~SynLexPortugol(){}
	void analise(void);


private:


	token_t currentToken;

	void prog(void);
	
	bool dec(void);
	bool decList(void);
	bool idList(void);	
	bool tipo(void);	
	bool compTipo(void);
	
	bool comand(void);
	bool lValue(void);
	bool rValue(void);
	bool args(void);
	bool argList(void);
	bool Else(void);

	bool e0(void);
	bool x(void);

	bool e1(void);
	bool y(void);

	bool e2(void);

	bool e3(void);
	bool w(void);

	bool e4(void);
	bool z(void);

	bool e5(void);
	bool b(void);
};
#endif