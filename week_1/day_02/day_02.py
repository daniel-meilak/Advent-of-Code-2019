import os
import numpy as np
import csv

# calculate opcode
def calculate(array,index):

    if array[index] == 1:
        a = array[array[index+1]]
        b = array[array[index+2]]

        array[array[index+3]] = a + b
    elif array[index] == 2:
        a = array[array[index+1]]
        b = array[array[index+2]]

        array[array[index+3]] = a * b
    elif array[index] == 99:
        return 1
    else:
        print("opcode must be one of [1,2,99]")
    return 0

# set array position 1 and 2
def set_ab(a,b,array):
    array[1] = a
    array[2] = b

# read csv into numpy array
with open(os.path.join(os.sys.path[0],'input')) as file:
    reader = csv.reader(file)
    y = np.array(list(reader)[0],dtype=int)

# value copy of y (NOT REFERENCE ugh python)
y_save = np.copy(y)

done = False
# brute force answer
for i in range(0,100,1):
    for j in range(0,100,1):
        set_ab(i,j,y)

        for k in range(0,y.shape[0],4):
            if calculate(y,k):
                break


        if y[0] == 19690720:
            print("noun: ", y[1])
            print("verb: ", y[2])
            done = True
            break

        y = np.copy(y_save)
    if done:
        break

print(y[0])
