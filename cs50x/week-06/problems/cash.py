import cs50

change = -1
while change < 0:
    change = cs50.get_float("Change owed: ")

coins = 0
remainder = 0

if change >= 0.25:
    print(change, coins, 0.25)
    remainder = round(change % 0.25, 3)
    coins += round((change - remainder) / 0.25)
    change = remainder

if change >= 0.10:
    print(change, coins, 0.10)
    remainder = round(change % 0.1, 3)
    coins += round((change - remainder) / 0.1)
    change = remainder

if change >= 0.05:
    print(change, coins, 0.05)
    remainder = round(change % 0.05, 3)
    coins += round((change - remainder) / 0.05)
    change = remainder

if change >= 0.01:
    print(change, coins, 0.01)
    remainder = round(change % 0.01, 3)
    coins += round((change - remainder) / 0.01)
    change = remainder

print(coins)
