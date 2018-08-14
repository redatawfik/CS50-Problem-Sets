from cs50 import get_int

# Prompt user for input
while True:
    n = get_int("Height: ")
    # Validate user input
    if(n >= 0 and n <= 23):
        break

# loop itrate throw hight
for i in range(n):

    # Print the first half of the pyramid
    print(" " * (n - i - 1), end="")
    print("#" * (i + 1), end="")

    # Print the gap
    print("  ", end="")

    # Print the second half of the pyramid
    print("#" * (i + 1), end="")
    print()
