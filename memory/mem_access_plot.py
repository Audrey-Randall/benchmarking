import matplotlib.pyplot as plt
import math

results = []
input_file = "/home/anil/Desktop/benchmarking/memory/results8.out"
with open(input_file, "r") as fp:
    for line in fp:
        float_list = [float(i) for i in line.split()]
        results.append(float_list)
print(results)

# Remove outliers
results = list(filter(lambda r: r[2] < 300, results))

# log_sizes = list(map(lambda r: math.log(r[0]), results))
# values = list(map(lambda r: r[2], results))
strides = set(list(map(lambda r: r[1], results)))

for stride in strides:
    results_for_stride = list(filter(lambda r: r[1] == stride, results))
    log_sizes = list(map(lambda r: math.log(r[0], 2), results_for_stride))
    values = list(map(lambda r: r[2], results_for_stride))
    plt.plot(log_sizes, values, label=str(stride))

# plt.plot(log_sizes, values)
# plt.legend()
# plt.show()
plt.xlabel('Log2 (Array size - number of integers)')
plt.ylabel('CPU cycles')
plt.title('Memory access latency')
plt.text(60, .025, r'$\mu=100,\ \sigma=15$')
plt.savefig('/home/anil/Desktop/benchmarking/memory/plot8.eps', format='eps')
