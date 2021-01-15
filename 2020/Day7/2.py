import re

rules = open('input.txt').read().strip().split('\n')
rColor = r'(.+?) bags contain'
rContains = r'(\d+?) (.+?) bags?'
#dictionary/hashmap will contain rules for each bag type
bags = {}
#populate dict with rules
for r in rules:
    color = re.match(rColor, r)[1]
    bags[color] = re.findall(rContains, r)
#bag plus the sum of its children
def bagsIn(color):
    items = bags[color]
    return 1 + sum([bagsIn(c)*int(n) for n,c in items])

#subtract 1 to not include the outermost gold bag
print (bagsIn('shiny gold') - 1)
