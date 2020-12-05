import re

f = open('input.txt', 'r')

rParse = r'^(\d+)-(\d+) ([a-z]): ([a-z]+)$'
validPasses = 0
for line in f:
    p = re.match(rParse, line)
    if p:
        cnt = len(re.findall(p.group(3), p.group(4)))
        if int(p.group(1)) <= cnt <= int(p.group(2)):
            validPasses += 1
print (validPasses)
