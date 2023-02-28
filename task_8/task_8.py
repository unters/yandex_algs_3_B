def main():
    top_right = None
    bottom_left = None

    k = int(input())
    for _ in range(k):
        x, y = map(int, input().split())

        if top_right is None:
            top_right = [x, y]
        if bottom_left is None:
            bottom_left = [x, y]

        if x < bottom_left[0]:
            bottom_left[0] = x
        if x > top_right[0]:
            top_right[0] = x
        if y > top_right[1]:
            top_right[1] = y
        if y < bottom_left[1]:
            bottom_left[1] = y

    print(f'{bottom_left[0]} {bottom_left[1]} {top_right[0]} {top_right[1]}')
    return

if __name__ == '__main__':
    main()
