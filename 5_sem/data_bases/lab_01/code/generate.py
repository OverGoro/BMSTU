import csv
import random
from faker import Faker
from datetime import datetime, timedelta

fake = Faker('ru_RU')


def create_satellite_csv(file_name='satellite.csv', num_records=100):
    orbit_types = ['Геостационарная', 'Низкая', 'Средняя', 'Высокая']
    work_statuses = ['Работает', 'На обслуживании', 'Не работает']
    
    with open(file_name, mode='w', newline='', encoding='utf-8') as file:
        writer = csv.writer(file)
        writer.writerow(['id', 'model', 'launch_date', 'orbit_type', 'work_status'])
        
        for i in range(1, num_records + 1):
            model = f'Модель-{i}'
            launch_date = fake.date_between(start_date='-10y', end_date='today')
            orbit_type = random.choice(orbit_types)
            work_status = random.choice(work_statuses)
            writer.writerow([i, model, launch_date, orbit_type, work_status])

def create_reception_center_csv(file_name='reception_center.csv', num_records=20):
    work_statuses = ['Работает', 'На обслуживании', 'Не работает']
    
    with open(file_name, mode='w', newline='', encoding='utf-8') as file:
        writer = csv.writer(file)
        writer.writerow(['id', 'center_name', 'center_location', 'capacity', 'work_start', 'work_status'])
        
        for i in range(1, num_records + 1):
            center_name = fake.company()
            center_location = fake.city()
            capacity = random.randint(10, 100)
            work_start = fake.date_between(start_date='-20y', end_date='today')
            work_status = random.choice(work_statuses)
            writer.writerow([i, center_name, center_location, capacity, work_start, work_status])

def create_operator_csv(file_name='operator.csv', num_records=50):
    with open(file_name, mode='w', newline='', encoding='utf-8') as file:
        writer = csv.writer(file)
        writer.writerow(['id', 'fio', 'job_position', 'experience', 'shift', 'workplace_id'])
        
        for i in range(1, num_records + 1):
            fio = fake.name()
            job_position = random.choice(['Техник', 'Инженер', 'Оператор'])
            experience = random.randint(1, 30)
            shift = random.randint(1, 3)
            workplace_id = random.randint(1, 20)  # Ссылается на id из таблицы reception_center
            writer.writerow([i, fio, job_position, experience, shift, workplace_id])
def create_reception_session_csv(file_name='reception_session.csv', num_records=200):
    with open(file_name, mode='w', newline='', encoding='utf-8') as file:
        writer = csv.writer(file)
        writer.writerow(['id', 'start_date_time', 'end_date_time', 'satellite_id', 'operator_id'])
        
        for i in range(1, num_records + 1):
            start_date_time = fake.date_time_between(start_date='-2y', end_date='now')
            end_date_time = start_date_time + timedelta(hours=random.randint(1, 5))
            satellite_id = random.randint(1, 100)  # Ссылается на id из таблицы satellite
            operator_id = random.randint(1, 50)  # Ссылается на id из таблицы operator
            writer.writerow([i, start_date_time, end_date_time, satellite_id, operator_id])

def create_reception_data_csv(file_name='reception_data.csv', num_records=300):
    file_types = ['Изображение', 'Радиоданные', 'Телеметрия']
    
    with open(file_name, mode='w', newline='', encoding='utf-8') as file:
        writer = csv.writer(file)
        writer.writerow(['id', 'file_type', 'file_path', 'area', 'measure_date_time', 'reception_session_id'])
        
        for i in range(1, num_records + 1):
            file_type = random.choice(file_types)
            file_path = f'/data/file_{i}.{file_type.lower()}'
            area = random.randint(1, 1000)
            measure_date_time = fake.date_time_between(start_date='-2y', end_date='now')
            reception_session_id = random.randint(1, 200)  # Ссылается на id из таблицы reception_session
            writer.writerow([i, file_type, file_path, area, measure_date_time, reception_session_id])

def generate_all(num_records = 2000):
    create_satellite_csv(num_records = 2000)
    create_reception_center_csv(num_records = 2000)
    create_operator_csv(num_records = 2000)
    create_reception_session_csv(num_records = 2000)
    create_reception_data_csv(num_records = 2000)