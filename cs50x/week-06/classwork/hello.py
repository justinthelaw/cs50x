from cs50 import get_string

count = 1
max = int(input("Pick a number: "))
blocks = "#"
name = get_string("What is your name? ")

print(f"hello, {name}")

if name == "Justin":
    print("You have the same name as me!")
elif name == "hello":
    print("Haha, very funny...")
else:
    print("Welcome to Justin's week-06 cs50x repository!")

while count <= max:
    for i in range(count):
        print(blocks)
    blocks += "#"
    count += 1
