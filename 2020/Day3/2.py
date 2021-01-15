
data = [line.strip() for line in open('input.txt', 'r')]
width = len(data[0])
height = len(data)

def func(slope):
    curPos = [0,0]
    treesHit = 0
    while curPos[1] < height:
        if data[curPos[1]][curPos[0]] is '#':
            treesHit += 1
        curPos[0] = (curPos[0] + slope[0]) % width
        curPos[1] += slope[1]
    return treesHit

print(func([1,1])*func([3,1])*func([5,1])*func([7,1])*func([1,2]))
