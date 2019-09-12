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
    None 
    

def length(se):
    if se.right == None:
        return 0
    elif se.right != None:
        return 1 + length(se.right)

def islist():
    None


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
   se_test_suite() 















