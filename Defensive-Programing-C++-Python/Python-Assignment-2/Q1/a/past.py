#Maman 13 - Q1-a - Bar Aloush 314673849

words = ["adopt", "bake","beam", "cook", "time", "grill", "waved", "hire"]

for word in words:
    if word[-1:] == "e":
        word += 'd'
    elif word[-1] != "e" and word[-2:] != "ed":
        word += 'ed'
 
        