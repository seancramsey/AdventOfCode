import re

r_ticket_field = r'^(.+): (\d+)-(\d+) or (\d+)-(\d+)$'
ticket_field_rules = {} #{ field_name : [[list of rules],[colums it applies to]] }
your_ticket = []
nearby_tickets = []
# parse entire text file into requisite data structures
for i,line in enumerate(open('input.txt')):
    if i < 20:      # this is information in the ticket field limits
        match = re.match(r_ticket_field, line.strip())
        ticket_field_rules[match.group(1)] = [[int(match.group(2)),int(match.group(3)), int(match.group(4)),int(match.group(5))], []]
        continue
    elif i > 24:    # this start the 'other tickets' section
        nearby_tickets.append([int(x) for x in line.strip().split(',')])
        continue
    elif i == 22:   # this is your ticket info
        your_ticket = [int(x) for x in line.strip().split(',')]
    else:           # else we do not care
        continue
#applies the rule given in the input file
def applyRule(n, rule):
    return ((rule[0][0] <= n <= rule[0][1]) or (rule[0][2] <= n <= rule[0][3]))
#a number is valid if it matches any rule
def isNumberValid(n):
    return any([applyRule(n,r) for r in ticket_field_rules.values()])
#a ticket is valid only if all numbers in it are valid
def isTicketValid(ticket):
    return all([isNumberValid(n) for n in ticket])
#get rid of trash data
def removeInvalidTickets():
    for i in range(len(nearby_tickets)-1, -1, -1):
        if not isTicketValid(nearby_tickets[i]):
            nearby_tickets.pop(i)
    return None
removeInvalidTickets()

#populate rules data that point to valid indices
for rule in ticket_field_rules:
    ticket_field_rules[rule][1] = [x for x in range(len(your_ticket))]
#add your ticket to the pool, it could hold valuable info too after all, probably not tho
nearby_tickets.append(your_ticket)
#Step 1: determine which fields each set of values could be
#We already initialized the rules dict to point to all, so we can just remove what doesnt work
for i in range(len(your_ticket)):
    for rule in ticket_field_rules:
        for ticket in nearby_tickets:
            if not applyRule(ticket[i], ticket_field_rules[rule]):
                ticket_field_rules[rule][1].remove(i)
                break
#Step 2: because this why not there will be at least one rule which only matches
# a single value. So, remove that option from other rules. Continue until one in each
#It would be fun to solve situations where more complicated elimations are required
#but that is beyond the scope of this exercise
def allLenOne():
    return all([len(values[1]) == 1 for values in ticket_field_rules.values()])
while not allLenOne():
    for rule in ticket_field_rules:
        if len(ticket_field_rules[rule][1]) == 1:
            for rule2 in ticket_field_rules:
                if rule != rule2:
                    if ticket_field_rules[rule][1][0] in ticket_field_rules[rule2][1]:
                        ticket_field_rules[rule2][1].remove(ticket_field_rules[rule][1][0])

multiplyDepartures = 1
for rule in ticket_field_rules:
    if re.match(r'departure',rule):
        multiplyDepartures *= your_ticket[ticket_field_rules[rule][1][0]]

print(multiplyDepartures)
