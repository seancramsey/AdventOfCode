group = open('input.txt').read().split('\n\n')
total = 0
for g in group:
    total += ( len(set.intersection(*map(set,filter(None,g.split('\n'))))) )
print (total)
