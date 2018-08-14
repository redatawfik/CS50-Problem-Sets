from cs50 import get_int

# Prompt user for input
n = get_int("Number: ")
sum = 0
multiple_sum = 0
copy = n
count = 1

# Set sum and multiple_sum values
while copy != 0:

    digit = copy % 10
    if count % 2 == 0:
        digit *= 2
        while digit != 0:
            d = digit % 10
            multiple_sum += d
            digit //= 10

    else:
        sum += digit

    copy //= 10
    count += 1

final_sum = multiple_sum + sum
number_of_digits = count - 1
first_two_digit = int(str(n)[:2])
first_digit = first_two_digit // 10

# Check type of card
if final_sum % 10 == 0:
    # AMEX card
    if number_of_digits == 15 and (first_two_digit == 34 or first_two_digit == 37):
        print("AMEX")
    # MASTERCARD card
    elif number_of_digits == 16 and (first_two_digit in range(51, 56)):
        print("MASTERCARD")
    elif (number_of_digits == 13 or number_of_digits == 16) and first_digit == 4:
        print("VISA")
    else:
        print("INVALID")
else:
    print("INVALID")
