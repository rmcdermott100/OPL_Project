#include <stdio.h>
#include <stdbool.h>
#include "LL.h"



expr* make_JNum(int number) {

	JNum* p = malloc(sizeof(JNum));
	p->head.tag = JNUM;
	p->n = number;
	return (expr*)p;

}

expr* make_JBool(bool boolean) {

	JBool* p = malloc(sizeof(JBool));
	p->head.tag = JBOOL;
	p->b = boolean;
	return (expr*)p;

}

expr* make_JPrim(char prim) {

	JPrim* p = malloc(sizeof(JPrim));
	p->head.tag = JPRIM;
	p->p = prim;
	return (expr*)p;

}


expr* make_JIf(expr* c, expr* t, expr * f) {

	JIf *p = malloc(sizeof(JIf));
	p->head.tag = JIF;
	p->c = c;
	p->t = t;
	p->f = f;
	return (expr*)p;

}


expr* make_JApp(expr* func, expr* args) {

	JApp *p = malloc(sizeof(JApp));
	p->head.tag = JAPP;
	p->func = func;
	p->args = args;
	return (expr*)p;

}

expr* make_KRet(expr r){

    KRet *p = malloc(sizeof(KRet));
    p->head.tag = KRET;
    p->ret = r;
    return (expr*)p;
}

expr* make_KIf(expr* c, expr* t, expr* f){

    KIf *p = malloc(sizeof(KIf));
    p->head.tag = KIF;
    p->t = t;
    p->f = f;
    p->c = c;
    return (expr*)p;

}

expr* make_KApp(expr* es, expr* vs, expr* k){

    KApp *p = malloc(sizeof(KApp));
    p->es = es;
    p->vs = vs;
    p->k = k;
    return (expr*)p;

}








