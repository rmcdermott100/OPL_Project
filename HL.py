import os
from subprocess import call
import time

class J1e(object):
   None

class C(object):
    None

class E(object):
    None

class Lambda(J1e):

    vars = None
    e = None
    name = None

    def __init__(self, n, v, e):
        self.name = n
        self.vars = v
        self.e = e


class JVar(J1e): # start with lowercase letter
    var = None # name of functions

    def __init__(self,v):
        self.var = v

    def pp(self):
        return self.var

    def subst(self, x, v):
        if self.var == x:
            return v
        else:
            return self

class JFunc(J1e): # should make a dict of functions
    func = None

    def __init__(self, f):
        self.func = f

    def pp(self):
        return self.func

class JDef():
    func = None
    vars = []
    e = None

    def __init__(self,f,v,e):
        self.func = f
        self.vars = v
        self.e = e

    def subst(self,x,v):

        self.e.subst(x,v)

class JNull(J1e):
    x = None

    def pp(self):
        return "NULL"

    def subst(self,x,v):
        return

class JCons(J1e):

    left = None
    right = None

    def __init__(self, l, r):
        self.left = l
        self.right = r

    def pp(self):
        return "(" + self.left.pp() + self.right.pp() + ")"

    def subst(self,x,v):
        self.left.subst(x,v)
        self.right.subst(x,v)

class JPrim(J1e):
    p = None

    def __init__(self, prim):
        self.p = prim

    def pp(self):
        return ""+self.p

    def subst(self,x,v):
        None

class JBool(J1e):
    b = None

    def __init__(self, boolean):
        self.b = boolean

    def pp(self):
        return ""+self.b

    def subst(self,x,v):
        None

class JIf(J1e):
    cond = None
    tbr = None
    fbr = None

    def __init__(self, c, t, f):
        self.cond = c
        self.tbr = t
        self.fbr = f

    def pp(self):
        return "if" + self.cond.pp() + self.tbr.pp() + self.fbr.pp()

    def subst(self,x,v):
        self.cond.subst(x,v)
        self.tbr.subst(x,v)
        self.fbr.subst(x,v)


class JApp(J1e):
    fun = None
    args = None

    def __init__(self, f, a):
        self.fun = f
        self.args = a

    def pp(self):
        return "@" + self.fun.pp() + self.args.pp()

    def subst(self,x,v):
        self.args.subst(x,v)

class JNum(J1e):
    n = None
    def __init__(self, num):
        self.n = num
    
    def pp(self):
        return str(self.n)

    def interp(self):
        return int(self.n)

    def subst(self,x,v):
        None


class case:
    #? what is this
    None

class unit:
    #? what is this?
    None

class pair:
    left = None
    right = None

    def __init__(self, l, r):
        self.left = l
        self.right = r

class inl:
    value = None

    def __init__(self, v):
        self.value=v

class inr:
    value = None

    def __init__(self, v):
        self.value=v

class Se(object):
    None

class Sep(Se):  
    left = None
    Right = None
    
    def __init__(self, l, r):
        self.left = l
        self.right = r

class Sestr(Se):
    s = None
    def __init__(self, s):
        self.s = str(s)

class Senum(Se):
    n = None
    def __init__(self, n):
        self.n = int(n)

class Semt(Se):
    None

def JA(l, r):
    return JApp(JPrim("+"), JCons(l, JCons(r, None)))

def JM(l, r):
    return JApp(JPrim("*"), JCons(l, JCons(r, None)))


class EHole(E):
    h = None

    def __init__(self):
        h = None

    def plug(self, x):
        self.h = x

class EIf(E):

    con = None
    e2 = None
    e3 = None

    def __init__(self, c, e2, e3):
        self.con = c
        self.e2 = e2
        self.e3 = e3

    def plug(self, x):
        self.con = JIf(self.cond.plug(x), self.e2, self.e3)


class Elist(E):
    #make this a tree/linked list type deal?
    vs = []
    h = None
    es = []

    def __init__(self, l, h, r):
        self.vs = l
        self.h = h
        self.es = r

    def plug(self, x):
        # do not really know how to do this one
        self.left = JApp(self.vs, self.h.plug(x), self.es)






def step(e):

    cp, ep = find_redex(e)
    if ep == None:
        return e

    if type(cp) is EHole:
        cp.plug(ep.interp())
        e = cp.h

    #turn into CList
    elif type(cp) is EHole:
        cp.plug(ep.interp())
        e = cp.h

    elif type(cp) is EIf:
        cp.plug(step(ep))
        e = cp.con

    e = step(e)
    return e

