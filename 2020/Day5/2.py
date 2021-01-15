input = open('input.txt').read().strip().split()
#boarding passes are converted to binary representation based on FBLR upper/lower encoding
#the value is cast to an integer, which is equal to the seat id
input = [int(x.replace('F','0').replace('B','1').replace('L','0').replace('R','1'),2) for x in input]
input.sort()

#this finds all missing seats, though there should only be one(,yours)
for i in range(len(input) - 1):
    if input[i] + 1 != input[i+1]:
        print(input[i] + 1)
