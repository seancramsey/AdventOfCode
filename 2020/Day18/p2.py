import re

def doMath(l,r,op):
    if op == '+':
        return l+r
    elif op == '*':
        return l*r
    return 0

# evaluates math expression given as a tokenized list
# recursively collapses subproblems bound by parentheses
def evaluate(expression,orderOfOperations):
    #first step, collapse parentheses
    i=0
    j=0
    # WHILE
    while i < len(expression):
        if expression[i] == '(': #we have found a subproblem that can be collapsed
            #keep track of how many open parentheses
            cntP = 1
            for j in range(i+1,len(expression)):
                #increase count of open parentheses
                if expression[j] == '(':
                    cntP += 1
                #decrease count
                elif expression[j] == ')':
                    cntP -= 1
                #once count reaches 0, we have isolated this subproblem and can
                #   evaluate it separately
                if cntP == 0:
                    break
            #new expression =   partition of expression before first found parentheses  +
            #                   evaluated partition within parentheses bounded subproblem      +
            #                   partition after subproblem
            expression = expression[:i] + [evaluate(expression[i+1:j], orderOfOperations)] + expression[j+1:]
            i+=1

        i+=1
    #END WHILE

    # evaluate expression based on given order of operations
    #   find the operater and its operands and collapse it collapse it
    for step in orderOfOperations:
        #by this point the expression has been made into the form: number,operator,number,operater....
        i=1
        #WHILE
        while i < len(expression):
            #if we find an operator for the given precedence step
            # find left and right operands and evaluate
            if type(expression[i]) is str and expression[i] in step:
                tot = doMath(expression[i-1],expression[i+1],expression[i])
                expression = expression[:i-1] + [tot] + expression[i+2:]
                continue
            i+=2
        #END WHILE
    # returns a single integer value
    return expression[0]

def preproccess(string):
    # remove all whitespace characters
    string = re.sub(r'\s+', '', string)
    # tokenize the string
    out = []
    i = 0
    while i < len(string):
        if string[i].isdigit():
            num = string[i]
            while i+1 < len(string) and string[i+1].isdigit():
                num+=string[i+1]
                i+=1
            out.append(int(num))
        else:
            out.append(string[i])
        i+=1
    return out

with open('input.txt') as file:
    total = 0
    for line in file:
        total += evaluate(preproccess(line),['+','*'])
    print(total)
