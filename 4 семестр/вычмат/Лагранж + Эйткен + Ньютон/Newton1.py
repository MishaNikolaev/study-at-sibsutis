import matplotlib.pyplot as plt
import numpy as np
import math


def interpolation_function(x):
    return np.sqrt(x)
    #return 1 / x if x != 0 else np.inf
    # return np.sin(x)
    # return np.cos(x)


def calc_d(points_x, points_y):
    n = len(points_x)
    diff = np.zeros((n, n))
    diff[:, 0] = points_y

    for j in range(1, n):
        for i in range(n - j):
            diff[i][j] = diff[i + 1][j - 1] - diff[i][j - 1]

    return diff


def newton_interpolation_first(points_x, points_y, x):
    n = len(points_x)
    diff = calc_d(points_x, points_y)
    h = points_x[1] - points_x[0]
    q = (x - points_x[0]) / h

    result = points_y[0]
    term = q

    for i in range(1, n):
        result += term * diff[0][i] / math.factorial(i)
        term *= (q - i)

    return result


def draw_graph(points_x, points_y, blue_x, blue_y, x_step=1.0):
    plt.figure(figsize=(12, 8))

    plt.axhline(0, color='black', linestyle='-', linewidth=0.8)
    plt.axvline(0, color='black', linestyle='-', linewidth=0.8)

    x_min = min(points_x) - x_step
    x_max = max(points_x) + x_step
    x_vals = np.linspace(x_min, x_max, 1000)

    x_vals = [x for x in x_vals if x != 0]
    y_newton = [newton_interpolation_first(points_x, points_y, x) for x in x_vals]
    plt.plot(x_vals, y_newton, 'b-', label=f'Интерполяция Ньютона (N={len(points_x)})', linewidth=2)

    x_vals_pos = np.linspace(x_min, x_max, 500)
    x_vals_pos = [x for x in x_vals_pos if x != 0]
    y_func = [interpolation_function(x) for x in x_vals_pos]
    plt.plot(x_vals_pos, y_func, 'r-', label=f'y = f(x)', linewidth=2)

    plt.scatter(points_x, points_y, color='black', s=100, label='Точки интерполяции', zorder=5)

    y_all = y_newton + y_func
    y_finite = [y for y in y_all if not np.isinf(y)]
    y_min = min(y_finite) - 1 if y_finite else -10
    y_max = max(y_finite) + 1 if y_finite else 10

    plt.title(f'Интерполяция Ньютона (N={len(points_x)}) для функции', fontsize=16)
    plt.xlabel('x', fontsize=14)
    plt.ylabel('y', fontsize=14)

    plt.xlim(x_min, x_max)
    plt.ylim(y_min, y_max)

    plt.grid(True, linestyle='--', alpha=0.7)
    plt.legend(fontsize=12, loc='upper left')

    plt.xticks(np.arange(round(x_min), round(x_max) + 1, 1))
    plt.yticks(np.arange(round(y_min), round(y_max) + 1, 1))

    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    try:
        x0 = float(input("Введите начальную точку x0: "))
        h = float(input("Введите шаг h: "))
        n = int(input("Введите количество точек интерполяции n: "))

        if interpolation_function(0) == np.inf:
            if x0 == 0 or any(x0 + i * h == 0 for i in range(n)):
                raise ValueError("Для функции 1/x точки интерполяции не могут включать x=0")

        points_x = [x0 + i * h for i in range(n)]
        points_y = [interpolation_function(x) for x in points_x]

        blue_x = (points_x[0] + points_x[-1]) / 2
        blue_y = newton_interpolation_first(points_x, points_y, blue_x)

        draw_graph(points_x, points_y, blue_x, blue_y, h)

    except Exception as e:
        print(f"Произошла ошибка: {e}")