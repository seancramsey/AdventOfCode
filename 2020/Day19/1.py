import re
rRuleMatch = r'():'

rules = {}
tests = []
with open('input.txt') as file:
    for line in file:
        # if line begins with a number it is a rule
        if line[0].isdigit():

            continue
        #else it is a text string to be matched
        else:
            tests.append(line.strip())
