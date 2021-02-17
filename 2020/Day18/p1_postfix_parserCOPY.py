#   This solves part 1 just fine, however adapting it to part 2 has not worked at all

def parsePostfix(expression):
    print(expression)
    s = []
    for item in expression:
        if item in ['+', '*']:
            a = s.pop()
            b = s.pop()
            if item == '+': res = b+a
            if item == '*': res = b*a
            s.append(res)
        else:
            s.append(int(item))
    return s.pop()

def reverse_infixToPostfix(expression):
    s = []
    postfix = []
    i = len(expression)-1
    while i >= 0:
        if expression[i].isdigit():
            num = expression[i]
            while (i-1)>=0 and expression[i-1].isdigit():
                i -= 1
                num += expression[i]
            postfix.append(num)

        elif expression[i]==')':
            s.append(expression[i])

        elif expression[i]=='(':
            while len(s)>0 and s[-1] != ')':
                postfix.append(s.pop())
            s.pop() #pop off '('

        #operators and precedence
        else:
            s.append(expression[i])
        i-=1

    while len(s) != 0:
        postfix.append(s.pop())
    return postfix

def evaluate(expression):
    return parsePostfix(reverse_infixToPostfix(expression.replace(' ','').strip()))

with open('input.txt') as file:
    print(sum([evaluate(line) for line in file]))
