// TODO: talvez trocar os cout's de erro por exceções..
// TODO: dar uma revisada e finalizar a gramática

#ifndef SYNLEXPORTUGOL_H
#define SYNLEXPORTUGOL_H
#include "LexPortugol.h"


class SynLexPortugol : public LexPortugol
{
public:
	SynLexPortugol(char *file):LexPortugol(file){}
	~SynLexPortugol(){}
	void analise(void);

	void prog(void);

};




#endif