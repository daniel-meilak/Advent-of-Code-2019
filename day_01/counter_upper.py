import numpy as np

def fuel_for_mass(mass):
    fuel = int(mass/3) - 2

    if (int(fuel/3) -2) <= 0:
        return fuel
    else:
        return (fuel + fuel_for_mass(fuel))

input_file = "input"

y = np.loadtxt(input_file)

total = 0
for i in range(0,y.shape[0],1):
    total += fuel_for_mass(y[i])

print("Total fuel required: ", total)
