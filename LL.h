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

typedef enum {



}Prim;

typedef struct {
    enum Tag tag;
} expr;

typedef struct {
    enum Tag tag
}K;

typedef struct {
    expr head;
    int n;

} JNum;

expr* make_JNum(int number);

typedef struct{
    expr head;
    bool b;

} JBool;

expr* make_JBool(bool boolean);

typedef struct{
    expr head;
	char p;

} JPrim;

expr* make_JPrim(char prim);

typedef struct{

    expr head;
    expr *c, *t, *f;

} JIf;

expr* make_JIf(expr* c, expr* t, expr * f);

typedef struct{

    expr head;
	expr* func;
	expr* args;

} JApp;

expr* make_JApp(expr* func, expr* args);

typedef struct {

    expr head;
    expr ret;

}KRet;


typedef struct{

    expr head;
    expr *t, *f, *c;

}KIf;


typedef struct{

    expr head;
    expr *vs;
    expr *es;
    expr k;

}KApp;