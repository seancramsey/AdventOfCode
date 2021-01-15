#use modified twoSum solution from day 1
def bTwoSum(List, value):
    dict = {}
    for n in List:
        nv = value - n
        if nv in dict:
            return True
        dict[n] = nv
    return False

#find the value
def part1(data):
    for i in range(26, len(data)):
        if not bTwoSum(data[i-25:i],data[i]):
            return (data[i])
    return 0

data = [int(x) for x in open('input.txt').read().split()]

n = part1(data)

st = 0 #start index
ed = 0 #end index
sum = data[st]
while sum != n:
    if sum < n:
        ed += 1
        sum += data[ed]
    elif sum > n:
        sum -= data[st]
        st += 1

print(min(data[st-1:ed+1]) + max(data[st-1:ed+1]))
