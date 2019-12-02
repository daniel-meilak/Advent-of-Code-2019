import numpy as np
import csv

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

def set_ab(a,b,array):
    array[1] = a
    array[2] = b

with open('input.txt') as file:
    reader = csv.reader(file)
    y = np.array(list(reader)[0],dtype=int)

y_save = np.copy(y)

done = False
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
