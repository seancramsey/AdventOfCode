#Part 2
import re

def toBin36(n:int):
    return format(n,"b").zfill(36)

#iterative generation
def genAddresses_iter(srcAddress):
    xid = [] #store all the indices of X
    ret = [] #list storing generated address
    ret.append(srcAddress)
    for i in range(len(srcAddress)):
        if srcAddress[i] == 'X':
            xid.append(i)
    for i in xid:
        ret0 = [] #tempoorary address list
        for r in ret:
            ret0.append(r[:i] + '0' + r[i+1:])
            ret0.append(r[:i] + '1' + r[i+1:])
        ret.clear()
        ret = ret0
    return ret
#recursive generation
def genAddresses_recur(srcAddress):
    i = srcAddress.find('X') #finds the first instance of X
    #if no more X's are found, end recusion
    if i < 0:
        return [srcAddress]
    return genAddresses_recur(srcAddress[:i]+'0'+srcAddress[i+1:]) + genAddresses_recur(srcAddress[:i]+'1'+srcAddress[i+1:])


#mask is applied to destination memory
def applyMask(m:str, n:str):
    floating = []
    ret = []
    for i in range(len(m)):
        if m[i] != '0':
            n = n[:i] + m[i] + n[i+1:]
    #ret = genAddresses_iter(n)
    ret = genAddresses_recur(n)
    return ret
#dictionary/hashmap to contain values and there keys(memory addresses)
memory = {}
mask = ""
for line in open("input.txt"):
    if  line[1] == 'a':
        #set mask
        mask = re.match(r'^mask = (.*)$',line).group(1)
    elif line[1] == 'e':
        #apply current mask and store value in "memory"
        kv = re.match(r'^mem\[(\d*)\] = (.*)$',line)
        addresses = applyMask(mask,toBin36(int(kv.group(1))))
        value = int(kv.group(2))
        for address in addresses:
            memory[int(address,2)] = value

sum = 0
for k in memory:
    sum += memory[k]
print(sum)
