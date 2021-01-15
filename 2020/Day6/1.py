group = open('input.txt').read().split('\n\n')

print(sum([len(set(g.replace('\n', ''))) for g in group]))
