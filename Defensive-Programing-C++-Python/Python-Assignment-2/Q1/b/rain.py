#Maman 13 - Q1-b - Bar Aloush 314673849

Rainfull_mi = "45,65,70.4,82.6,20.1,90.8,76.1,30.92,46.8,67.1,79.9"

list_Rainfull_mi = Rainfull_mi.split(",")

num_rainy_months = 0

for l in list_Rainfull_mi:
    if float(l) > 75.0 :
        num_rainy_months += 1
        