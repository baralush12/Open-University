#Maman 13 - Q2-a - Bar Aloush 314673849

class AppleBasket:
    
    def __init__(self, apple_color, apple_quantity):
        self.color = apple_color
        self.quantity = apple_quantity
    def increase(self):
        self.quantity += 1
    def __str__(self):
        return "A basket of " +  str(self.quantity) + " " + str(self.color) + " apples."
    
p1 = AppleBasket("red",4)
p2 = AppleBasket("blue",50)
print(p1)
print(p2)