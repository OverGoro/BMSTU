-- Импорт данных в таблицу satellite
COPY satellite (id, model, launch_date, orbit_type, work_status)
FROM '/home/yurik/5_sem/data_bases/lab_01/code/satellite.csv'
DELIMITER ','
CSV HEADER;

-- Импорт данных в таблицу reception_center
COPY reception_center (id, center_name, center_location, capacity, work_start, work_status)
FROM '/home/yurik/5_sem/data_bases/lab_01/code/reception_center.csv'
DELIMITER ','
CSV HEADER;

-- Импорт данных в таблицу operator
COPY operator (id, fio, job_position, experience, shift, workplace_id)
FROM '/home/yurik/5_sem/data_bases/lab_01/code/operator.csv'
DELIMITER ','
CSV HEADER;

-- Импорт данных в таблицу reception_session
COPY reception_session (id, start_date_time, end_date_time, satellite_id, operator_id)
FROM '/home/yurik/5_sem/data_bases/lab_01/code/reception_session.csv'
DELIMITER ','
CSV HEADER;

-- Импорт данных в таблицу reception_data
COPY reception_data (id, file_type, file_path, area, measure_date_time, reception_session_id)
FROM '/home/yurik/5_sem/data_bases/lab_01/code/reception_data.csv'
DELIMITER ','
CSV HEADER;