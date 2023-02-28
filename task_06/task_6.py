def main():
    valid_partitions = set()
    corrupted_partitions = list()

    m = int(input())
    n = int(input())
    for _ in range(n):
        a, b = map(int, input().split())

        for partition in valid_partitions:
            # Newly created partition starts or ends within existing
            # partition.
            if partition[0] <= a <= partition[1] or \
                    partition[0] <= b <= partition[1]:
                corrupted_partitions.append(partition)
            # Newly created partition contains existing partition.
            elif a < partition[0] and partition[1] < b:
                corrupted_partitions.append(partition)

        for partition in corrupted_partitions:
            valid_partitions.remove(partition)

        valid_partitions.add((a, b))
        corrupted_partitions.clear()

    print(len(valid_partitions))
    return


if __name__ == '__main__':
    main()
