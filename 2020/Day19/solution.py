import re

def extract_Data_AoC19(fPATH):
    rules = []
    tests = []
    with open(fPATH) as file:
        for line in file:
            #if blank line, ignore
            if line == '\n':
                continue
            #rules begin with a digit
            if line[0].isdigit():
                ruleIdx, rulesList = line.split(':')
                ruleIdx = int(ruleIdx)
                ruleSet = [[int(x) if x.isdigit() else x.strip('"') for x in sub.split()] for sub in rulesList.split('|')]
                #if the next rule falls outside of the index range, expand the list to hold it and any preceding values
                #at worst this would be called n times, but if the first rule spotted was the "last" then this would only be called once
                if len(rules)-1 < ruleIdx:
                    rules.extend([None]*((ruleIdx)-(len(rules)-1)))
                rules[ruleIdx] = ruleSet
            #else it is a text string to be matched
            else:
                tests.append(line.strip())
    return rules, tests
def gen_REGEX_Pattern(RULES, RULE, DEPTH):
    if DEPTH < 0:
        return ''
    elif type(RULE) is int:
        return '(' + '|'.join([''.join([gen_REGEX_Pattern(RULES, R, DEPTH - 1) for R in SUB]) for SUB in RULES[RULE]]) + ')'
    else:
        return RULE
def evalTests(TESTS, PATTERN):
    r = re.compile(PATTERN)
    count = 0
    for t in TESTS:
        if r.fullmatch(t):
            count += 1
    return count

rules,tests = extract_Data_AoC19('input.txt')

#part1
rPATTERN = gen_REGEX_Pattern(rules, 0, 20)
print(evalTests(tests, rPATTERN))

#rule change for part 2
rules[8] = [[42],[42,8]]
rules[11] = [[42,31],[42,11,31]]
#part2
rPATTERN = gen_REGEX_Pattern(rules, 0, 20)
print(evalTests(tests, rPATTERN))

'''
[print(i,r) for i,r in enumerate(rules)]
print()
print(rPATTERN)
'''