def find_redex(e):

    if type(e) is JIf:
        if type(e.cond) is JPrim or type(e.cond) is JNum or type(e.cond) is JBool:
            return EHole(), e
        else:
            cp, ep = find_redex(e.cond)
            return EIf(cp, e.tbr, e.fbr), ep
    if type(e) is JApp:
        # look at the first thing that is not a value
        if type(e.fun) is JBool or type(e.fun) is JPrim or type(e.fun) is JNum:
            #retunr CList
            return EHole(), e
        else:
            # go deeper into the JApp???, is that possible?
            cp, ep = find_redex(e.args)
    if type(e) is JCons:
        if type(e.left) is JBool or type(e.left) is JPrim or type(e.left) is JNum:
            return EHole(), e
        else:
            cp, ep = find_redex(e.right)

    if type(e) is JPrim or type(e) is JNum or type(e) is JBool:
        # do nothing? or failure
        return None, None

    return None, None
    # return None on failure? for step function.


# could add a lot to the desugarer but might not be time effiecient, especially if it gets changed anyway
def desug(se):

    if type(se) is Senum:
        return JNum(se.n)

    if type(se) is Sep and \
        type(se.left) is Sestr and \
        se.lhs.s == "+" and \
        se.right == None:
        return JNum(0)
    if type(se) is Sep and \
        se.left.s == "+" and \
        type(se.right) is Sep:
        return JA(desug(se.right.left), desug(Sep(se.left, se.right.right)))
    if type(se) is Sep and \
        type(se.left) is Sestr and \
        se.left.s == "*" and \
        se.right == None :
        return JNum(1)
    if type(se) is Sep and \
        type(se.left) is Sestr and \
        se.left.s == "*" and \
        type(se.right) is Sep:
        return JM(desug(se.right.left), Sep(se.left, se.right.right))
    if type(se) is Sep and \
        type(se.left) is Sestr and \
        se.left.s == "-" and \
        type(se.right) is Sep and \
        se.right.right == None:
        return JM(JNum(-1), desug(se.right.left))
    if type(se) is Sep and \
        type(se.left) is Sestr and \
        type(se.right) is Sep and \
        type(se.right.right) is Sep and \
        se.right.right.right == None:
        return JApp(JPrim(se.left.s), Sep(desug(se.right.left), Sep(se.right.right.left, None)))
    if type(se) is Sep and \
        type(se.left) is Sestr and \
        se.left.s == "if" and \
        type(se.right) is Sep and \
        type(se.right.right) is Sep and \
        type(se.right.right.right) is Sep and \
        se.right.right.right.right == None:
        return JIf(desug(se.right.left), desug(se.right.right.left), desug(se.right.right.right.left))

    if type(se)is Sep and \
        type(se.left) is Sestr and \
        se.left.s == "let" and \
        type(se.right) is Sep and\
        type(se.right.right) is Sep and \
        type(se.right.right.right.right.right) is Sep:
        return JCons(Lambda(se.right.left.s, se.right.left, se.right.right.right.right.right.left),JCons(se.right.right.right.left,JNull()))

    if type(se)is Sep and \
        type(se.left) is Sestr and \
        se.left.s == "let" and \
        type(se.right) is Sep and\
        type(se.right.left) is Sestr and \
        se.right.left.s == "rec" and \
        type(se.right.right) is Sep and \
        type(se.right.right.right.right.right) is Sep:
        return JCons(Lambda("rec", se.right.left, se.right.right.right.right.right.left),JCons(se.right.right.right.left,JNull()))


    #if got down to here its bad news
    return JNum(666)

class st():

    e = None
    E = None

    def __init__(self, e, E):
        self.e = e
        self.E = E



def isNull(se):
    if se == None:
        return True
    else:
        return False




def J5test():
    # desugar J3 classes, because the HL isnt connected to the LL and print them out to write the tests??

    None



def emit_LL():
    f = open("x.c", "w")
    f.write("#include <stdio.h> \n")
    f.write("#include \"LL.h\"\n\n")
    f.write("int main(int argc, char * argv[]) {\n")
    f.write("JVar * var = make_JVar(\"test\");\n")
    f.write("JCons * var_list = make_JCons(var, make_JNull());\n")
    f.write("JApp * e = make_JApp(make_JPrim(ADD), make_JCons(var, make_JCons(make_JNum(1), make_JNull())));\n")
    f.write("Lambda * l1 = make_Lambda(\"hello\", var_list, e);\n")
    f.write("JDef *def = make_JDef(\"Add1\", var_list, e);\n")
    f.write("JApp * q = make_JApp(make_JPrim(ADD), make_JCons(make_JNum(3), make_JCons(make_JNum(7), make_JNull())));\n")
    f.write("JApp * func_test = make_JApp(make_JPrim(ADD), make_JCons(l1, make_JCons(make_JNum(0),make_JCons(make_JNum(1), make_JNull()))));\n")
    f.write("JApp * v = make_JApp(make_JPrim(ADD), make_JCons(q, make_JCons(make_JNum(3), make_JNull())));\n")

    f.write("\teval(func_test);\n")
    f.write("\treturn 0;\n")
    f.write("}")
    f.close()

    call(["gcc", "-w", os.path.abspath("x.c"), os.path.abspath("LL.c"), "-o", "x"])
    time.sleep(1)
    call([os.path.abspath("x")])


if __name__ == "__main__":
    #test()
    emit_LL()




