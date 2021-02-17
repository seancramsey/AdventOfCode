from math import ceil
#part 2
#https://www.reddit.com/r/adventofcode/comments/kc4njx/2020_day_13_solutions/
# u/imbadatreading
file = open('input.txt')
timestamp = int(file.readline())
ids = [x for x in file.readline().strip().split(',')]
#pair data with its original index (offset from 0)
ids = [[i,int(x)] for i,x in enumerate(ids) if x != 'x']

lcm = 1
t = 0
for i in range(len(ids) - 1):
    idx,id = ids[i+1]
    lcm *= ids[i][1]
    while (t + idx) % id != 0:
        t += lcm
print(t)
