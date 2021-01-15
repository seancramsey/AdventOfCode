import re

f = open('input.txt', 'r')

rParse = r'^(\d+)-(\d+) ([a-z]): ([a-z]+)$'
validPasses = 0
for line in f:
    p = re.match(rParse, line)
    if p:
        if (p.group(4)[int(p.group(1)) - 1] == p.group(3)) ^ (p.group(4)[int(p.group(2)) - 1] == p.group(3)):
            validPasses += 1
print (validPasses)
