import matplotlib.pyplot as plt
import math
import numpy as np

results = []
input_file = "/Users/NadahFeteih/Desktop/cse221/benchmarking/file_reads/results.out"
with open(input_file, "r") as fp:
    for line in fp:
        float_list = [float(i) for i in line.split()]
        results.append(float_list)
# print(results)

if results[0].__len__() == 2:

    sizes = list(map(lambda r: r[0], results))
    values_ms = list(map(lambda r: r[1]/(2.7*1000), results))

    plt.xlabel('File size (MB)')
    plt.ylabel('Read latency (Micro-seconds)')
    plt.title('Avg. read latency vs file size')
    plt.plot(sizes, values_ms, color="black")
    plt.show()