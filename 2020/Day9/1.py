#use modified two solution from day 1
def bTwoSum(List, value):
    dict = {}
    for n in List:
        nv = value - n
        if nv in dict:
            return True
        dict[n] = nv
    return False

data = [int(x) for x in open('input.txt').read().split()]

for i in range(26, len(data)):
    if not bTwoSum(data[i-25:i],data[i]):
        print (data[i])
        break;
