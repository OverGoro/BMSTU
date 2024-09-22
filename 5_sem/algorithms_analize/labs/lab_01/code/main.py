import random as r
import time
import matplotlib.pyplot as plt
import numpy as np

def head(str: str) -> str:
    return str[0]

def tail(str: str) -> str:
    return str[1:]


def levenshtein_distance_recursion(str1: str, str2: str) -> int:
    if len(str1) == 0:
        return len(str2)
    elif len(str2) == 0:
        return len(str1)
    elif (head(str1) == head(str2)):
        return levenshtein_distance_recursion(tail(str1), tail(str2))
    return 1 + min(
        levenshtein_distance_recursion(tail(str1), str2),
        levenshtein_distance_recursion(str1, tail(str2)),
        levenshtein_distance_recursion(tail(str1), tail(str2)))

def levenshtein_distance_mem(str1: str, str2: str) -> int:
    mat = [[0] * (len(str2) + 1) for i in range(len(str1) + 1)]

    for j in range(len(str1) + 1):
        mat[0][j] = j

    for i in range(len(str2) + 1):
        mat[i][0] = i

    for i in range(1, len(str2) + 1):
        for j in range(1, len(str1) + 1):
            mat[i][j] = min(
                    mat[i - 1][j] + 1,
                    mat[i][j - 1] + 1,
                    mat[i - 1][j - 1] + (1 if str1[j - 1] != str2[i - 1] else 0))
    return mat[-1][-1]

def damerau_levenshtein(str1: str, str2: str) -> int:
    mat = [[0] * (len(str1) + 1) for i in range(len(str2) + 1)]

    for i in range(len(str1) + 1):
        mat[0][i] = i

    for i in range(len(str2) + 1):
        mat[i][0] = i

    for i in range(1, len(str2) + 1):
        for j in range(1, len(str1) + 1):
            if (i > 1 and j > 1 and str2[i - 1] == str1[j - 2] and str2[i - 2] == str1[j - 1]):
                mat[i][j] = min(
                    mat[i - 2][j - 2] + 1,
                    mat[i - 1][j - 1] + (1 if str1[j - 1] != str2[i - 1] else 0),
                    mat[i][j - 1] + 1,
                    mat[i - 1][j] + 1
                )
            else:
                mat[i][j] = min(
                    mat[i - 1][j] + 1,
                    mat[i][j - 1] + 1,
                    mat[i - 1][j - 1] + (1 if str1[j - 1] != str2[i - 1] else 0)
                )
    return mat[-1][-1]

def measure_func(str1: str, str2: str, func: callable) -> float:
    start_time = time.process_time()
    func(str1, str2)
    end_time = time.process_time()
    return (end_time - start_time) * 1000000
    

def measure_range(min_len: int, max_len: int, measures_num: int, *funcs: callable) -> list[list[float]]:
    results = []

    for cur_len in range(min_len, max_len + 1):   
        words_1 = []
        words_2 = []
        for i in range(measures_num):
            words_1.append(''.join(r.choices('abcdefghijklmnopqrstuvwxyz', k=cur_len)))
            words_2.append(''.join(r.choices('abcdefghijklmnopqrstuvwxyz', k=cur_len)))
        measure_results = []
        for func in funcs:
            total_time = 0
            for i in range(measures_num):
                total_time += measure_func(words_1[i], words_2[i], func)
            measure_results.append(total_time / measures_num)
        results.append(measure_results)
    return results

def print_results(results: list[list[float]], names: list[str]):
    print("\t\t\t",end="")
    for n in names:
        print(n,end="")
        if (n != names[-1]):
            print(" & ",end="")
    print("\\\\\n\t\t\t\\hline")
    i = 1
    for measures in results:
        print("\t\t\t",end="")
        print(i, end=" & ")
        i += 1
        for m in measures:
            print("{:1.2f}".format(m), end="")
            if (m!= measures[-1]):
                print(" & ", end="")
        print("\\\\\n\t\t\t\\hline")


def plot_results(results: list[list[float]], names: list[str], colors: list[str]):
    fig, ax = plt.subplots()
    y = np.array(results)
    x = np.arange(1, len(results) + 1)

    for i in range(len(results[0])):
        ax.plot(x, y[:, i], label=names[i], color=colors[i])  # Добавлен параметр color
    ax.set_xlabel('Длина слова(в символах)')
    ax.set_ylabel('Время(мкс)')
    ax.set_title('Сравнение алгоритмов по времени')
    ax.legend()
    plt.show()


if __name__ == '__main__':
    results = measure_range(1, 8, 100, levenshtein_distance_recursion, levenshtein_distance_mem, damerau_levenshtein)
    print_results(results, ['Длина строк(символов)', 'Лев.(рек.)', 'Лев.(мат.)', 'Дам.-Лев.(мат.)'])
    colors = ['red', 'blue', 'green']  # Определение цветов для каждого алгоритма
    plot_results(results, ['Левенштейна (рекурсивный)', 'Левенштейна (матричный)', 'Дамерау-Левенштейна (матричный)'], colors)
    colors = ['blue', 'green']  # Определение цветов для каждого алгоритма
    
    for i in range(len(results)):
        results[i] = results[i][1:]
    
    print(results)
    plot_results(results, ['Левенштейна (матричный)', 'Дамерау-Левенштейна (матричный)'], colors)