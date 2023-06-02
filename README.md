# Library Sort: Implementation and Analysis (Project)

## Description

Insertion sort is a simple sorting algorithm that builds the final sorted array one item at a time. It is much less efficient on large lists than more advanced algorithms such as quicksort.

Library sort is a modification of insertion sort that gains speed by trading space. It is also known as gapped insertion sort.

## How to run

```bash
chmod +x run.sh
./run.sh
```

OR

```bash
make
./gentests 7 # creates files upto 1e7
python3 distribution.py
python3 test.py
python3 epsilons.py
```