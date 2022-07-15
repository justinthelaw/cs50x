import cs50

height = cs50.get_int("Height: ")
while height < 1 or height > 8:
    height = cs50.get_int("Height: ")

i = 1
while i <= height:
    print(" " * int(height - i), end="")
    print("#" * int(i), end="  ")
    print("#" * int(i))
    i += 1
