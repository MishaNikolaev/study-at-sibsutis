import matplotlib.pyplot as plt
import numpy as np

def interpolation_function(x):
    return np.sqrt(x)

        #if isinstance(x, (list, np.ndarray)):
        #    with np.errstate(divide='ignore', invalid='ignore'):
        #        result = np.where(x != 0, 1 / x, np.inf)
        #    return result
        #else:
        #    return 1 / x if x != 0 else np.inf

    # return np.sin(x)
    # return np.cos(x)

def lagrange_interpolation(points_x, points_y, x):
    result = 0.0
    n = len(points_x)
    for i in range(n):
        term = points_y[i]
        for j in range(n):
            if i != j:
                term *= (x - points_x[j]) / (points_x[i] - points_x[j])
        result += term
    return result

def draw_graph(points_x, points_y, blue_x, blue_y, x_step=10.0):
    plt.figure(figsize=(12, 8))

    plt.axhline(0, color='black', linestyle='-', linewidth=0.8)
    plt.axvline(0, color='black', linestyle='-', linewidth=0.8)

    x_min = min(points_x) - x_step
    x_max = max(points_x) + x_step
    x_vals = np.linspace(x_min, x_max, 1000)

    y_lagrange = [lagrange_interpolation(points_x, points_y, x) for x in x_vals]
    plt.plot(x_vals, y_lagrange, 'b-', label=f'Интерполяция Лагранжа (N={len(points_x)})', linewidth=2)

    x_vals_pos = np.linspace(0.01 if interpolation_function(0) == np.inf else 0, x_max, 500)
    y_func = interpolation_function(x_vals_pos)
    plt.plot(x_vals_pos, y_func, 'r-', label=f'y = f(x)', linewidth=2)

    plt.scatter(points_x, points_y, color='black', s=100, label='Точки интерполяции', zorder=5)

    #for x, y in zip(points_x + [blue_x], points_y + [blue_y]):
    #    plt.plot([x, x], [0, y], 'k--', alpha=0.3, linewidth=0.8)
    #    plt.plot([0, x], [y, y], 'k--', alpha=0.3, linewidth=0.8)

    y_min = min(min(y_lagrange), min(y_func), 0) - 1
    y_max = max(max(y_lagrange), max(y_func)) + 1

    plt.title(f'Интерполяция Лагранжа (N={len(points_x)}) для функции', fontsize=16)
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

        points_x = [x0 + i * h for i in range(n)]
        points_y = [interpolation_function(x) for x in points_x]

        blue_x = (points_x[0] + points_x[1]) / 2 if n > 1 else x0
        blue_y = interpolation_function(blue_x)

        draw_graph(points_x, points_y, blue_x, blue_y, h)

    except Exception as e:
        print(f"Произошла ошибка: {e}")