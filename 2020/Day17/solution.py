def countActiveCells(grid):
    count = 0
    for k in grid:
        if grid[k][1]:
            count += 1
    return count
# recurvisely generates neighborhood of coords where each value is at most 1 away from the origin
def getNeighborhood(origin, i):
    if i >= len(origin):
        return [origin]
    return getNeighborhood(origin, i+1) + getNeighborhood(origin[:i] + [origin[i]+1] + origin[i+1:], i+1) + getNeighborhood(origin[:i] + [origin[i]-1] + origin[i+1:], i+1)
# check if update condition is met
def doUpdate(n,count):
    return (n and (count<2 or count>3)) or (not n and (count == 3))
def updateGrid(grid):
    # the following two vars prevent duplicates, this is needed to get accuracte update behaviour
    toAdd = {} # this dict will contain a key value pair of coordinates to be added to the expanded grid this turn
    toUpdate = set() # this set contains the keys of cells that should be updated at the end of this turn
    #for each cell in the current grid
    for key in grid:
        count = 0
        #loop through its nieghbors
        for i in range(1,len(grid[key][0])):
            nC = grid[key][0][i]
            s_nC = str(nC)
            if s_nC in grid:
                #if neighbor exists in current grid, check its state
                count += grid[s_nC][1]
            else:
                #if neighbor does not exist, stage it to be added in the next step
                toAdd[s_nC] = nC
        if doUpdate(grid[key][1],count):
            toUpdate.add(key)
    # add all new cells to the grid
    #   this expands the grid 1 step
    for key in toAdd:
        grid[key] = [getNeighborhood(toAdd[key],0),0]
        count = 0
        for i in range(1,len(grid[key][0])):
            nC = grid[key][0][i]
            s_nC = str(nC)
            if s_nC in grid:
                #if neighbor exist in current grid, check its state
                count += grid[s_nC][1]
                # we dont stage extra nighbors to add this time
        if doUpdate(grid[key][1],count):
            toUpdate.add(key)
    # update all cells that have been staged
    for key in toUpdate:
        grid[key][1] = 1-grid[key][1]
    return
#initGrid:
# takes puzzle input and number of dimensions
# create dict entries in the form:
#   grid[str(['x1,x2,...,xn' coord])] = [int[3^(#dim) neighborhood coords], activeState]
def initGrid(puzzInput, dim):
    grid = {}
    for i,row in enumerate(puzzInput):
        for j,item in enumerate(row):
            coord = [i,j] + [0]*(dim-2)
            grid[str(coord)] = [getNeighborhood(coord,0), item]
    return grid
# Runs the simulation for n turns
def run(puzzInput, dim, turns):
    #generate initial grid from puzzle input and number of dimensions
    grid = initGrid(puzzInput, dim)
    for _ in range(turns):
        # update n time
        updateGrid(grid)
    # return the final count of active cells
    return countActiveCells(grid)

puzzInput = [[int(x) for x in line.replace('#', '1').replace('.', '0').strip()] for line in open('input.txt')]

print ('part 1: ',run(puzzInput,3,6))
print ('part 2: ',run(puzzInput,4,6))
