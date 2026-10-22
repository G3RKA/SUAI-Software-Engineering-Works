use hospital_info;

create table archived_docs (
	id_archive int auto_increment primary key,
    id_doctor int,
    name varchar(100),
    surname varchar(100),
    patronym varchar(100),
    phone varchar(20),
    archived_at datetime
);

insert into Doctor (surname, name, patronym, phone) values ("Иванов", "Иван", "Петрович", "9999999999");

delete from Doctor where id_doctor=5;

create table Apparatus_Logs (
    id_log int auto_increment primary key,
    id_apparatus int,
    name_of_apparatus varchar(30),
    action_name varchar(30),
    action_time datetime
);

insert into Apparatus(name_of_apparatus) values ("Название");

update Apparatus set name_of_apparatus="Название2" where id_apparatus=11;

insert into Consultation_Session (id_doctor, id_patient, id_office, date_of_consult, price_of_consult) values 
(40, 4, 5, '2025-09-10', 125);