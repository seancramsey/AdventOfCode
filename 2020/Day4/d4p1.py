import re

cat = ['byr','ecl','eyr','hcl','hgt','iyr','pid']

#open file
file = open('input.txt', 'r')
#break file into individual passports
data = file.read().split('\n\n')
file.close()

valid = 0
for d in data:
    #breaks each passport into dictionary of category and requisite data
    str = dict(sorted(re.findall(r'(\w{3}):(\S*)', d)))
    #we dont give AF about cid
    str.pop('cid', '')
    if len(str) is 7:
        valid+=1
print(valid)
