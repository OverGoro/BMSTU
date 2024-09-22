import os
import psycopg2
from psycopg2 import sql
from generate import generate_all

# Конфигурация для подключения к базе данных PostgreSQL
DB_CONFIG = {
    'dbname': 'lab_01',
    'user': 'yuri',
    'password': '1',
    'host': 'localhost',
    'port': 5432
}

# Функция для создания подключения к базе данных
def connect_to_db():
    try:
        connection = psycopg2.connect(**DB_CONFIG)
        print("Подключение к базе данных установлено.")
        return connection
    except Exception as e:
        print(f"Ошибка подключения к базе данных: {e}")
        return None

# Функция для вставки данных из CSV в БД
def copy_data_to_db():
    connection = connect_to_db()
    if connection is None:
        return
    
    try:
        with connection.cursor() as cursor:

            # Копирования данных в таблицу satellite
            with open('satellite.csv', 'r', encoding='utf-8') as file:
                next(file)  # Пропуск заголовок
                cursor.copy_expert("COPY satellite FROM STDIN WITH CSV", file)
                        
            # Копирования данных в таблицу reception_center
            with open('reception_center.csv', 'r', encoding='utf-8') as file:
                next(file)  # Пропуск заголовок
                cursor.copy_expert("COPY reception_center FROM STDIN WITH CSV", file)
            
            # Копирования данных в таблицу operator
            with open('operator.csv', 'r', encoding='utf-8') as file:
                next(file)  # Пропуск заголовок
                cursor.copy_expert("COPY operator FROM STDIN WITH CSV", file)


            # Копирования данных в таблицу reception_session
            with open('reception_session.csv', 'r', encoding='utf-8') as file:
                next(file)  # Пропуск заголовок
                cursor.copy_expert("COPY reception_session FROM STDIN WITH CSV", file)

            # Копирования данных в таблицу reception_data
            with open('reception_data.csv', 'r', encoding='utf-8') as file:
                next(file)  # Пропуск заголовок
                cursor.copy_expert("COPY reception_data FROM STDIN WITH CSV", file)

            connection.commit()
            print("Данные успешно скопированы в БД.")
    except Exception as e:
        print(f"Ошибка копирования данных в БД: {e}")
        connection.rollback()
    finally:
        connection.close()


def execute_file(filename:str, success:str, failure:str):
    connection = connect_to_db()
    if connection is None:
        return
    
    try:
        with connection.cursor() as cursor:
            cursor.execute(sql.SQL(open(filename).read()))
            connection.commit()
            print(success)
    except Exception as e:
        print(f"{failure} {e}")
        connection.rollback()
    finally:
        connection.close()

def clear_tables():
    execute_file("clear_data.sql", "Таблицы очищены.", "Ошибка очистки таблиц: ")

def clear_db():
    execute_file("clear_db.sql", "БД очищена.", "Ошибка очистки БД: ")

def init_db():
    execute_file("init.sql", "БД инициализирована", "Ошибка инициализации БД:")

def restric_db():
    execute_file("restrict.sql", "Ограничения наложены", "Ошибка наложения ограничений:")


# Меню для работы с приложением
def main_menu():
    while True:
        print("\n--- Меню ---")
        print("1. Сгенерировать случайные данные")
        print("2. Скопировать данные в БД")
        print("3. Очистить данные в таюлицах")
        print("4. Обнулить БД")
        print("5. Инициализировать БД")
        print("6. Наложить ограничения на БД")
        print("7. Выйти")

        choice = input("Выберите опцию: ")

        if choice == '1':
            # Запуск генерации данных
            generate_all()
            print("Данные успешно сгенерированы.")
        elif choice == '2':
            copy_data_to_db()
        elif choice == '3':
            clear_tables()
        elif choice == '4':
            clear_db()
        elif choice == '5':
            init_db()
        elif choice == '6':
            restric_db()
        elif choice == '7':
            print("Выход из программы.")
            break
        else:
            print("Неверный выбор, попробуйте снова.")

if __name__ == '__main__':
    main_menu()
