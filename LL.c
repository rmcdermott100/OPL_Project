#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "LL.h"


// make Vcons and econs linked lists for the KApp structure?

expr* make_JNull(){

    JNull* p = (JNull*)malloc(sizeof(JNull));
    p->head.tag = JNULL;
    return (expr*) p;

}

expr* make_JNum(int number) {

	JNum* p =(JNum*)malloc(sizeof(JNum));
	p->head.tag = JNUM;
	p->n = number;
	return (expr*)p;

}

expr* make_JCons(expr* l, expr* r){

    JCons *p = (JCons*)malloc(sizeof(JCons));
    p->head.tag = JCONS;
    p -> left = l;
    p -> right = r;
    return (expr*)p;
}

expr* make_JBool(bool boolean) {

	JBool* p = (JBool*)malloc(sizeof(JBool));
	p->head.tag = JBOOL;
	p->b = boolean;
	return (expr*)p;

}

expr* make_JPrim(char prim) {

	JPrim* p = (JPrim*)malloc(sizeof(JPrim));
	p->head.tag = JPRIM;
	p->p = prim;
	return (expr*)p;

}


expr* make_JIf(expr* c, expr* t, expr * f) {

	JIf *p = (JIf*)malloc(sizeof(JIf));
	p->head.tag = JIF;
	p->c = c;
	p->t = t;
	p->f = f;
	return (expr*)p;

}


expr* make_JApp(expr* func, expr* args) {

	JApp *p = (JApp*)malloc(sizeof(JApp));
	p->head.tag = JAPP;
	p->func = func;
	p->args = args;
	return (expr*)p;

}

expr* make_KRet(){

    KRet *p = (KRet*)malloc(sizeof(KRet));
    p->head.tag = KRET;
    return (expr*)p;
}

expr* make_KIf(expr* c, expr* t, expr* f, expr* k){

    KIf *p = (KIf*)malloc(sizeof(KIf));
    p->head.tag = KIF;
    p->t = t;
    p->f = f;
    p->c = c;
    p->k = k;
    return (expr*)p;

}

expr* make_KApp(expr* rator, expr* es, expr* vs, expr* k){

    KApp *p = (KApp*)malloc(sizeof(KApp));
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
            //values we switch onto what the continuation is
            case JCONS:{

            }
            case JNUM:
            case JPRIM:
            case JBOOL:
            case JNULL:{
                switch(find_tag(ok)){
                    case KRET:{
                        return;
                    }
                    case KIF:{
                        KIf *k = (KIf*) ok;
                        oc = (j_false(oc)) ? k->t : k->f;
                        oe = k->c;
                        ok = k->k;
                        break;
                    }
                    case KAPP:{
                        KApp* ka = (KApp*) ok;
                        expr* ratorp = ka -> rator;
                        expr* vs = ka -> vs;
                        if(!ratorp){
                            ratorp = oc;
                        }else{
                            vs = make_JCons(oc, vs);
                        }
                        // maybe make es and vs vectors instead of linked list
                        if(empty_list(ka->es)){
                            // rule 6
                            // oe = delta(ka->vs), ek = k
                        }else{
                            // rule 5, take first value in es and put at end of vs
                            JCons* tmp = ka->es;
                            ka = tmp -> right;
                            oe = tmp -> left;
                            // run delta function on the e i just popped to add to value list?
                            //ok = make_KApp(vs,ka);
                        }
                    }
                }
            }
        }
    }
}

Tag find_tag(expr *h){

    return h->tag;

}

Prim find_prim(expr* app){
    JApp * papp = (JApp*) app;
    JPrim * Jp = papp->func;
    return Jp->p;
}

bool j_false(expr* c){

    JIf *m = (JIf*) c;
    JBool* boolean = (JBool*)m->c;
    if(boolean -> b = true){
        return true;
    }else{
        return false;
    }
}

int empty_list(expr* l){
    JCons * tmp = (JCons*) l;
    if (tmp -> left == NULL && tmp -> right == NULL || tmp->head.tag == JNULL){
        return true;
    }else{
        return false;
    }
    return 0;

}

void japp_push(JCons** vs, expr* p){
    JCons* tmp = make_JCons(p,vs);
    *vs = tmp;
}

expr* japp_pop(expr* vs){

    JCons* tmp = vs;
    expr* result = tmp->left;
    vs = tmp->right;
    free_list(tmp);
    return result;
}

void free_list(JCons* p){
    switch(find_tag(p)){
        case JNULL:
        case JNUM:
        case JBOOL:
        case JPRIM:{
            free(p);
        }
        case JCONS:{
            JCons* tmp = (JCons*)p;
            free_list(tmp->left);
            free_list(tmp->right);
        }
    }
    free(p);
}


void pretty_printer(expr* p){
    switch(find_tag(p)){

        case JNUM:{
            JNum* pp = (JNum*)p;
            printf("%d\n", pp->n);
            break;
        }
        case JBOOL:{
            JBool *pp = (JBool*)p;
            printf("%s\n", pp->b ? "true" : "false");
            break;
        }
        case JPRIM:{
            JPrim* pp = (JPrim*)p;
            printf("%c\n", pp->p);
            break;
        }
        case JNULL:{
            JNull* pp = (JNull*)p;
            printf("NULL\n");
            break;
        }
    }

}





// write delta function for values
// remember delta function is backwards

int delta(expr* d){

    switch(find_tag(d)){
        case JNUM:{
            JNum * x = (JNum*)d;
            return x->n;
        }
        case JBOOL:{
            JBool * x = (JBool*) d;
            return x->b;
        }
        case JAPP:{
            //looks to see what the JPrim is
            JApp *x = (JApp*)d;
            switch(find_prim(d)){
                case ADD:{
                    // add together the args, make d-> right jcons then add the values
                    expr *z = japp_pop(x);

                    expr *y = japp_pop(x);

                    return delta(z) + delta(y);
                }
                case SUBTRACT:{

                }
                case MULTIPLY:{

                }
                case DIVIDE:{

                }
            }
        }
    }

}


int main(int argc, char * argv[]){
//testing

	JCons* t = make_JCons(make_JNum(3), make_JNull());
	JCons* l = make_JCons(make_JNum(7), make_JNull());
    japp_push(&t, l);
    Prim tmp = ADD;
    JCons* b = japp_pop(t);
    //works
    JNum *c = b->left;
    pretty_printer(c);


    //delta(t);
    //pretty_printer(delta(v));
    return 0;
}




