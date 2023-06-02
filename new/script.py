import subprocess as sp
import matplotlib.pyplot as plt

lrandom_insertion = []
lrandom_quick = []
lrandom_library = []

max_power_of_10 = 5
powers = range(1, max_power_of_10 + 1)

# sorts = ['insertion_sort', 'quick_sort', 'library_sort']

# library sort with different values of epsilon
sorts = [
    'library_sort_1', 'library_sort_2', 'library_sort_3', 'library_sort_4',
    'library_sort_5'
]

types = ['nearly_sorted', 'random', 'reverse']

sp.call(["g++", "sort.cpp", "-Ofast"])

values = {}
for t in types:
    types_data = {}
    for sort_algo in sorts:
        algo_data = []
        for i in powers:
            tmp = sp.run(
                [
                    "./a.out",
                    f"testcase_1e{i}_{t}.txt",
                    sort_algo[0],  # sort_algo
                    sort_algo[-1],  # epsilon
                ],
                capture_output=True,
                text=True)
            ms = tmp.stderr
            ms = int(ms.strip())
            algo_data.append(ms)
            print(f"{sort_algo} type: {t} n: 1e{i} time: {ms}ms")
        types_data[sort_algo] = algo_data
    values[t] = types_data

n_list = [10**i for i in powers]

import pprint

pprint.pprint(values)

for t in types:
    for sort_algo in sorts:
        plt.plot(n_list, values[t][sort_algo], linestyle="solid")

    plt.yticks([])
    plt.legend(sorts)
    plt.title(t)
    plt.ylabel("Time Required")
    plt.xlabel("Array Size")
    plt.xscale("log")
    plt.show()