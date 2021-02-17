def N_Z(i): # Natural numbers (Z+) to all integers
    if i%2: # odd -> negative
        return int(-(i+1)/2)
    else:   # even-> positive
        return int(i/2)
def Z_N(i): # Integers to Natural numbers
    if i<0: # neg to odd
        return int(-2*i-1)
    else:   # pos to even
        return int(2*i)

def printGrid(grid):
    return

def getNeighbors():
    return


def genEmpty(grid, dim):
    if dim == 2:
        return 0
    return
    return [genEmpty(grid, dim-1)]

def expandGrid_r(grid,dim):
    if dim < 2:
        return
    for g in grid:
        expandGrid_r(g, dim - 1)
        buffer = genEmpty(g, dim)
        g.append(buffer)
        g.insert(0, buffer)
    return

# # NOTE: Rethink this, for each dimensions, copy the contents of the dimesion lower

def expandGrid(grid, dim):
    expandGrid_r(grid, dim)
    grid.append(genEmpty(grid, dim))
    grid.insert(0,genEmpty(grid,dim))
    return


#initGrid:
# takes puzzle input and the number of dimensions
# recursively generate nested lists until the number of dimensions is equal to
#   dimensions of the input. once that val is reached insert the input into the
#   matrix
def initGrid(puzzInput,dim):
    if dim < 2:
        return [-1]
    if dim == 2:
        return [[x for x in line] for line in puzzInput]
    return [initGrid(puzzInput,dim-1)]

# Runs the simulation for n turns
def run(puzzInput, dim, turns):
    #generate initial grid from puzzle input and number of dimensions
    grid = initGrid(puzzInput, dim, turns)
    for _ in range(turns):
        #expand the grid space
        expandGrid(grid, dim)
        #apply rules and advance game
        continue

puzzInput = [[int(x) for x in line.replace('#', '1').replace('.', '0').strip()] for line in open('input.txt')]


grid = initGrid(puzzInput, 3)
[print(g,'\n') for g in grid]
expandGrid(grid,3)
print()
[print(g,'\n') for g in grid]

# Construct algorithm that can be expanded to any number of dimensions


#space is not continous, every 'cube' occupies a discrete integer position
#how to store these points


#as a hashmap
#dict = {string(coord[x,y,z,w]) : [coord[x,y,z,w], curState, nextState]}
    #   {"0,0,0,16" : [[0,0,0,16], 1, 0] }

#as an n-dimensional array (list)
#x1 = [
#        x1y1 = [
#                x1y1z1 = [
#                            curState,nextState
#                        ]
#            ],
#        x1y2 = [
#                x1y2z1 = [
#                            curState,nextState
#                        ]
#            ],
#    ]
