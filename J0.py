class J1e(object):
   None

class JNull(J1e):
    x = None

    def pp(self):
        print("None")

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

class JPrim(J1e):
    p = None

    def __init__(self, prim):
        self.p = prim

    def pp(self):
        return self.p

class JBool(J1e):
    b = None

    def __init__(self, boolean):
        self.b = boolean

    def pp(self):
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

class JApp(J1e):
    fun = None
    args = None

    def __init__(self, f, a):
        self.fun = f
        self.args = a

    def pp(self):
        return "@" + self.fun.pp() + self.args.pp()

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

class Semt(Se):
    None




def d(se):

    if type(se) is str:
        return JNum(se)

    if islist(se) and length(se) == 2 and first(se) == "-":
        None
        #return JMult(JNum(-1), JNum(second(se)))

    elif islist(se) and length(se) == 3 and first(se) == '-':
        None
        #return JAdd(d(second(se)), d(Sep("-", (Sep(third(se), None)))))
    
    elif islist(se) and length(se) == 1 and first(se) == "+":
        None
        #return JNum(0)

    elif islist(se) and first(se) == "+":
        None
        #return JAdd(d(second(se)), d(Sep("+", se.right.right)))#the none might have to be changed



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
    


