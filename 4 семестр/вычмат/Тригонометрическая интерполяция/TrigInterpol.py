import numpy as np
import matplotlib.pyplot as plt
import math


def trigonometric_interpolation(x_arr, y_arr, x, h, n):
    n = len(x_arr)
    h = x_arr[1] - x_arr[0]
    Aj = lambda j: sum(y_arr[k] * np.exp(-2j * np.pi * k * j / n) for k in range(n))

    tmp = (1 / n) * sum(Aj(j) * np.exp(2j * np.pi * j * (x - x_arr[0]) / (n * h))
                        for j in range(-n // 2 + 1, n // 2 + 1))
    return tmp


def draw_graph(x_data, y_data, x_min, x_max, h, n):
    plt.figure(figsize=(12, 6))
    plt.grid(True)

    x_range = x_max - x_min
    y_range = max(y_data) - min(y_data)
    x_min_extended = x_min - 0.2 * x_range
    x_max_extended = x_max + 0.2 * x_range
    y_min_extended = min(y_data) - 0.2 * y_range
    y_max_extended = max(y_data) + 0.2 * y_range

    x_fine = np.linspace(max(0, x_data[0] - 0.5), x_data[-1] + 1, 1000)
    y_fine = f(x_fine)
    plt.plot(x_fine, y_fine, color="blue", label='Исходная функция')

    x_plot = np.linspace(x_min_extended, x_max_extended, 1000)
    y_interp = [trigonometric_interpolation(x_data, y_data, xi, h, n) for xi in x_plot]

    y_real = np.real(y_interp)
    y_imag = np.imag(y_interp)

    plt.plot(x_plot, y_real, color="purple", label='Вещественная часть интерполяции')
    plt.plot(x_plot, y_imag, color="green", label='Мнимая часть интерполяции')

    plt.scatter(x_data, y_data, color='red', s=50, label='Узлы интерполяции')

    plt.axhline(0, color='red', linewidth=0.5)
    plt.axvline(0, color='red', linewidth=0.5)

    plt.xlim(x_min_extended, x_max_extended)

    y_min_int = math.floor(min(min(y_real), min(y_imag), min(y_data), 0))
    y_max_int = math.ceil(max(max(y_real), max(y_imag), max(y_data)))
    plt.ylim(y_min_int, y_max_int)

    plt.title(f'Тригонометрическая интерполяция')
    plt.xlabel('x')
    plt.ylabel('y')

    plt.yticks(np.arange(y_min_int, y_max_int + 1, 1))

    plt.legend(bbox_to_anchor=(0, 1), loc='upper left', borderaxespad=0.)
    plt.grid(True)
    plt.tight_layout()
    plt.show()


def f(x):
     return (1/x)
    #return np.sqrt(x)


if __name__ == "__main__":
    try:
        x0 = float(input("Введите начальную точку x0: "))
        h = float(input("Введите шаг h: "))
        n = int(input("Введите количество точек интерполяции n: "))

        if f.__name__ == 'sqrt':
            if x0 < 0:
                raise ValueError("Для функции sqrt(x) начальная точка должна быть >= 0")

        x_data = np.arange(x0, x0 + n * h, h)
        y_data = f(x_data)

        x_min = x_data[0]
        x_max = x_data[-1]

        draw_graph(x_data, y_data, x_min, x_max, h, n)

    except Exception as e:
        print(f"Произошла ошибка: {e}")