input = sorted([int(x) for x in open('input.txt').read().split()])
#append your device (largest adapter + 3) to the list
input.append(input[-1] + 3)
d = {0:1}
#memoized solution
for i in input:
    d[i] = d.get(i-3,0) + d.get(i-2,0) + d.get(i-1,0)
print(d[input[-1]])
