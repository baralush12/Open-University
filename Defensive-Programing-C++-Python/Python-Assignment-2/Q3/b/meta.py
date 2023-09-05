#Maman 13 - Q3-b - Bar Aloush 314673849

import os

# Define a decorator to add code to a function
def add_code_decorator(code_to_add):
    def decorator(func):
        def wrapper(*args, **kwargs):
            exec(code_to_add)
            return func(*args, **kwargs)
        return wrapper
    return decorator

# Main execution starts here
if __name__ == "__main__":
    # Get the Python file name and the code snippet from the user
    file_name = input("Enter python file name: ")

    # Check for .py extension
    if not file_name.endswith('.py'):
        print("Please provide a Python file with a .py extension.")
        exit(1)

    # Check if the file exists
    if not os.path.exists(file_name):
        print("The file " + file_name + " does not exist.")
        exit(1)

    code_to_add = input("Enter a Python code: ")

    # Validate the code snippet
    max_code_length = 500
    if len(code_to_add) > max_code_length:
        print("The code snippet is too long.")
        exit(1)

    risky_functions = ['exec', 'eval', 'open', 'write', 'system']
    if any(func in code_to_add for func in risky_functions):
        print("The code snippet contains risky function calls.")
        exit(1)
        
    try:
        with open(file_name, 'r') as f:
            source_code = f.read()
    except Exception as e:
        print("Could not read the file: " + str(e))
        exit(1)

    exec_globals = {}
    try:
        exec(source_code, exec_globals)
    except Exception as e:
        print("Could not execute the source code: " + str(e))
        exit(1)

    for name, obj in exec_globals.items():
        if isinstance(obj, type):
            new_methods = {}
            for attr_name, attr_value in obj.__dict__.items():
                if callable(attr_value):
                    new_methods[attr_name] = add_code_decorator(code_to_add)(attr_value)
            
            ModifiedClass = type(name, (obj,), new_methods)
            
            try:
                instance = ModifiedClass("red", 4)  # This is a placeholder. You'll need to handle this dynamically.
            except Exception as e:
                print("Could not instantiate the class: " + str(e))
                continue

            for method_name in new_methods.keys():
                try:
                    if method_name == "__init__":
                        continue
                    method = getattr(instance, method_name)
                    method()
                except Exception as e:
                    print("Could not execute " + method_name + ": " + str(e))
