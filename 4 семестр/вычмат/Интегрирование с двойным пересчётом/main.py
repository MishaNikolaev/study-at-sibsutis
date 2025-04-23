import numpy as np
from scipy.integrate import quad as itg


def fun(x):
    return 1 / x


def orig(l, r):
    return itg(fun, l, r)[0]


def Trapez(xs, xe, h):
    x = np.arange(xs, xe + h, h)
    y = [fun(i) for i in x]
    result = 0
    for i in range(1, len(x)):
        result += h * ((y[i] + y[i - 1]) / 2)
    return result


def Simpson(xs, xe, h):
    x = np.arange(xs, xe + h, h)
    y = [fun(i) for i in x]
    result = 0
    for i in range(2, len(x), 2):
        result += (2 * h) * ((y[i] + y[i - 2]) / 6 + y[i - 1] * (2 / 3))
    return result

print("hello ruban")

def main():
    e = 10 ** (-8)
    h = 0.1
    a, b = 1, 2
    #org = functions.orig(a, b)
    rt = 0
    step = 0
    print("Формула трапеции")
    while fabs(org - rt) > e:
        step += 1
        rt = functions.Trapez(a, b, h)
        print("---------------------------")
        print("Шаг:", step)
        print("h:", h)
        print("Оригинальная функция:", org)
        print("Результат:", rt)
        h /= 2

    rs = 0
    step = 0
    h = 0.1
    print("---------------------------\n\nФомрула Симпсона")
    while fabs(org - rs) > e:
        step += 1
        #rs = functions.Simpson(a, b, h)
        print("---------------------------")
        print("Шаг:", step)
        print("h:", h)
        print("Оригинальная функция:", org)
        print("Результат:", rs)
        h /= 2


if __name__ == '__main__':
    main()
