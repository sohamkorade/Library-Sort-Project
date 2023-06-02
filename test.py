import subprocess as sp
import matplotlib.pyplot as plt
import pandas as pd
import tempfile

max_power_of_10 = 5
saved = False

powers = range(1, max_power_of_10 + 1)

sorts = [
    'insertion_sort',
    'quick_sort',
    'library_sort',
    'std_sort',
]

types = [
    "shuffled",
    "all_equal",
    "ascending",
    "descending",
    "pipe_organ",
    "push_front",
    "push_middle",
    "nearly_sorted",
    "sawtooth",
]

if not saved:
    processes = []
    for i in powers:
        print(f"1e{i}")
        for type in types:
            for sort_algo in sorts:
                # print(f"{sort_algo} {type} 1e{i} ")
                f = tempfile.TemporaryFile(mode="w+")
                p = sp.Popen([
                    "./sort",
                    f"testcases/1e{i}_{type}.txt",
                    sort_algo,
                    "output.txt",
                ],
                             stderr=f,
                             text=True)
                processes.append((p, f, sort_algo, type, i))

    data = []
    while True:
        if len(processes) == 0:
            break
        for p, f, sort_algo, type, i in processes:
            if p.poll() is None:
                continue
            p.wait()
            f.seek(0)
            ns = int(f.read().strip())
            f.close()
            if i > 4:
                print(f"{sort_algo} {type} 1e{i} done in {ns} ns")
            data.append([sort_algo, type, 10**i, ns])
            processes.remove((p, f, sort_algo, type, i))

    # save data
    df = pd.DataFrame(data, columns=["sort_algo", "type", "size", "ns"])
    df.to_csv("data.csv")
else:
    df = pd.read_csv("data.csv")

# print(df)

# plot all plots as subplots
plt.figure(figsize=(20, 10))
plt.style.use("ggplot")
plt.subplots_adjust(hspace=0.5, wspace=0.5)

for i, type in enumerate(types):
    plt.subplot(3, 3, i + 1)
    for sort_algo in sorts:
        temp_df = df.where(df["sort_algo"] == sort_algo).where(
            df["type"] == type).dropna()
        plt.plot(temp_df["size"], temp_df["ns"], linestyle="solid")
    plt.title(type)

plt.xlabel("Input Size")
plt.ylabel("Time")

plt.figlegend(sorts)
plt.suptitle(
    "Time taken by different sorting algorithms for different input distributions"
)
plt.savefig("all_plots.png")
plt.show()