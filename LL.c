#include <stdio.h>

enum tag {
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
};

typedef struct {
    enum tag;
} expr;

typedef struct {
    expr head;
    int n;

} JNum;

typedef struct{
    expr head;
    bool b;

} JBool;

typedef struct{
    expr head;
    char p

} JPrim;

typedef struct{

    expr head;
    expr *c, *t, *f;

} JIF;

typedef struct{

    expr head;
	expr* func, * args;

} JApp;


