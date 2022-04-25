#! /usr/bin/env python

import sys
import random

# Максимально возможное значение числа.
MAX_POW = 40
SHORT_POW = 5
MIN_VALUE = 1

def get_random_int():
    return random.randint(MIN_VALUE, 100 ** random.randint(1, MAX_POW))

def get_random_short():
    return random.randint(MIN_VALUE, 10 ** random.randint(1, SHORT_POW))

def get_random_nums():
    return get_random_int(), get_random_int()

def get_random_shorts():
    return get_random_short(), get_random_short()

def get_answer(num1, num2, operation):
    if operation == "+":
        return str(num1 + num2)
    if operation == "-":
        return str(num1 - num2) if num1 >= num2 else "Error"
    if operation == "*":
        return str(num1 * num2)
    if operation == "<":
        # num1 < num2 вернёт True или False, чтобы
        # получить true или false, то сначала необходимо
        # привести его к int'у, а потом уже в строку.
        return str(num1 < num2).lower()
    if operation == "=":
        # Аналогично как для оператора <.
        return str(num1 == num2).lower()
    if operation == "/":
        return str(num1 // num2)
    if operation == "^":
        if num1 != 0 and num2 != 0:
            return str(num1 ** num2)
        else:
            return "Error"
    return None

def main():
    # Ожидаем, что будет три аргумента: название программы,
    # путь до директории с тестами и количество тестов в каждом
    # файле.
    if len(sys.argv) != 4:
        print(f"Usage: {sys.argv[0]} <tests directory> <tests count> <tests type>")
        sys.exit(1)

    # Считываем путь до папки с тестами.
    test_dir = sys.argv[1]
    # Считываем количество тестов для каждой операции.
    tests_count = int(sys.argv[2])
    tests_type = sys.argv[3]
    if (tests_type != "test" and tests_type != "benchmark"):
        print(f"Usage: {sys.argv[0]} <tests directory> <tests count> <tests type>")
        print(f"illegal tests type = {tests_type}")
        sys.exit(1)

    # Пробегаемся по операциям, для которых мы хотим сгенерировать тесты.

    if (tests_type == "test"):
        for enum, operation in enumerate(["+", "-", "*", "<", "=", "/", "^"]):
            # Открываем файлы для записи самих тестов и ответов к ним.
            filename_pattern = f'{test_dir}/{enum+1:02}'
            with open(f'{filename_pattern}.t', 'w') as test_file, \
                open(f'{filename_pattern}.a', 'w') as answer_file:
                for _ in range(0, tests_count):
                    # Генерируем рандомные большие числа.
                    if operation == "^":
                        num1, num2 = get_random_shorts()
                    else:
                        num1, num2 = get_random_nums()
                    # num1, num2 = get_random_nums()
                    # Записываем в файл получившийся тест.
                    test_file.write(f"{num1}\n{num2}\n{operation}\n")
                    # Получаем ответ в виде строки и записываем его
                    # в файл с ответами.
                    answer = get_answer(num1, num2, operation)
                    answer_file.write(f"{answer}\n")
    else:
        filename_pattern = f'{test_dir}/01'
        with open(f'{filename_pattern}.t', 'w') as test_file, \
            open(f'{filename_pattern}.a', 'w') as answer_file:
            for enum, operation in enumerate(["+", "-", "*", "<", "=", "/", "^"]):
                for _ in range(0, tests_count):
                    # Генерируем рандомные большие числа.
                    if operation == "^":
                        num1, num2 = get_random_shorts()
                    else:
                        num1, num2 = get_random_nums()
                    # num1, num2 = get_random_nums()
                    # Записываем в файл получившийся тест.
                    test_file.write(f"{num1}\n{num2}\n{operation}\n")
                    # Получаем ответ в виде строки и записываем его
                    # в файл с ответами.
                    answer = get_answer(num1, num2, operation)
                    answer_file.write(f"{answer}\n")

if __name__ == "__main__":
    main()
