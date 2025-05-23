import numpy as np
import matplotlib.pyplot as plt
from matplotlib.ticker import MultipleLocator


def custom_function(x):
    return np.sqrt(x)


def cubic_spline(x_val, x_arr, y_arr, h, M, n):
    i = 0
    while i < n - 1 and x_val > x_arr[i + 1]:
        i += 1

    if i >= n - 1:
        i = n - 2

    dx = x_val - x_arr[i]
    term1 = M[i] * np.power(x_arr[i + 1] - x_val, 3) / (6.0 * h[i])
    term2 = M[i + 1] * np.power(x_val - x_arr[i], 3) / (6.0 * h[i])
    term3 = (y_arr[i] - M[i] * h[i] * h[i] / 6.0) * (x_arr[i + 1] - x_val) / h[i]
    term4 = (y_arr[i + 1] - M[i + 1] * h[i] * h[i] / 6.0) * (x_val - x_arr[i]) / h[i]

    return term1 + term2 + term3 + term4


def gauss(matrix, size):
    solution = np.zeros(size)

    for i in range(size):
        max_row = i
        for k in range(i + 1, size):
            if abs(matrix[k][i]) > abs(matrix[max_row][i]):
                max_row = k

        matrix[[i, max_row]] = matrix[[max_row, i]]

        for k in range(i + 1, size):
            factor = matrix[k][i] / matrix[i][i]
            for j in range(i, size + 1):
                matrix[k][j] -= factor * matrix[i][j]

    for i in range(size - 1, -1, -1):
        solution[i] = matrix[i][size]
        for j in range(i + 1, size):
            solution[i] -= matrix[i][j] * solution[j]
        solution[i] /= matrix[i][i]

    return solution


def setup_spline_system(x_arr, y_arr, h, n):
    if n <= 2:
        return None

    mat = np.zeros((n - 2, n - 1))

    for i in range(n - 2):
        if i > 0:
            mat[i][i - 1] = h[i] / 6.0
        mat[i][i] = (h[i] + h[i + 1]) / 3.0
        if i < n - 3:
            mat[i][i + 1] = h[i + 1] / 6.0

        mat[i][n - 2] = ((y_arr[i + 2] - y_arr[i + 1]) / h[i + 1] - \
                         ((y_arr[i + 1] - y_arr[i]) / h[i]))

    return mat


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


def draw_graph(x_arr, y_arr, h, M, n):
    plt.figure(figsize=(12, 8))

    x_min = x_arr[0] - h[0]
    x_max = x_arr[-1] + h[-1]
    if x_min < 0:
        x_min = 0

    x_original = np.linspace(0.01 if x_min == 0 else x_min, x_max, 500)
    y_original = custom_function(x_original)

    x_spline = np.linspace(x_min, x_max, 1000)
    y_spline = [cubic_spline(x, x_arr, y_arr, h, M, n) for x in x_spline]

    if x_arr[0] > 3:
        y_min, y_max = calculate_y_limits_new(x_arr, y_arr, custom_function)
    else:
        y_min, y_max = calculate_y_limits_old(y_spline, y_original, y_arr)
        y_min = max(0, y_min)

    y_step = calculate_y_step(y_min, y_max)

    plt.plot(x_original, y_original, 'r-', label='y = √x', linewidth=2)
    plt.plot(x_spline, y_spline, 'b-', label=f'Кубический сплайн (N={n})', linewidth=2)
    plt.scatter(x_arr, y_arr, color='black', s=100, label='Точки интерполяции', zorder=5)

    plt.axhline(0, color='black', linestyle='-', linewidth=0.8)
    plt.axvline(0, color='black', linestyle='-', linewidth=0.8)
    plt.grid(True, linestyle='--', alpha=0.7)

    plt.xlim(x_min, x_max)
    plt.ylim(y_min, y_max)
    plt.title(f'Кубический сплайн (N={n}) для функции y = √x', fontsize=16)
    plt.xlabel('x', fontsize=14)
    plt.ylabel('y', fontsize=14)
    plt.legend(fontsize=12, loc='upper left')

    # Разметка осей
    plt.xticks(np.arange(np.floor(x_min), np.ceil(x_max) + 1, 1))
    plt.yticks(np.arange(y_min, y_max + y_step, y_step))

    plt.tight_layout()
    plt.show()


def main():
    try:
        x0 = float(input("Введите начальную точку x0: "))
        step = float(input("Введите шаг h: "))
        n = int(input("Введите количество узлов n (>=2): "))

        if n < 2:
            raise ValueError("n должно быть >= 2")

        x_arr = np.array([x0 + i * step for i in range(n)])
        y_arr = np.array([custom_function(x) for x in x_arr])

        h = np.array([x_arr[i + 1] - x_arr[i] for i in range(n - 1)])

        M = np.zeros(n)
        if n > 2:
            mat = setup_spline_system(x_arr, y_arr, h, n)
            solution = gauss(mat, n - 2)
            M[1:-1] = solution

        draw_graph(x_arr, y_arr, h, M, n)

    except Exception as e:
        print(f"Ошибка: {e}")


if __name__ == "__main__":
    main()