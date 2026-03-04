import os

options = "-l"

# Using .format() to create the string (acts as the print/format function)
command = "ls {}".format(options)

# Executing the command
os.system(command)