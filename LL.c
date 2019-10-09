#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "LL.h"


// make Vcons and econs linked lists for the KApp structure?

expr* make_JNull(){

    JNull* p = (JNull*)malloc(sizeof(JNull));
    p->head.tag = JNULL;
    return p;

}

expr* make_JNum(int number) {

	JNum* p =(JNum*)malloc(sizeof(JNum));
	p->head.tag = JNUM;
	p->n = number;
	return p;

}

expr* make_JCons(expr* l, expr* r){

    JCons *p = (JCons*)malloc(sizeof(JCons));
    p->head.tag = JCONS;
    p -> left = l;
    p -> right = r;
    return p;
}

expr* make_JBool(bool boolean) {

	JBool* p = (JBool*)malloc(sizeof(JBool));
	p->head.tag = JBOOL;
	p->b = boolean;
	return p;

}

expr* make_JPrim(char prim) {

	JPrim* p = (JPrim*)malloc(sizeof(JPrim));
	p->head.tag = JPRIM;
	p->p = prim;
	return p;

}


expr* make_JIf(expr* c, expr* t, expr * f) {

	JIf *p = (JIf*)malloc(sizeof(JIf));
	p->head.tag = JIF;
	p->c = c;
	p->t = t;
	p->f = f;
	return p;

}


expr* make_JApp(expr* func, expr* args) {

	JApp *p = (JApp*)malloc(sizeof(JApp));
	p->head.tag = JAPP;
	p->func = func;
	p->args = args;
	return p;

}

expr* make_KRet(){

    KRet *p = (KRet*)malloc(sizeof(KRet));
    p->head.tag = KRET;
    return p;
}

expr* make_KIf(expr* c, expr* t, expr* f){

    KIf *p = (KIf*)malloc(sizeof(KIf));
    p->head.tag = KIF;
    p->t = t;
    p->f = f;
    p->c = c;
    return p;

}

expr* make_KApp(expr* rator, expr* es, expr* vs, expr* k){

    KApp *p = (KApp*)malloc(sizeof(KApp));
    p-> rator = rator;
    p->es = es;
    p->vs = vs;
    p->k = k;
    return p;

}


void eval(expr* oc){
    expr* oe = make_JNull();
    expr* ok = make_KRet();
    // does this insert and extract?
    while(1){
        switch(find_tag(oc)){
            // case 1
            case JIF:{
                JIf * c = (JIf *)oc;
                oc = c->c;
                ok = make_KIf(oe, c->t, c->f, ok);
                break;
            }
            case JAPP:{
                JApp *c = (JApp*)oc;
                oc = c->func;
                ok = make_KApp(NULL, make_JNull(), oe, c->args, ok);
                break;
                }
            case JNUM:
            case JPRIM:
            case JBOOL:
            case JNULL:
            // case 2 and 3
            case KIF:{
                KIf *k = (KIf*) ok;
                //oc =
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
                    vs = 1;//change
                }

            }
            case KRET:{
                return;
            }
        }
    }
}

Tag find_tag(expr *h){

    JNull* l = (JNull *) h;

    return l->head.tag;

}

JBool * find_bool(expr* c){

    c = 1;

}

int main(int argc, char * argv[]){
//testing
    JCons* x = make_JCons(make_JNum(5), make_JNull());
    JNum *y = x->left;
    printf("%d\n", y->n);
    //make it so that expr can be any of the types so that jcons can hold many things?
	printf("%d\n", (JNum*)(x->left)->n);
    return 0;
}




