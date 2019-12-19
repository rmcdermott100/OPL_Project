import HL as hilvl


#standard library function
add1e = hilvl.JApp(hilvl.JPrim("+"), hilvl.JCons(hilvl.JVar("x"), hilvl.JCons(hilvl.JNum(1), hilvl.JNull())))
add1 = hilvl.JCons(hilvl.Sestr("let"), hilvl.JCons(hilvl.Sestr("add1"), hilvl.JCons(hilvl.Sestr("="),
        hilvl.JCons(hilvl.Sestr("x"), hilvl.JCons(hilvl.Sestr("in"), hilvl.JCons(add1e, hilvl.JNull()))))))

#options and basic list functions
#do not kow exactly how to do this?
Jmap = hilvl.JCons(hilvl.Lambda('','',''), hilvl.JCons(hilvl.JCons('',''), hilvl.JNull()))