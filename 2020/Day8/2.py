import re

rCode = r'(acc|jmp|nop) ((?:\-?\+?)\d+)'
input = open('input.txt').read()

code = re.findall(rCode,input)

def exec():
    tracker = [False]*len(code)
    accumulator = 0
    cur = 0
    while cur < len(code) and not tracker[cur]:
        tracker[cur] = 1
        cmd, value = code[cur]
        value = int(value)
        if cmd == 'acc':
            accumulator += value
            cur += 1
        elif cmd == 'jmp':
            cur += value
        elif cmd == 'nop':
            cur += 1
    if cur == len(code):
        #successfully reached end of code
        return (True, accumulator)
    else:
        #breaking while loop means a loop was encountered
        return (False, accumulator)

for i,(c,v) in enumerate(code):
    if c == 'jmp':
        code[i] = ('nop', v)
        t,acc = exec()
        if t is True:
            print(acc)
            break
        code[i] = ('jmp', v)
    elif c == 'nop':
        code[i] = ('jmp', v)
        t,acc = exec()
        if t is True:
            print(acc)
            break
        code[i] = ('nop', v)
    else:
        continue
