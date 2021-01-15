import re

rCode = r'(acc|jmp|nop) ((?:\-?\+?)\d+)'
input = open('input.txt').read()

code = re.findall(rCode,input)

tracker = [False]*len(code)
accumulator = 0
cur = 0

while not tracker[cur]:
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

print (accumulator)
