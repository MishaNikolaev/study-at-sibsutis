import matplotlib.pyplot as plt
import numpy as np


def interpolation_function(x):
    return np.sqrt(x)
    # return 1 / x
    # return np.sin(x)
    # return np.cos(x)


def eitken_interpolation(points_x, points_y, x_val):
    n = len(points_x)
    P = np.zeros((n, n))

    for i in range(n):
        P[i, 0] = points_y[i]

    for j in range(1, n):
        for i in range(n - j):
            P[i, j] = ((x_val - points_x[i + j]) * P[i, j - 1] - \
                       (x_val - points_x[i]) * P[i + 1, j - 1]) / \
                      (points_x[i] - points_x[i + j])

    return P[0, n - 1]


def draw_graph(points_x, points_y, blue_x, blue_y, x_step=10.0):
    plt.figure(figsize=(12, 8))

    plt.axhline(0, color='black', linestyle='-', linewidth=0.8)
    plt.axvline(0, color='black', linestyle='-', linewidth=0.8)

    x_min = min(points_x) - x_step
    x_max = max(points_x) + x_step
    x_vals = np.linspace(x_min, x_max, 1000)

    y_eitken = [eitken_interpolation(points_x, points_y, x) for x in x_vals]
    plt.plot(x_vals, y_eitken, 'b-', label=f'Интерполяция Эйткена (N={len(points_x)})', linewidth=2)

    x_vals_pos = np.linspace(0.01 if interpolation_function(0) == np.inf else 0, x_max, 500)
    y_func = interpolation_function(x_vals_pos)
    plt.plot(x_vals_pos, y_func, 'r-', label=f'y = f(x)', linewidth=2)

    plt.scatter(points_x, points_y, color='black', s=100, label='Точки интерполяции', zorder=5)

    y_min = min(min(y_eitken), min(y_func), 0) - 1
    y_max = max(max(y_eitken), max(y_func)) + 1

    plt.title(f'Интерполяция Эйткена (N={len(points_x)}) для функции', fontsize=16)
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

        if x0 < 0:
            raise ValueError("x0 должен быть больше или равен 0")
        if n < 2:
            raise ValueError("Количество точек должно быть не менее 2")
        if h <= 0:
            raise ValueError("Шаг должен быть положительным числом")

        points_x = [x0 + i * h for i in range(n)]
        points_y = [interpolation_function(x) for x in points_x]

        blue_x = (points_x[0] + points_x[-1]) / 2
        blue_y = eitken_interpolation(points_x, points_y, blue_x)

        draw_graph(points_x, points_y, blue_x, blue_y, h)

    except Exception as e:
        print(f"Произошла ошибка: {e}")