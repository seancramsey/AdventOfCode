import re

cat = ['byr','cid','ecl','eyr','hcl','hgt','iyr','pid']
ecList = ['amb','blu','brn','gry','grn','hzl','oth']

def validateH(h, m):
    if m == 'in':
        if 59 <= h <= 76:
            return True
    if m == 'cm':
        if 150 <= h <= 193:
            return True
    return False

def isValid(id):
    id.pop('cid','')
    if len(id) is 7:
        if (1920 <= int(id['byr']) <= 2002 and
            2010 <= int(id['iyr']) <= 2020 and
            2020 <= int(id['eyr']) <= 2030 and
            re.match('^#([a-z0-9]{6})$', id['hcl']) and
            id['ecl'] in ecList and
            re.match('^(\d{9})$', id['pid']) and
            validateH(int(id['hgt'][:-2]),id['hgt'][-2:])):
            return True
    return False

#open file
file = open('input.txt', 'r')
#break file into individual passports
data = file.read().split('\n\n')
file.close()

valid = 0
for d in data:
    #breaks each passport into dictionary of category and requisite data
    id = dict(sorted(re.findall(r'(\w{3}):(\S*)', d)))
    if isValid(id):
        valid+=1
print(valid)
