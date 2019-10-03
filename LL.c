#include <stdio.h>
#include <stdbool.h>

typedef enum {
    JNULL,
    JIF,
    JNUM,
    JAPP,
    JBOOL,
    JPRIM,
    KRET,
    KIF,
    KAPP,
    JCONS,
} Tag ;

typedef struct {
    enum Tag tag;
} expr;

typedef struct {
    expr head;
    int n;

} JNum;

expr* make_JNum(int number) {

	JNum* p = malloc(sizeof(JNum));
	p->head.tag = JNUM;
	p->n = number;
	return p;

}

typedef struct{
    expr head;
    bool b;

} JBool;

expr* make_JBool(bool boolean) {

	JBool* p = malloc(sizeof(JBool));
	p->head.tag = JBOOL;
	p->b = boolean;
	return p;

}

typedef struct{
    expr head;
	char p;

} JPrim;

expr* make_JPrim(char prim) {

	JPrim* p = malloc(sizeof(JPrim));
	p->head.tag = JPRIM;
	p->p = prim;
	return p;

}

typedef struct{

    expr head;
    expr *c, *t, *f;

} JIf;

expr* make_JIf(expr* c, expr* t, expr * f) {

	JIf *p = malloc(sizeof(JIf));
	p->head.tag = JIF;
	p->c = c;
	p->t = t;
	p->f = f;
	return p;

}

typedef struct{

    expr head;
	expr* func;
	expr* args;

} JApp;

expr* make_JApp(expr* func, expr* args) {

	JApp *p = malloc(sizeof(JApp));
	p->head.tag = JAPP;
	p->func = func;
	p->args = args;
	return p;

}