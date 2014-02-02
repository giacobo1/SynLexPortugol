// TODO: talvez trocar os cout's de erro por exceções..
// TODO: dar uma revisada e finalizar a gramática

#ifndef SYNLEXPORTUGOL_H
#define SYNLEXPORTUGOL_H
#include "LexPortugol.h"


class SynLexPortugol : public LexPortugol
{
	token_t currentToken;
	bool vazio;

public:
	SynLexPortugol(char *file):LexPortugol(file)
	{
		//vazio = false;
		currentToken = _error_;
	}
	~SynLexPortugol(){}
	void analise(void);

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
	bool q(void);
	bool x(void);
	bool x_(void);

	bool e1(void);
	bool k(void);
	bool y(void);
	bool y_(void);

	bool e2(void);

	bool e3(void);
	bool g(void);
	bool w(void);
	bool w_(void);

	bool e4(void);
	bool u(void);
	bool z(void);
	bool z_(void);

	bool e5(void);
	bool b(void);
};
#endif