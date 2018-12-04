import matplotlib.pyplot as plt
import math
import numpy as np

results = []

input_file = "results.txt"
with open(input_file, "r") as fp:
    for line in fp:
        float_list = [float(i) for i in line.split()]
        float_list = [x for x in float_list if ~np.isnan(x)]
        if float_list.__len__() == 3:
            results.append(float_list)

print (results)

if results[0].__len__() == 3:

    sizes = list(map(lambda r: r[0], results))
    random_access_ms = list(map(lambda r: r[1]/(2.7*1000), results))
    sequential_access_ms = list(map(lambda r: r[2]/(2.7*1000), results))
    
    plt.xlabel('File size (MB)')
    plt.ylabel('Random and Sequential File Access')
    plt.title('Avg. read latency vs file size')
    plt.plot(sizes, random_access_ms, color="black", label="Random File Access", marker="x")
    plt.plot(sizes, sequential_access_ms, color="black", label="Sequential File Access", marker="o")
    plt.legend()
    plt.show()
