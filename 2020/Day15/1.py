from collections import defaultdict

MAX_TURNS = 2020 #Part 1
#MAX_TURNS = 30000000 #Part 2
starting_numbers = [20,9,11,0,1,2]
#dict contains each number and the turn it was used previously
game_memory = defaultdict(lambda: 0)
#load game memory with starting numbers
for i in range(len(starting_numbers)-1):
    game_memory[starting_numbers[i]] = i+1
prev = starting_numbers[-1]
for i in range(len(starting_numbers)+1,MAX_TURNS+1):
    #print(i-1,':',prev)
    #RULES
    #if the previous number is new, this turns number is 0
    last_used = game_memory[prev]
    game_memory[prev] = i-1
    if not last_used:
        prev = 0
    #else it is the difference between the previous turn (i-1) and when it was last spoken
    else:
        prev = (i-1) - last_used
print(prev)
