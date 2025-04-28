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


def draw_graph(x_arr, y_arr, h, M, n):
    plt.figure(figsize=(12, 8))

    x_min = x_arr[0] - 0.5 * h[0]
    x_max = x_arr[-1] + 0.5 * h[-1]
    if x_min < 0:
        x_min = 0

    x_original = np.linspace(x_min, x_max, 500)
    y_original = custom_function(x_original)

    x_spline = np.linspace(x_min, x_max, 500)
    y_spline = []
    for x in x_spline:
        if x < x_arr[0]:
            i = 0
        elif x > x_arr[-1]:
            i = n - 2
        else:
            i = 0
            while i < n - 1 and x > x_arr[i + 1]:
                i += 1

        dx = x - x_arr[i]
        term1 = M[i] * np.power(x_arr[i + 1] - x, 3) / (6.0 * h[i])
        term2 = M[i + 1] * np.power(x - x_arr[i], 3) / (6.0 * h[i])
        term3 = (y_arr[i] - M[i] * h[i] * h[i] / 6.0) * (x_arr[i + 1] - x) / h[i]
        term4 = (y_arr[i + 1] - M[i + 1] * h[i] * h[i] / 6.0) * (x - x_arr[i]) / h[i]

        y_spline.append(term1 + term2 + term3 + term4)

    plt.plot(x_original, y_original, 'b-', label='Original function (sqrt(x))', linewidth=2)
    plt.plot(x_spline, y_spline, 'r-', label='Cubic spline', linewidth=2)
    plt.scatter(x_arr, y_arr, color='green', s=100, label='Interpolation points', zorder=5)

    plt.axhline(0, color='black', linestyle='-', linewidth=0.8)
    plt.axvline(0, color='black', linestyle='-', linewidth=0.8)

    y_min = min(min(y_original), min(y_spline), 0)
    y_max = max(max(y_original), max(y_spline)) * 1.1

    plt.xlim(x_min, x_max)
    plt.ylim(y_min, y_max)

    plt.grid(True, linestyle='--', alpha=0.7)

    plt.title(f'Cubic Spline Interpolation (N={n})', fontsize=16)
    plt.xlabel('x', fontsize=14)
    plt.ylabel('y', fontsize=14)
    plt.legend(fontsize=12, loc='upper left')

    x_step = max(1.0, (x_max - x_min) / 10)
    y_step = max(1.0, (y_max - y_min) / 10)

    plt.gca().xaxis.set_major_locator(MultipleLocator(x_step))
    plt.gca().yaxis.set_major_locator(MultipleLocator(y_step))

    info_text = f'Number of points: {n}\nStep size: {h[0]:.2f}'
    plt.text(0.02, 0.98, info_text, transform=plt.gca().transAxes,
             verticalalignment='top', bbox=dict(facecolor='white', alpha=0.8))

    plt.tight_layout()
    plt.show()

def main():
    try:
        x0 = float(input("Enter initial x0: "))
        step = float(input("Enter step h: "))
        n = int(input("Enter number of nodes n (>=2): "))

        if n < 2:
            raise ValueError("n must be >= 2")

        x_arr = np.array([x0 + i * step for i in range(n)])
        y_arr = np.array([custom_function(x) for x in x_arr])

        h = np.array([x_arr[i + 1] - x_arr[i] for i in range(n - 1)])
        print("\nCalculating steps h:")
        for i in range(n - 1):
            print(f"h[{i}] = {h[i]}")

        M = np.zeros(n)
        if n > 2:
            mat = setup_spline_system(x_arr, y_arr, h, n)
            solution = gauss(mat, n - 2)
            M[1:-1] = solution

        print("\nVector M:")
        for i in range(n):
            print(f"M[{i}] = {M[i]}")

        print("\nInterpolation check at nodes:")
        for i in range(n):
            xi = x_arr[i]
            si = cubic_spline(xi, x_arr, y_arr, h, M, n)
            print(f"S({xi:.2f}) = {si:.6f} ({y_arr[i]:.6f})")

        draw_graph(x_arr, y_arr, h, M, n)

    except Exception as e:
        print(f"Error: {e}")


if __name__ == "__main__":
    main()