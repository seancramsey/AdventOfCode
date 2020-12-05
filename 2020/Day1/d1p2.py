#function for finding 2 elements summing to k in a dataset
#sol to part 1
def func(data, k):
    dict = {} #dictionary/unordered hashmap
    for d in data: #for every line in the file
        d = int(d)
        dk = k - d
        if dk in dict:
            return (d, dk)
        dict[d] = dk
    return (1,-1) #could not be found

#sol to part2
def func2(data, k):
    i = -1
    for d in data:
        i += 1
        dk = k - d
        rl,rr = func(data[i:], dk)
        if rl*rr == -1:
            continue
        else:
            return (d, rl, rr)
    return(1,1,-1) #could not be found

f = open('input.txt', 'r')
data = list(map(int, f.read().split('\n')))
l,m,r = func2(data, 2020)
print (l,m,r)
print(l*m*r)
