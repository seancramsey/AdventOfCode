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
#now, perform a recursive tree search on the ruleset to locate shiny gold bags
def findGold(color):
    items = bags[color]
    if items == []:
        return False
    if color == 'shiny gold':
        return True
    else:
        return any(findGold(c) for _,c in items)

count = -1
for b in bags:
    if findGold(b):
        count += 1
print (count)




'''
for b,r in bags.items():
    print(b, r)
'''
