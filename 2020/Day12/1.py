from math import sin, cos, radians
data = [[x[0],int(x[1:-1])] for x in open('input.txt')]

pos = [0,0] # point [x,y] [(+east/-west),(+north/-south)]
forward = [1,0] # normalized vector [x,y] [(+east/-west),(+north/-south)]
def rotate(n):
    n = radians(n)
    forward[0],forward[1] = forward[0]*cos(n) - forward[1]*sin(n),\
                            forward[0]*sin(n) + forward[1]*cos(n)
    return
for ins,n in data:
    if ins == 'N':#move north n spaces
        pos[1] += n
    if ins == 'S':#move south n spaces
        pos[1] -= n
    if ins == 'E':#move east n spaces
        pos[0] += n
    if ins == 'W':#move west n spaces
        pos[0] -= n
    if ins == 'L':#turn left n degrees (change forward direction)
        rotate(n)
    if ins == 'R':#turn right n degrees (change forward direction)
        rotate(-n)
    if ins == 'F':#Move forward (forward rirection)
        pos[0] += forward[0]*n
        pos[1] += forward[1]*n
print(abs(pos[0]) + abs(pos[1]))
