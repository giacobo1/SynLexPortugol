/*
	Universidade Federal de Pelotas
	Bacharelado em Ciência da Computação
	Disciplina de Linguagens Formais.

	Analizador léxico para linguavem portugol.

	Bruno Giacobo Pinto - 11107588 - bgpinto@inf.ufpel.edu.br;
	Évero Signorini - 11108253;
*/


#ifndef LEXPORTUGOL_H
#define LEXPORTUGOL_H

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <map>

using namespace std;

//
enum states_t 
{
	q0, q1, q2, q3, q4, q5, q6, q7, q8, q9, q10, q11, q12,			\
	q13, q14, q15, q16, q17,q18,q19,q20,q21,q22,q23,q24,q25,		\
	q26,q27,q28,q29,q30,q31,q32,q33,q34,q35,q36,q37,q38,q39,q40, 	\
	q41,q42,q43,q44,q45,q46,q47,q48	
};

enum token_t	
{ 
	_algo_ = 1 ,
	_id_,
	_const_,
	_verdadeiro_,
	_falso_ ,
	_sum_,
	_sub_,
	_div_,
	_mod_,
	_mult_,
	_uneg_,
	_ap_,
	_fp_,
	_v_,
	_pp_,

	_pv_ ,
	_atrib_,
	_print_,

    _read_,
    _eq_,
    _leq_,
    _neq_,
    _geq_,
    _gt_,
    _lt_,
    _Elogic_,
    _OUlogic_,
    _NOTlogic_,
    _vars_ ,
    _fim_,
    _fimvar_,
    _fimse_,

	_fimenquanto_,
	_inicio_,
	_enquanto_,
	_faca_ ,
	_se_,
	_entao_,
	_senao_,
	_int_,
	_real_,
	_bool_,
	_char_,
	_string_,

	_intcomp_,
	_boolcomp_,
	_charcomp_,
	_stringcomp_,
	_realcomp_,
	_dimension_,
	_ac_,
	_fc_,
	_error_ 
};

//
class LexPortugol
{
	map<string , token_t> reservedWords;
	
	FILE *_file;	

public:

	
	unsigned int lines;
	unsigned int columns;
	LexPortugol(char *file);	
	~LexPortugol();

	token_t readToken(void);	
};
#endif