

ALTER TABLE satellite add constraint chek_id
    CHECK (id > 0);
ALTER TABLE satellite ALTER COLUMN
    model SET NOT NULL;
ALTER TABLE satellite add constraint chek_launch_date 
    CHECK (launch_date >= '1957-01-01');
ALTER TABLE satellite ALTER COLUMN
    orbit_type SET NOT NULL;
ALTER TABLE satellite ALTER COLUMN
    work_status SET NOT NULL;


ALTER TABLE reception_center add constraint chek_id
    CHECK (id > 0);
ALTER TABLE reception_center ALTER COLUMN
    center_name SET NOT NULL;
ALTER TABLE reception_center ALTER COLUMN
    center_location SET NOT NULL;
ALTER TABLE reception_center add constraint chek_capacity 
    CHECK (capacity > 0);
ALTER TABLE reception_center add constraint check_work_start
    CHECK (work_start > '1900-01-01');
ALTER TABLE reception_center ALTER COLUMN
    work_status SET NOT NULL;


ALTER TABLE operator add constraint check_id
    CHECK (id > 0);
ALTER TABLE operator ALTER COLUMN fio SET NOT NULL;
ALTER TABLE operator add constraint check_address
    CHECK (id > 0);
ALTER TABLE operator ALTER COLUMN job_position SET NOT NULL;
ALTER TABLE operator add constraint check_experience
    CHECK(experience >= 0);
ALTER TABLE operator add constraint chek_shift
    CHECK (shift >= 1 AND shift <= 3);
ALTER TABLE operator ALTER COLUMN workplace_id SET NOT NULL;


ALTER TABLE reception_session add constraint check_id
    CHECK (id > 0);
ALTER TABLE reception_session add constraint check_start 
    CHECK (start_date_time <= end_date_time);
ALTER TABLE reception_session add constraint check_end 
    CHECK (start_date_time <= end_date_time);
ALTER TABLE reception_session ALTER COLUMN satellite_id SET NOT NULL;
ALTER TABLE reception_session ALTER COLUMN operator_id SET NOT NULL;


ALTER TABLE reception_data add constraint check_id
    CHECK (id > 0);
ALTER TABLE reception_data ALTER COLUMN file_type SET NOT NULL;
ALTER TABLE reception_data ALTER COLUMN file_path SET NOT NULL;
ALTER TABLE reception_data add constraint check_area
    CHECK (area > 0);
ALTER TABLE reception_data ALTER COLUMN measure_date_time SET NOT NULL;
ALTER TABLE reception_data ALTER COLUMN reception_session_id SET NOT NULL;
