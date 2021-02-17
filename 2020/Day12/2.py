#part2
from math import sin, cos, radians
data = [[x[0],int(x[1:-1])] for x in open('input.txt')]

pos = [0,0] # point [x,y] [(+east/-west),(+north/-south)]
waypoint = [10,1] #the waypoint is just the forward vector that has been scaled
def rotate(n):
    n = radians(n)
    waypoint[0],waypoint[1] =   waypoint[0]*cos(n) - waypoint[1]*sin(n),\
                                waypoint[0]*sin(n) + waypoint[1]*cos(n)
    return
for ins,n in data:
    if ins == 'N':#move waypoint north n spaces
        waypoint[1] += n
    elif ins == 'S':#move waypoint south n spaces
        waypoint[1] -= n
    elif ins == 'E':#move waypoint east n spaces
        waypoint[0] += n
    elif ins == 'W':#move waypoint west n spaces
        waypoint[0] -= n
    elif ins == 'L':#turn left n degrees (change forward direction)
        rotate(n)
    elif ins == 'R':#turn right n degrees (change forward direction)
        rotate(-n)
    elif ins == 'F':#Move forward (forward rirection)
        pos[0] += waypoint[0]*n
        pos[1] += waypoint[1]*n
print(round(abs(pos[0]) + abs(pos[1])))
