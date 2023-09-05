#Maman 13 - Q3-a - Bar Aloush 314673849
import re
# Define Users class
class Users:
    def __init__(self,name,occupation):
        self.name = name
        self.oc = occupation

# Define department classes
class Engineer(Users):
    pass

class Technician(Users):
    pass
        
class Hairdresser(Users):
    pass
        
class Politician(Users):
    pass

# Define types of engineers
class ElecEngineers(Engineer):
    pass

class CompEngineers(Engineer):
    pass

class MechEngineers(Engineer):
    pass

# Pre-populate class_map
class_map = {
    "Users": Users,
    "Engineer": Engineer,
    "Technician": Technician,
    "Hairdresser": Hairdresser,
    "Politician": Politician,
    "ElecEngineers": ElecEngineers,
    "CompEngineers": CompEngineers,
    "MechEngineers": MechEngineers
}

# Function to dynamically create classes
def create_class():
    class_name = input("Please enter the name of new class: ").lower().capitalize()
    
    # Check if the class nme is alphabetic and if not return.
    if not re.match("^[A-Za-z]+$", class_name):
        print("Invalid class name. Only alphabets are allowed")
        return
    # Check if name already exsits
    if class_name in class_map:
        print(class_name + " already exists.")
        return
    
    base_class_name = input("Please enter name of base class (blank if none): ").lower().capitalize()
    
    # Check if base class exists
    if base_class_name and base_class_name not in class_map:
        print("Base class " + base_class_name + " does not exist.")
        return
    
    method_name = input("Please enter name of new method for class " + class_name + ": ")
    attribute_name = input("Please enter name of new attribute for class " + class_name + ": ")
    
    base_class = class_map.get(base_class_name, object)
    
    # Create the new method
    new_method = lambda self: method_name
    
    # Create the new class
    new_class = type(class_name, (base_class,), {attribute_name: None, method_name: new_method})
    
    class_map[class_name] = new_class
    
    print("Class " + class_name + " created with base class: " + base_class_name)
    print("Class __name__ is: " + new_class.__name__)
    print("Class __dict__ is: " + str(new_class.__dict__))
    
# Main program
if __name__ == "__main__":
    while True:
        create_class()
        cont = input("Do you want to create another class? (y/n): ")
        if cont.lower() != 'y':
            break