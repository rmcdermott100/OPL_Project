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
    JVAR,
    JFUNC,
    JDEF
} Tag ;

typedef enum {
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    LESS_THAN,
    GREATER_THAN,
    EQUAL,
    NOT_EQUAL,
    LESS_THAN_EQUAL,
    GREATER_THAN_EQUAL
}Prim;

typedef struct {
    Tag tag;
} expr;

typedef struct{
    expr head;
    char * v;
}JVar;
expr* make_JVar(char * v);

typedef struct{

    expr head;
    char * f;

}JFunc;
expr* make_JFunc(char * f);

typedef struct{

    expr head;
    expr* func;
    expr* vars;
    expr* e;
} JDef;
expr* make_JDef(expr* f, expr* v, expr* e);


typedef struct{

    expr head;

}JNull;
expr* make_JNull();

typedef struct {
    expr head;
    int n;

}JNum;
expr* make_JNum(int number);

typedef struct {

    expr head;
    expr *left;
    expr *right;

}JCons;

expr* make_JCons(expr* l, expr* r);

typedef struct {
    expr head;
    bool b;

} JBool;

expr* make_JBool(bool boolean);

typedef struct {
    expr head;
	Prim p;

} JPrim;

expr* make_JPrim(char prim);

typedef struct {

    expr head;
    expr *c, *t, *f;

} JIf;

expr* make_JIf(expr* c, expr* t, expr * f);

typedef struct {

    expr head;
	expr* func;
	expr* args;

} JApp;

expr* make_JApp(expr* func, expr* args);

typedef struct {

    expr head;

}KRet;
expr* make_KRet();

typedef struct {

    expr head;
    expr *t, *f, *c, *k;

}KIf;
expr* make_KIf(expr* c, expr* t, expr* f, expr* k);

typedef struct {

    expr head;
    expr *rator;
    expr *vs;
    expr *es;
    expr *k;

}KApp;
expr* make_KApp(expr* rator, expr* vs, expr* es, expr* k);

void pretty_printer(expr* p);
void free_list(expr* p);
expr *japp_remove_first(expr* vs);
expr* japp_return_first(expr* vs);
void japp_push(expr** vs, expr* p);
void eval(expr* oc);
Tag find_tag(expr *h);
bool j_false(expr* c);
int empty_list(expr* l);
Prim find_prim(expr* app);
expr* delta(expr* d);
expr* subst(expr* e, char* x, JNum *v);
void eval_state(expr* e, expr* k);









