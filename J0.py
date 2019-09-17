class J0e(object):
   None 

class JNum(J0e):
    n = None
    def __init__(self, num):
        self.n = num
    
    def pp(self):
        return str(self.n)

    def interp(self):
        return int(self.n)

class JAdd(J0e):
    left = None
    right = None
    def __init__(self, l,r):
        self.left = l
        self.right = r

    def pp(self):
        return "(" + self.left.pp() + " + " + self.right.pp() + ")" 

    def interp(self):
        return self.left.interp() + self.right.interp()

class JMult(J0e):
    left = None
    right = None
    def __init__(self, l,r):
        self.left = l
        self.right = r

    def pp(self):
        return "(" + self.left.pp() + " * " + self.right.pp() + ")"

    def interp(self):
        return self.left.interp() * self.right.interp()
    
class Se(object):
    None

class Sep(Se):  
    left = None
    Right = None
    
    def __init__(self, l, r):
        self.left = l
        self.right = r
    
    

def d(se):

    if type(se) is str:
        return JNum(se)

    if islist(se) and length(se) == 2 and first(se) == "-":
        return JMult(JNum(-1), JNum(second(se)))

    elif islist(se) and length(se) == 3 and first(se) == '-':
        return JAdd(d(second(se)), d(Sep("-", (Sep(third(se), None)))))
    
    elif islist(se) and length(se) == 1 and first(se) == "+":
        return JNum(0)

    elif islist(se) and first(se) == "+":
        return JAdd(d(second(se)), d(Sep("+", se.right.right)))#the none might have to be changed



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
    if se.left != None:
        return True
    else:
        return False


def isNull(se):
    if se == None:
        return True
    else:
        return False

def pretty_printer_test_suite():
    print(JNum(5).pp())
    print(JAdd(JNum(5), JNum(6)).pp())
    print(JMult(JNum(5), JNum(6)).pp())
    print(JNum(57).pp())
    print(JAdd(JNum(9), JNum(10)).pp())
    print(JMult(JNum(8), JNum(15)).pp())
    print(JAdd(JNum(5), JMult(JNum(5), JNum(7))).pp())
    print(JAdd(JNum(8), JMult(JNum(9), JNum(10))).pp())
    print(JAdd(JNum(5), JMult(JNum(5), JMult(JNum(3), JNum(7)))).pp())
    print(JMult(JNum(4), JMult(JNum(5), JNum(6))).pp())
    print(JAdd(JNum(77), JAdd(JNum(1), JNum(7))).pp())
    print(JMult(JNum(100), JMult(JNum(5), JNum(7))).pp())


def interp_test_suite():
    print("5 =", JNum(5).interp())
    print("15 =", JMult(JNum(3), JNum(5)).interp())
    print("14 =", JAdd(JNum(5), JNum(9)).interp())
    print("19 =", JAdd(JNum(7), JMult(JNum(2), JNum(6))).interp())

def se_test_suite():
    print(Sep("a",Sep("b",Sep("c",None).left).right).right)
    
if __name__ == "__main__":
    #se_test_suite()
    
    print(d(Sep("+", Sep("3", Sep("1", Sep("2", None))))).interp())
    


