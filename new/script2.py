import subprocess as sp
import matplotlib.pyplot as plt
lrandom_insertion = []
lrandom_quick = []
lrandom_library = []


sp.call(["g++", "library_sort.cpp"])
l1 = []
for i in range(1, 6):
    tmp = sp.run(["./a.out", f"testcase_1e{i}_random.txt"], capture_output=True, text=True)
    l1.append(tmp.stdout)
    lrandom_library = l1[0].split("\n")
    random_l = [lrandom_library[i] for i in range(0, 5)]
print(random_l)




sp.call(["g++", "quick_sort.cpp"])
l2 = []
tmp = sp.run(["./a.out", "random"], capture_output=True, text=True)
l2.append(tmp.stdout)
lrandom_quick = l2[0].split("\n")
random_q = [lrandom_quick[i] for i in range(0, 5)]
print(random_q)



sp.call(["g++", "insertion_sort.cpp"])
l = []
tmp = sp.run(["./a.out", "random"], capture_output=True, text=True)
l.append(tmp.stdout)
print(l)
lrandom_insertion = l[0].split("\n")
random_i = [lrandom_insertion[i] for i in range(0, 5)]
print(random_i)



n_list = [10**i for i in range(1, 6)]
plt.plot(n_list, random_i, linestyle = "solid", color = "red")
plt.plot(n_list, random_q, linestyle = "solid", color = "green")
plt.plot(n_list, random_l, linestyle = "solid", color = "blue")
plt.yticks([])
plt.legend(["Insertion Sort", "Quick Sort", "Library Sort"])
plt.ylabel("Time Required")
plt.xlabel("Value of N(Matrix Dimension)")
plt.xscale("log")
plt.show()