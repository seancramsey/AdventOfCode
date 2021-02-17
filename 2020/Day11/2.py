from copy import deepcopy
### KEY ###
#   L = empty seat
#   # = occupied seat
#   . = empty space
#floorMapCur = open('test.txt').read().split()
floorMapCur = open('input.txt').read().split()
floorMapCur = [list(row) for row in floorMapCur]
dim = len(floorMapCur)
directions = [[-1,-1],[-1,0],[-1,1],[0,-1],[0,1],[1,-1], [1,0], [1,1]]
#for part 2, extend check in line until first seat is seen
def checkNeighbors(i,j):
    sum = 0
    #in all 8 directions
    for x,y in directions:
        step = 1
        #take step in that direction
        while 1:
            ix = i+(step*x)
            jy = j+(step*y)
            #until first seat (or end of grid) is found
            if ix >=0 and jy >= 0 and ix < dim and jy < dim:
                if floorMapCur[ix][jy] == '#':
                    sum += 1
                    break
                if floorMapCur[ix][jy] == 'L':
                    break
            else:
                break
            step += 1
    return sum

changes = 100 #arbitrary value gt 0
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
            elif cur == '#' and n >= 5:
                #change seat to empty
                floorMapNxt[i][j] = 'L'
                changes += 1
            else: #if cur == '.'
                floorMapNxt[i][j] = cur
    #why does python not have pointer tho?
    floorMapCur = deepcopy(floorMapNxt)

print(sum([line.count('#') for line in floorMapCur]))
