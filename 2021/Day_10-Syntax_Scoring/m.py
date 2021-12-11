from statistics import median

scores = {")": 3, "]": 57, "}": 1197, ">": 25137, }
lines = list(line.strip() for line in open("input.txt"))
opening, closing = "([{<", ")]}>"
pairs = dict(zip(closing, opening))

def check(line, correct=True):
    stack = []
    for char in line:
        if char in opening:
            stack.append(char)
        else:
            if pairs[char] != stack.pop():  # corrupt
                if correct:
                    return 0
                return scores[char]
    if not correct:
        return 0
    score = 0
    while stack:
        score *= 5
        score += opening.index(stack.pop()) + 1
    return score

print(sum(check(line, correct=False) for line in lines))
print(median(filter(None, map(check, lines))))