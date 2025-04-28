import matplotlib.pyplot as plt
import numpy as np


def interpolation_function(x):
    return np.sqrt(x)
    # return 1 / x
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


def draw_graph(points_x, points_y, blue_x, blue_y, x_step=1.0):
    plt.figure(figsize=(12, 8))

    # Оси координат
    plt.axhline(0, color='black', linestyle='-', linewidth=0.8)
    plt.axvline(0, color='black', linestyle='-', linewidth=0.8)

    # Определяем диапазон для графика
    x_min = min(min(points_x) - x_step, 0)  # Всегда включаем 0
    x_max = max(points_x) + x_step

    # Генерируем точки для интерполяционной кривой
    x_vals = np.linspace(x_min, x_max, 1000)
    y_lagrange = [lagrange_interpolation(points_x, points_y, x) for x in x_vals]

    # Строим интерполяционную кривую
    plt.plot(x_vals, y_lagrange, 'b-', label=f'Интерполяция Лагранжа (N={len(points_x)})', linewidth=2)

    # График исходной функции
    x_vals_pos = np.linspace(max(0, x_min), x_max, 500)  # Только положительные x для sqrt(x)
    y_func = interpolation_function(x_vals_pos)
    plt.plot(x_vals_pos, y_func, 'r-', label='y = sqrt(x)', linewidth=2)

    # Контрольные точки
    plt.scatter(points_x, points_y, color='black', s=100, label='Контрольные точки', zorder=5)

    # Вертикальные пунктирные линии только для контрольных точек
    for x, y in zip(points_x, points_y):
        plt.plot([x, x], [0, y], 'k--', alpha=0.3, linewidth=0.8)

    # Автоматическое масштабирование с учетом всех кривых
    all_y = np.concatenate([y_lagrange, y_func, points_y])
    y_min = min(all_y) - 0.5
    y_max = max(all_y) + 0.5

    plt.title(f'Интерполяция Лагранжа (N={len(points_x)}) для функции sqrt(x)', fontsize=16)
    plt.xlabel('x', fontsize=14)
    plt.ylabel('y', fontsize=14)

    plt.xlim(x_min, x_max)
    plt.ylim(y_min, y_max)

    plt.grid(True, linestyle='--', alpha=0.7)
    plt.legend(fontsize=12, loc='upper left')

    # Настройка делений на осях
    x_ticks = np.arange(round(x_min), round(x_max) + 1, 1)
    plt.xticks(x_ticks)

    y_ticks = np.arange(round(y_min), round(y_max) + 1, 0.5)
    plt.yticks(y_ticks)

    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    try:
        x0 = float(input("Введите начальную точку x0: "))
        h = float(input("Введите шаг h: "))
        n = int(input("Введите количество точек интерполяции n: "))

        if n <= 0:
            raise ValueError("Количество точек должно быть положительным числом")
        if h <= 0:
            raise ValueError("Шаг должен быть положительным числом")

        points_x = [x0 + i * h for i in range(n)]
        points_y = [interpolation_function(x) for x in points_x]

        blue_x = (points_x[0] + points_x[1]) / 2 if n > 1 else x0
        blue_y = interpolation_function(blue_x)

        draw_graph(points_x, points_y, blue_x, blue_y, h)

    except ValueError as e:
        print(f"Ошибка ввода: {e}")
    except Exception as e:
        print(f"Произошла ошибка: {e}")