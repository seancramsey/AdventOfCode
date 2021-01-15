### KEY ###
#   L = empty seat
#   # = occupied seat
#   . = empty space
#floorMapCur = open('test.txt').read().split()
floorMapCur = open('input.txt').read().split()
# Add buffers to map, this will protect against out of index errors
#'''ADD BUFFER TO THE END OF EACH ROW
floorMapCur = [list('.'+floorMapCur[i]+'.') for i in range(0, len(floorMapCur))]
#'''ADD BUFFER ROWS
border = ['.'] * len(floorMapCur[0])
floorMapCur.insert(0,border)
floorMapCur.append(border)
#Store new map dimensions
dim = len(floorMapCur)
directions = [[-1,-1],[-1,0],[-1,1],[0,-1],[0,1],[1,-1], [1,0], [1,1]]
#part 2 checks for first in line of direction
def checkNeighbors(i,j):
    for x,y in direction:
        step = 0;
        return [floorMapCur[i+x][j+y] for x,y in directions].count('#')

changes = 100
iter = 0

#floorMapNxt = [['.' for i in range(dim)] for j in range(dim)]
while changes != 0:
    iter+=1
    changes = 0
    floorMapNxt = [['.' for i in range(dim)] for j in range(dim)]
    for i in range(1,dim-1):
        for j in range(1,dim-1):
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
    floorMapCur = floorMapNxt.copy()
    [print(i) for i in floorMapCur]
    print(iter)
    print()

print(sum([line.count('#') for line in floorMapCur]))
[print(i) for i in floorMapCur]
