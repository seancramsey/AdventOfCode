from math import ceil

file = open('input.txt')
timestamp = int(file.readline())
#get all ids that are "in service"
ids = [int(x) for x in file.readline().strip().replace(',x','').split(',')]
#calculate the next arrival time for each train
nxt_arrivals = [ceil(timestamp/id)*id for id in ids]

#the the index of the next arrivial
idx = nxt_arrivals.index(min(nxt_arrivals))

print ((nxt_arrivals[idx]-timestamp) * ids[idx])
