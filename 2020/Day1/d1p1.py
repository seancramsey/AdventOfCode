def func(f, k):
    data = {} #dictionary/unordered hashmap
    for d in f: #for every line in the file
        d = int(d)
        dk = k - d
        if dk in data:
            print(d, dk)
            return (d, dk)
        data[d] = dk
    return (1,-1) #could not be found

f = open('input.txt', 'r')
l,r = func(f,2020)
print(l*r)
