import re

def toBin36(n:int):
    return format(n,"b").zfill(36)
def applyMask(m:str, n:str):
    for i in range(len(m)):
        if m[i] != 'X':
            n = n[:i] + m[i] + n[i+1:]
    return n
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
        memory[int(kv.group(1))] = applyMask(mask,toBin36(int(kv.group(2))))

sum = 0
for k in memory:
    sum += int(memory[k],2)
print(sum)
