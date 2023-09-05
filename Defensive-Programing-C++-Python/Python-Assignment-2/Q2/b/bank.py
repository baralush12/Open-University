#Maman 13 - Q2-b - Bar Aloush 314673849

class BankAccount:
    
    def __init__(self, name, amt):
        self.n = name
        self.amount = amt
    def __str__(self):
        return "Your account, " +  str(self.n) + ", "  + "has " + str(self.amount) + " dollars"
    
if __name__ == "__main__":
    t1 = BankAccount("Bob",100)
    print(t1)