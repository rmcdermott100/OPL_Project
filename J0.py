class J0e(object):
    None

class JNum(J0e):
    n = None
    def __init__(self, num):
        n = num
            
class JAdd(J0e):
    left = None
    right = None
    def __init__(self, l,r):
        self.left = l
        self.right = r

class JMult(J0e):
    left = None
    right = None
    def __init__(self, l,r):
        self.left = l
        self.right = r


