import math

print("Prime numbers to 1000")

print("2, 3, 5, 7",end="")

for number in range(11, 10000, 2):
    prime = 1
    for divider in range(2, int(math.sqrt(number))+1, 1):
        if number/divider == int(number/divider):
            prime = 0

    if prime == 1:
        print(",", number, end="")
