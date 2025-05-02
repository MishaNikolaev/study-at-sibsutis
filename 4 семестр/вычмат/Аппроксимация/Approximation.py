import numpy as np


def gauss_lead_el(a, y):
    n = len(y)
    answers = np.zeros(n)

    for i in range(n):
        max_row = i
        for j in range(i + 1, n):
            if abs(a[j][i]) > abs(a[max_row][i]):
                max_row = j

        a[[i, max_row]] = a[[max_row, i]]
        y[i], y[max_row] = y[max_row], y[i]

        for j in range(i + 1, n):
            factor = a[j][i] / a[i][i]
            for k in range(i, n):
                a[j][k] -= a[i][k] * factor
            y[j] -= y[i] * factor

    for i in range(n - 1, -1, -1):
        answers[i] = y[i]
        for j in range(i + 1, n):
            answers[i] -= a[i][j] * answers[j]
        answers[i] /= a[i][i]

    return answers


def least_squares(x, y):
    n = len(x)
    sum_x = sum(x)
    sum_y = sum(y)
    sum_xy = sum(xi * yi for xi, yi in zip(x, y))
    sum_xx = sum(xi ** 2 for xi in x)
    sum_xxx = sum(xi ** 3 for xi in x)
    sum_xxxx = sum(xi ** 4 for xi in x)
    sum_xxy = sum(xi ** 2 * yi for xi, yi in zip(x, y))

    print("\nСуммы для системы уравнений:")
    print(f"Σx = {sum_x:.4f}")
    print(f"Σy = {sum_y:.4f}")
    print(f"Σxy = {sum_xy:.4f}")
    print(f"Σx² = {sum_xx:.4f}")
    print(f"Σx³ = {sum_xxx:.4f}")
    print(f"Σx⁴ = {sum_xxxx:.4f}")
    print(f"Σx²y = {sum_xxy:.4f}")

    matrix = np.array([
        [n, sum_x, sum_xx],
        [sum_x, sum_xx, sum_xxx],
        [sum_xx, sum_xxx, sum_xxxx]
    ])
    col = np.array([sum_y, sum_xy, sum_xxy])

    print("\nМатрица системы:")
    print(matrix)
    print("\nВектор правой части:")
    print(col)

    coef = gauss_lead_el(matrix, col)

    print("\nПосле прямого хода метода Гаусса:")
    print(matrix)

    errors = sum((yi - (coef[0] + coef[1] * xi + coef[2] * xi ** 2)) ** 2 for xi, yi in zip(x, y))

    print("\nПолученные коэффициенты:")
    print(f"a = {coef[0]:.6f}")
    print(f"b = {coef[1]:.6f}")
    print(f"c = {coef[2]:.6f}")

    return coef, errors


x = [0, 1, 2, 3]
y = [0, 1, 4, 9]

print("Входные данные:")
print("X:", " ".join(f"{xi:.3f}" for xi in x))
print("Y:", " ".join(f"{yi:.3f}" for yi in y))

coef, error = least_squares(x, y)

print("\nИтоговое уравнение:")
print(f"y = {coef[0]:.4f} + {coef[1]:.4f}x + {coef[2]:.4f}x²")