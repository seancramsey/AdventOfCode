import re

r_ticket_field = r'^(.+): (\d+)-(\d+) or (\d+)-(\d+)$'
ticket_field_rules = {}
your_ticket = []
nearby_tickets = []

# parse entire text file into requisite data structures
for i,line in enumerate(open('input.txt')):
    if i < 20:      # this is information in the ticket field limits
        match = re.match(r_ticket_field, line.strip())
        ticket_field_rules[match.group(1)] = [int(match.group(2)),int(match.group(3)), int(match.group(4)),int(match.group(5))]
        continue
    elif i > 24:    # this start the 'other tickets' section
        nearby_tickets.append([int(x) for x in line.strip().split(',')])
        continue
    elif i == 22:   # this is your ticket info
        your_ticket = [int(x) for x in line.strip().split(',')]
    else:           # else we do not care
        continue
# sol to part 1
def ticketScanError():
    invalid_numbers = []
    for ticket in nearby_tickets:
        for number in ticket:
            invalid_numbers.append(number)
            for rule in ticket_field_rules.values():
                if rule[0] <= number <= rule[1] or (rule[2] <= number <= rule[3]):
                    invalid_numbers.pop()
                    break

    return sum(invalid_numbers),len(invalid_numbers)

print(ticketScanError())
