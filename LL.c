#include <stdio.h>
#include <stdbool.h>
#include "LL.h"


// make Vcons and econs linked lists for the KApp structure?

expr* make_JNull(){

    JNull* p = malloc(sizeof(JNull));
    p->head.tag = JNULL;
    return p;

}

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

expr* make_KRet(){

    KRet *p = malloc(sizeof(KRet));
    p->head.tag = KRET;
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

expr* make_KApp(expr rator, expr* es, expr* vs, expr* k){

    KApp *p = malloc(sizeof(KApp));
    p-> rator = rator;
    p->es = es;
    p->vs = vs;
    p->k = k;
    return (expr*)p;

}


void eval(expr* oc){
    expr* oe = make_JNull();
    expr* ok = make_KRet();
    // does this insert and extract?
    while(1){
        switch(find_tag(oc)){
            // each case updates e and k, the old k gets remembered
            case JIF:{
                JIf * c = (JIf *)oc;
                oc = c->c;
                ok = make_KIf(oe, c->t, c->f, ok);
                break;
            }
            case JAPP:{
                JApp * c = (JApp*)oc;
                oc = c->func;
                ok = make_KApp(NULL, make_JNull(), oe, c->args, ok);
                break;
                }
            case JNUM:
            case JPRIM:
            case JBOOL:
            case JNULL:
            case KIF:{
                KIf *k = (KIf*) ok;
                //check if it is true or false
            }
            case KAPP:{
                KApp* ka = (KApp*) ok;
                expr* ratorp = ka -> rator;
                expr* vs = ka -> vs;
                break;
                // if there is no operator then ???
                if(!ratorp){
                    ratorp = oc;
                }else{

                }

            }
            case KRET:{
                return;
            }

        }


    }

}

expr * find_tag(expr *h){

    return (JNull*)h -> head.tag;

}






