DO
$$
BEGIN
  IF NOT EXISTS (SELECT *
                        FROM pg_type typ
                             INNER JOIN pg_namespace nsp
                                        ON nsp.oid = typ.typnamespace
                        WHERE nsp.nspname = current_schema()
                              AND typ.typname = 'orbittype') THEN
    CREATE TYPE orbittype AS ENUM (
        'Геостационарная', 
        'Низкая', 
        'Средняя',
        'Высокая'
    );
  END IF;
END;
$$
LANGUAGE plpgsql;


DO
$$
BEGIN
  IF NOT EXISTS (SELECT *
                        FROM pg_type typ
                             INNER JOIN pg_namespace nsp
                                        ON nsp.oid = typ.typnamespace
                        WHERE nsp.nspname = current_schema()
                              AND typ.typname = 'workstatustype') THEN
    CREATE TYPE workstatustype AS ENUM (
        'Работает',
        'На обслуживании',
        'Не работает'
    );
  END IF;
END;
$$
LANGUAGE plpgsql;

DO
$$
BEGIN
  IF NOT EXISTS (SELECT *
                        FROM pg_type typ
                             INNER JOIN pg_namespace nsp
                                        ON nsp.oid = typ.typnamespace
                        WHERE nsp.nspname = current_schema()
                              AND typ.typname = 'datafiletype') THEN
    CREATE TYPE datafiletype AS ENUM (
        'Изображение',
        'Радиоданные',
        'Телеметрия'
    );
  END IF;
END;
$$
LANGUAGE plpgsql;





CREATE TABLE IF NOT EXISTS satellite(
    id INTEGER PRIMARY KEY,
    model VARCHAR(256),
    launch_date DATE,
    orbit_type ORBITTYPE,
    work_status WORKSTATUSTYPE
);

CREATE TABLE IF NOT EXISTS reception_center(
    id INTEGER PRIMARY KEY,
    center_name VARCHAR(256),
    center_location VARCHAR(256),
    capacity INTEGER,
    work_start DATE,
    work_status WORKSTATUSTYPE
);

CREATE TABLE IF NOT EXISTS operator(
    id INTEGER PRIMARY KEY,
    fio VARCHAR(256),
    job_position VARCHAR(256),
    experience INTEGER,
    shift INTEGER,
    workplace_id INTEGER REFERENCES reception_center(id)
);

CREATE TABLE IF NOT EXISTS reception_session (
    id INTEGER PRIMARY KEY,
    start_date_time TIMESTAMP,
    end_date_time TIMESTAMP,
    satellite_id INTEGER REFERENCES satellite(id),
    operator_id INTEGER REFERENCES operator(id)
);

CREATE TABLE IF NOT EXISTS  reception_data(
    id INTEGER PRIMARY KEY,
    file_type DATAFILETYPE,
    file_path VARCHAR(512),
    area INTEGER,
    measure_date_time TIMESTAMP,
    reception_session_id INTEGER REFERENCES reception_session(id)
);