class J1e(object):
   None

class C(object):
    None

class JNull(J1e):
    x = None

    def pp(self):
        print("None")
    def interp(self):
        return None
class JCons(J1e):

    left = None
    right = None

    def __init__(self, l, r):
        self.left = l
        self.right = r

    def pp(self):
        print(type(self.left.pp()))
        print(type(self.right.pp()))
        return "(" + self.left.pp() + self.right.pp() + ")"

    def interp(self):
        return JCons(self.left.interp(), self.right.interp())

class JPrim(J1e):
    p = None

    def __init__(self, prim):
        self.p = prim

    def pp(self):
        return self.p

    def interp(self):
        return self.p

class JBool(J1e):
    b = None

    def __init__(self, boolean):
        self.b = boolean

    def pp(self):
        return self.b

    def interp(self):
        return self.b

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

    def interp(self):
        condv = self.cond.interp()
        if type(condv) is JBool and condv.b == False:
            return self.fbr.interp()
        else:
            return self.tbr.interp()

class JApp(J1e):
    fun = None
    args = None

    def __init__(self, f, a):
        self.fun = f
        self.args = a

    def pp(self):
        return "@" + self.fun.pp() + self.args.pp()

    def interp(self):
        which_fun = self.fun.interp()
        arg_vals = self.arg.interp()

        if type(which_fun) is JPrim:
            p = which_fun.p
        else:
            print("error in JApp interp, fun p =" + which_fun)
            exit(1)
        lhs = arg_vals.lhs.p
        rhs = arg_vals.rhs.lhs.p

        if p == "+": return JNum(lhs + rhs)
        if p == "*": return JNum(lhs * rhs)
        if p == "/": return JNum(lhs / rhs)
        if p == "-": return JNum(lhs - rhs)
        if p == "<": return JBool(lhs < rhs)
        if p == ">": return JBool(lhs > rhs)
        if p == "<=": return JBool(lhs <= rhs)
        if p == ">=": return JBool(lhs >= rhs)
        if p == "==": return JBool(lhs == rhs)
        if p == "!=": return JBool(lhs != rhs)


class JNum(J1e):
    n = None
    def __init__(self, num):
        self.n = num
    
    def pp(self):
        return str(self.n)

    def interp(self):
        return int(self.n)

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


class CHole(C):
    h = None

    def __init__(self, h):
        self.h = h

    def plug(self, x):
        self.h = x

class CIf0(C):
    con = None
    e2 = None
    e3 = None

    def __init__(self, c, e2, e3):
        self.con = c
        self.e2 = e2
        self.e3 = e3

    def plug(self, x):
        self.con = x

class CIf1(C):
    e1 = None
    con = None
    e3 = None

    def __init__(self,  e1, c, e3):
        self.con = c
        self.e1 = e1
        self.e3 = e3

    def plug(self, x):
        self.con = x

class CIf2(C):
    e1 = None
    e2 = None
    con = None

    def __init__(self, e1, e2, c):
        self.con = c
        self.e2 = e2
        self.e1 = e1

    def plug(self, x):
        self.con = x

class Celist(C):
    #make this a tree/linked list type deal?
    con = None
    exp = None

    def __init__(self, l ,r):
        self.con = l
        self.exp = r

    def plug(self, x):
        # do not really know how to do this one
        con = x




# could add a lot to the desugarer but might not be time effiecient
def desug(se):

    if type(se) is Senum:
        return JNum(se.n)

    if type(se) is Sep and \
        type(se.left) is Sestr and \
        se.lhs.s == "+" and \
        se.right == None:
        return JNum(0)
    if type(se) is Sep and \
        se.left.s == "=" and \
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
    #if got down to here its bad news
    return JNum(666)


def length(se):
    
    if isNull(se.right):
        return 1
    elif not isNull(se.right):
        return 1 + length(se.right)

def first(se):
    return se.left

def second(se):
    if not isNull(se.right):
        return se.right.left
    else:
        print("Second function failed")
        exit()

def third(se):
    return se.right.right.left

def islist(se):
    if isNull(se):
        return True
    elif isCons(se):
        return islist(se.right)
    else:
        return False

def isCons(se):
    #if se == '-' or se == '+' or se == '*' or se == '/':
    if type(se) is Sep:
        return True
    else:
        return False


def isNull(se):
    if se == None:
        return True
    else:
        return False




def test():
    print(JCons(JPrim("-"), JNum("5")).pp())
    
if __name__ == "__main__":
    test()
    


