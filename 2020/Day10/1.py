input = sorted([int(x) for x in open('input.txt').read().split()])
#prepend the wall outlet to the list
input.insert(0,0)
#append your device (largest adapter + 3) to the list
input.append(input[-1] + 3)
#get all differences between elements (will be less than or equal to 3)
diffs = [input[i] - input[i-1] for i in range(1,len(input))]
#count 1's and 3's
n1 = 0
n3 = 0
for i in diffs:
    if i == 1:
        n1 += 1
    elif i == 3:
        n3 += 1
print(n1*n3)
