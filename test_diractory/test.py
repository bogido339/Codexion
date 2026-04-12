for square in range(9):
    for i in range(3):
        for j in range(3):
            row = (square//3) * 3 + i
            col = (square % 3) * 3 + j
            print("row", row)
            print("col", col)
    print("*******")