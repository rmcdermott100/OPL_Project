#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "LL.h"

Env* env;

expr* make_Env(JDef* y, expr* z){

    Env* p = (Env*)malloc(sizeof(Env));
    p -> def = y;
    p -> next = z;
    return (Env*)p;

}

expr* make_JVar(char* v){

    JVar* p = (JVar*)malloc(sizeof(JVar));
    p->head.tag = JVAR;
    p->v = v;
    return (expr*)p;
}

expr* make_JFunc(char* f){

    JFunc* p = (JFunc*)malloc(sizeof(JFunc));
    p->head.tag = JFUNC;
    p->f = f;
    return (expr*)p;

}

expr* make_JDef(expr *f, expr* v, expr* e){

    JDef * p = malloc(sizeof(JDef));
    p->head.tag = JDEF;
    p->name = f;
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

expr* make_Lambda(char* name, expr* v, expr* e){

    Lambda * p = (Lambda*)malloc(sizeof(Lambda));
    p ->head.tag = LAMBDA;
    p->name = name;
    p->vars = v;
    p->e = e;
    return (expr*)p;

}

expr* make_Closure(expr* l, expr* env){

    Closure * p = (Closure*)malloc(sizeof(Closure));
    p -> head.tag = CLOSURE;
    p -> lam = l;
    p -> env = env;
    return (expr*)p;

}


void eval(expr* oc){
    expr* oe = make_JNull();
    expr* ok = make_KRet();
    // does this insert and extract?
    while(1){
        //find tag of ok is not working second pass by beacuase of make_KApp functions???
        // KApp struct and make function wrong?

        eval_state(oc, ok);

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
                ok = make_KApp(c->func, make_JNull(), c->args, ok);

                break;
                }
            //values we switch onto what the continuation is

            case JNUM:
            case JPRIM:
            case JBOOL:
            case JVAR:
            case JNULL:{
                switch(find_tag(ok)){
                    case KRET:{

                        pretty_printer(oc);
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
                        // how if J4 different from J3?? only the name??
                        KApp* ka = (KApp*) ok;
                        expr* ratorp = ka -> rator;
                        expr* vs = ka -> vs;
                        /*if(!ratorp){
                            ratorp = oc;
                        }*/
                        if(empty_list(ka->es)){

                            JCons * temp2 = (JCons *) ka -> vs;

                            if(find_tag(temp2->left) == LAMBDA){

                                Lambda * lam = temp2 -> left;
                                //make a define of the function name?
                                JCons * vals = temp2 -> right;
                                //find definition

                                Env* temp_env = env;
                                //JDef* def = lam -> e;

                                //look in environment for the function definition
                                /*
                                while(find_tag(temp_env) != JNULL){
                                    if(!(strcmp(jfunc -> f, def -> name))){

                                        def = temp_env -> def;
                                        break;
                                    }else{
                                        temp_env = temp_env -> next;
                                    }
                                }
                                */
                                //def = lam -> e;
                                if(find_tag(temp_env) == JNULL || temp_env == NULL){
                                    printf("fail");
                                    exit(1);
                                }
                                JCons* vars = lam -> vars;
                                while(find_tag(vars) != JNULL){


                                    JVar * var = vars -> left;
                                    lam -> e = subst(lam->e, var -> v, japp_return_first(vals));
                                    vals = vals -> right;
                                    vars = vars -> right;

                                }

                                ka -> vs = vals;

                                japp_push(&ka->es, lam -> e);
                                ok = ka;
                                // finish this part then it works?
                                break;

                            }else{

                                japp_push(&vs, ratorp);
                                JNum *d = delta(vs);
                                oe = d;
                                oc = d;

                                if(find_tag(ka -> k) == KAPP){

                                    KApp * m = (KApp*) ka ->k;
                                    japp_push(&m ->es, d);
                                }
                                //pretty_printer(d);
                                japp_push(&ka ->es, d);
                                ok = ka -> k;
                                break;
                            }

                        }else{

                            JCons* tmp = ka->es;

                            if (find_tag(tmp -> left) == JNUM || find_tag(tmp -> left) == LAMBDA){

                                ka -> es = tmp -> right;
                                oe = japp_return_first(tmp);
                                tmp = japp_remove_first(tmp);
                                vs = japp_add_end(vs, oe);

                                ka -> vs = vs;

                                ka -> es = tmp;
                                break;
                            }else{

                                oc = tmp->left;
                                ka -> es = japp_remove_first(ka ->es);
                                ok = ka;
                                break;

                            }
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
    JNum * num = (JNum*) m;
    //JBool* boolean = (JBool*)m;
    if(num -> n > 0){
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

void eval_state(expr* e, expr* k){

    switch(find_tag(e)){
        case JNUM:{
            printf("(JNUM ");
            break;
        }
        case JIF:{
            printf("(JIF ");
            break;
        }
        case JAPP:{
            printf("(JAPP ");
            break;
        }
        case JPRIM:{
            printf("(JPRIM ");
            break;
        }
        case JNULL:{
            printf("(JNULL ");
            break;
        }
        case JBOOL:{
            printf("(JBOOL ");
            break;
        }
        case JCONS:{
            printf("(JCONS ");
            break;
        }
    }
    switch(find_tag(k)){
        case KAPP:{
            printf("KAPP) \n");
            break;
        }
        case KIF:{
            printf("KIF) \n");
            break;
        }
        case KRET:{
            printf("KRET) \n");
            break;
        }

    }
}

void japp_push(expr** vs, expr* p){
    //should push on to end of list
    //JNum* l  = (JNum*) p;
    JCons *tmp = *vs;
    JNull* x = make_JNull();
    if (find_tag(*vs) == JNULL){
        tmp = make_JCons(p, x);
    }else{
        
        tmp = make_JCons(p,*vs);
    }
    *vs = tmp;


}

expr* japp_add_end(expr* vs, expr* p){
    JCons* tmp = vs;
    JCons* tmp2 = vs;
    JNull* x = make_JNull();
    if (find_tag(vs) == JNULL){
        //printf("empty list");
        tmp = make_JCons(p, x);
    }else{
        while(find_tag(tmp2->right) != JNULL){
            tmp2 = tmp2 -> right;
        }
        tmp2 -> right = make_JCons(p, x);
    }

    return tmp;
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
            printf("JNULL\n");
            break;
        }
		case JCONS:{
            JCons* pp = (JCons*)p;
            printf("JCONS start\n");
            while(find_tag(pp) != JNULL){
                pretty_printer(pp->left);
                pp = pp->right;
            }
            printf("JCONS End\n");
            break;
        }
        case JAPP:{
            JApp* pp = (JApp*) p;
            printf("func = ");
            pretty_printer(pp->func);
            printf("args = ");
            pretty_printer(pp->args);
            break;
        }
        case JFUNC:{
            JFunc* pp = (JFunc*) p;
            printf("JFUNC %s\n", pp->f);
            break;
        }
        case JVAR:{
            JVar* pp = (JVar*)p;
            printf("JVAR %s\n", pp->v);
            break;
        }
    }

}






expr* delta(expr* d){

    switch(find_tag(d)){
        case JPRIM:{
            JPrim* x = (JPrim *)d;
            return x;
        }
        case JNULL:{
            JNull* x = (JNull *)d;
            return 0;
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
        case JNULL:{
            return e;
        }
        case JVAR:{
            JVar * temp = (JVar*) e;
            if (strcmp(temp->v, x)){

                return e;
            }else{

                return (JNum*)v;
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
            temp -> left = subst(temp -> left, x,v);

            temp -> right = subst(temp -> right, x,v);
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

void test(void){

    JFunc* Test = make_JFunc("Add1");

    JVar* var = make_JVar("test");
    JCons* var_list = make_JCons(var, make_JNull());
    JApp * e = make_JApp(make_JPrim(ADD), make_JCons(var, make_JCons(make_JNum(1), make_JNull())));
    Lambda * l1 = make_Lambda("hello", var_list, e);
    JDef * def = make_JDef("Add1", var_list, e);
    env = make_Env(def, make_JNull());
    JApp* q = make_JApp(make_JPrim(ADD), make_JCons(make_JNum(3), make_JCons(make_JNum(7), make_JNull())));
    JApp* func_test = make_JApp(make_JPrim(ADD), make_JCons(l1, make_JCons(make_JNum(0),
    make_JCons( make_JNum(1), make_JNull()))));
    JApp* v = make_JApp(make_JPrim(ADD), make_JCons(q, make_JCons(make_JNum(3), make_JNull())));

    // test cek on lambdas
    //Lambda * l1 = make_Lambda(var, e);


    eval(func_test);

}



int main(int argc, char * argv[]){
    test();
    return 0;
}





