#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "LL.h"



expr* make_JVar(char* v){

    JVar* p = (JVar*)malloc(sizeof(JVar));
    p->head.tag = JVAR;
    p->v = v;
    return (expr*)v;
}

expr* make_Jfunc(char* f){

    JFunc* p = (JFunc*)malloc(sizeof(JFunc));
    p->head.tag = JDEF;
    p->f = f;
    return (expr*)p;

}

expr* make_JDef(expr *f, expr* v, expr* e){

    JDef * p = malloc(sizeof(JDef));
    p->head.tag = JDEF;
    p->func = f;
    p->vars = v;
    p->e = e;
    return (expr*)p;

}

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

expr* make_KApp(expr* rator, expr* vs, expr* es, expr* k){

    KApp *p = (KApp*)malloc(sizeof(KApp));
    p->head.tag = KAPP;
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
        //find tag of ok is not working second pass by beacuase of make_KApp functions???
        // KApp struct and make function wrong?

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
                ok = make_KApp(NULL, make_JNull(), c->args, ok);

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
                        }
                        if(empty_list(ka->es)){

                            JCons * temp2 = (JCons *) ka -> vs;

                            if(find_tag(temp2->left) == JDEF){
                                //subs the vars in the def, and return the expression of the function?
                                JDef * def = temp2 -> left;
                                JCons * vals = temp2 -> right;
                                //while loop that repeats until one of the lists are empty?
                                //should contain equal # of values and variables
                                while(find_tag(vals) != JNULL){
                                    def -> e = subst(def->e, japp_return_first(def->vars), japp_return_first(vals));
                                    vals = japp_remove_first(vals);
                                    def->vars = japp_remove_first(def->vars);
                                }
                                // remake japp with just the expression?
                                // finish this part then it works?
                                

                            }else{

                                japp_push(&vs, ratorp);
                                JNum *d = delta(vs);
                                pretty_printer(d);
                                oc = d;
                                //shouldnt need this kret, but idk how to pop if off after i do the work?
                                ok = make_KRet();
                            }

                        }else{

                            JCons* tmp = ka->es;
                            ka -> es = tmp -> right;
                            oe = japp_return_first(tmp);
                            tmp = japp_remove_first(tmp);

                            japp_push(&vs, delta(oe));
                            ok = make_KApp(ratorp, vs, tmp, ok);
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
    JPrim * Jp = (JPrim*) app;
    return Jp->p;
}

bool j_false(expr* c){

    JIf *m = (JIf*) c;
    JBool* boolean = (JBool*)m->c;
    if(boolean -> b == true){
        return true;
    }else{
        return false;
    }
}

int empty_list(expr* l){
    JCons * tmp = (JCons*) l;
    if (tmp == NULL || tmp->head.tag == JNULL){
        return true;
    }else{
        return false;
    }
    return 0;

}

void japp_push(expr** vs, expr* p){
    JNum* l  = (JNum*) p;
    JCons *tmp = *vs;
    JNull* x = make_JNull();
    if (find_tag(*vs) == JNULL){
        tmp = make_JCons(l, x);
    }else{
        tmp = make_JCons(l,*vs);
    }
    *vs = tmp;
}
// Return first and remove first combined is pop function
expr* japp_return_first(expr* vs){
    JCons* tmp = (JCons*)vs;
    return tmp->left;
}

expr* japp_remove_first(expr* vs){

    JCons* tmp = (JCons*)vs;
    //expr* result = tmp->left;
    vs = tmp -> right;
    free(tmp);
    return (expr*)vs;
}




void pretty_printer(expr* p){
    switch(find_tag(p)){

        case JNUM:{
            JNum* pp = (JNum*)p;
            printf("jnum %d\n", pp->n);
            break;
        }
        case JBOOL:{
            JBool *pp = (JBool*)p;
            printf("jbool %s\n", pp->b ? "true" : "false");
            break;
        }
        case JPRIM:{
            JPrim* pp = (JPrim*)p;
            printf("jprim %d\n", pp->p);
            break;
        }
        case JNULL:{
            JNull* pp = (JNull*)p;
            printf("NULL\n");
            break;
        }case JCONS:{
            JCons* pp = (JCons*)p;
            printf("JCONS start\n");
            while(find_tag(pp->right) != JNULL){
                pretty_printer(pp->left);
                pp = pp->right;
            }
            printf("JCONS End\n");
        }
    }

}





// write delta function for values
// remember delta function is backwards

expr* delta(expr* d){

    switch(find_tag(d)){
        case JPRIM:{
            JPrim* x = (JPrim *)d;
            return x;
        }
        case JNULL:{
            JNull* x = (JNull *)d;
            return x;
        }
        case JNUM:{
            JNum * x = (JNum*)d;
            return x;
        }
        case JBOOL:{
            JBool * x = (JBool*) d;
            return x;
        }
        case JIF:{

        }
        case JCONS:{
            JCons* q = (JCons*)d;
            JPrim * p = q->left;
            switch(find_prim(p)){

                case ADD:{

                    int total = 0;
                    q = japp_remove_first(q);

                    while(find_tag(q) != JNULL){

                        JNum* tmp = japp_return_first(q);
                        q = japp_remove_first(q);
                        total+=tmp->n;
                    }
                    return make_JNum(total);
                }
            }
        }
        case JAPP:{
            //looks to see what the JPrim is
            JApp *q = (JApp*)d;
            switch(find_prim(q->func)){
                case ADD:{
                    // add together the args, make d-> right jcons then add the values
                    expr *z = japp_return_first(q->args);
                    q->args = japp_remove_first(q->args);
                    expr *y = japp_return_first(q->args);
                    q->args = japp_remove_first(q->args);
                    JNum * tmp1 = delta(z);
                    JNum * tmp2 = delta(y);
                    return make_JNum(tmp1->n + tmp2->n);
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

//
expr* subst(expr* e, char* x, JNum *v){
    //depending on the expression substitute differently
    switch(find_tag(e)){
        case JVAR:{
            JVar * temp = (JVar*) e;
            if (strcmp(temp->v, x)){
                return e;
            }else{
                return v;
            }
        }
        case JIF:{
            //sub each element of jif
            JIf* temp = (JIf*) e;
            JIf* l = make_JIf(subst(temp->c, x,v), subst(temp->t, x,v), subst(temp->f, x,v));
            return l;
        }
        case JCONS:{
            JCons * temp = (JCons*) e;
            temp = subst(temp -> left, x,v);
            temp = subst(temp -> right, x,v);
            return temp;
        }
        case JAPP:{
            JApp* temp = (JApp*) e;
            temp->args = subst(temp->args, x,v);
            return temp;
        }
        case JDEF:{
            JDef * temp = (JDef*) e;
            temp -> e = subst(temp->e, x,v);
            return temp;
        }
        default:{
            //these should not have any variables in them
            return e;
        }
    }

}




int main(int argc, char * argv[]){
//testing

	JCons* t = make_JCons(make_JNum(3), make_JNull());
	JNum* l = make_JNum(7);
    japp_push(&t, l);

    Prim* tmp = make_JPrim(ADD);
    japp_push(&t, tmp);

    //pretty_printer(delta(t));
    //works
    JApp* v = make_JApp(tmp, t);

    //JCons *r = t->right;
    //pretty_printer(r->left);

    eval(v);
    //printf("%d\n",find_tag(v));
    //pretty_printer(v);

    return 0;
}





