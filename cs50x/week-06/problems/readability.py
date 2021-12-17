import cs50

text = cs50.get_string("Text: ").strip()
grade = 0
totalWords = 0
totalSentences = 0
totalLetters = 0

for i in range(0, len(text)):
    if text[i].isalpha():
        totalLetters += 1
    if (i == 0 and text[i] != " ") or (text[i] == " " and text[i + 1] != " "):
        totalWords += 1
    if text[i] == "." or text[i] == "?" or text[i] == "!":
        totalSentences += 1

L = (totalLetters / totalWords) * 100
S = (totalSentences / totalWords) * 100
grade = round(0.0588 * L - 0.296 * S - 15.8)

if grade > 16:
    print(f"Grade 16+")
elif grade > 0:
    print(f"Grade {grade}")
else:
    print(f"Before Grade 1")
