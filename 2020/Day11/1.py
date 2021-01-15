from copy import deepcopy
### KEY ###
#   L = empty seat
#   # = occupied seat
#   . = empty space
#floorMapCur = open('test.txt').read().split()
floorMapCur = open('input.txt').read().split()
dim = len(floorMapCur)
directions = [[-1,-1],[-1,0],[-1,1],[0,-1],[0,1],[1,-1], [1,0], [1,1]]
def checkNeighbors(i,j):
    sum = 0
    for x,y in directions:
        ix = i+x
        jy = j+y
        if ix >=0 and jy >= 0 and ix < dim and jy < dim:
            if floorMapCur[i+x][j+y] == '#':
                sum += 1
    return sum

changes = 100
iter = 0

floorMapNxt = [['.' for i in range(dim)] for j in range(dim)]
while changes != 0:
    iter+=1
    changes = 0
    for i in range(dim):
        for j in range(dim):
            cur = floorMapCur[i][j]
            n = checkNeighbors(i,j)
            if cur == 'L' and n == 0:
                #change seat to occupied
                floorMapNxt[i][j] = '#'
                changes += 1
            elif cur == '#' and n >= 4:
                #change seat to empty
                floorMapNxt[i][j] = 'L'
                changes += 1
            else: #if cur == '.'
                floorMapNxt[i][j] = cur
    floorMapCur = deepcopy(floorMapNxt)

print(sum([line.count('#') for line in floorMapCur]))
