import matplotlib.pyplot as plt
import numpy as np
import math


def interpolation_function(x):
    return np.sqrt(x)


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


def calculate_y_limits_new(points_x, points_y, func):
    x_min = min(points_x)
    x_max = max(points_x)
    x_vals = np.linspace(x_min, x_max, 100)
    y_func = func(x_vals)
    all_y = np.concatenate([y_func, points_y])
    y_min = max(0, np.min(all_y) * 0.9)
    y_max = np.max(all_y) * 1.1
    return y_min, y_max


def calculate_y_limits_old(*y_sequences):
    all_values = [val for seq in y_sequences for val in seq]
    return min(all_values), max(all_values)


def calculate_y_step(y_min, y_max):
    y_range = y_max - y_min
    if y_range < 1:
        return 0.2
    elif y_range < 2:
        return 0.5
    else:
        return 1.0


def draw_graph(points_x, points_y, blue_x, blue_y, x_step=10.0):
    plt.figure(figsize=(12, 8))

    plt.axhline(0, color='black', linestyle='-', linewidth=0.8)
    plt.axvline(0, color='black', linestyle='-', linewidth=0.8)

    x_min = min(points_x) - x_step
    x_max = max(points_x) + x_step
    x_vals = np.linspace(x_min, x_max, 1000)

    y_newton = [newton_interpolation_first(points_x, points_y, x) for x in x_vals]

    x_vals_pos = np.linspace(0.01 if interpolation_function(0) == np.inf else 0, x_max, 500)
    y_func = interpolation_function(x_vals_pos)

    if points_x[0] > 3:
        y_min, y_max = calculate_y_limits_new(points_x, points_y, interpolation_function)
    else:
        y_min, y_max = calculate_y_limits_old(y_newton, y_func, points_y)
        y_min = max(0, y_min)

    y_step = calculate_y_step(y_min, y_max)

    label = f'Интерполяция Ньютона (N={len(points_x)})'
    plt.plot(x_vals, y_newton, 'b-', label=label, linewidth=2)
    plt.plot(x_vals_pos, y_func, 'r-', label='y = √x', linewidth=2)
    plt.scatter(points_x, points_y, color='black', s=100, label='Точки интерполяции', zorder=5)

    plt.title(f'Интерполяция Ньютона (N={len(points_x)}) для функции y = √x', fontsize=16)
    plt.xlabel('x', fontsize=14)
    plt.ylabel('y', fontsize=14)

    plt.xlim(x_min, x_max)
    plt.ylim(y_min, y_max)

    plt.grid(True, linestyle='--', alpha=0.7)
    plt.xticks(np.arange(np.floor(x_min), np.ceil(x_max) + 1, 1))
    plt.yticks(np.arange(y_min, y_max + y_step, y_step))

    plt.legend(fontsize=12, loc='upper left')
    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    try:
        x0 = float(input("Введите начальную точку x0: "))
        h = float(input("Введите шаг h: "))
        n = int(input("Введите количество точек интерполяции n: "))

        points_x = [x0 + i * h for i in range(n)]
        points_y = [interpolation_function(x) for x in points_x]

        blue_x = (points_x[0] + points_x[1]) / 2 if n > 1 else x0
        blue_y = interpolation_function(blue_x)

        draw_graph(points_x, points_y, blue_x, blue_y, h)

    except Exception as e:
        print(f"Произошла ошибка: {e}")