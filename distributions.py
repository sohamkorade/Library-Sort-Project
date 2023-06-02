import matplotlib.pyplot as plt

max_power_of_10 = 5

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

# plot all plots as subplots
plt.figure(figsize=(20, 10))
plt.style.use("ggplot")
plt.subplots_adjust(hspace=0.5, wspace=0.5)

# read data
for i, type in enumerate(types):
    plt.subplot(3, 3, i + 1)
    with open(f"testcases/1e{max_power_of_10}_{type}.txt", "r") as f:
        numbers = [int(x) for x in f.read().split()]
        # scatter plot
        plt.scatter(range(len(numbers)), numbers, s=1)
        plt.title(type)

plt.suptitle("Distributions of inputs")
plt.savefig("distributions.png")
plt.show()