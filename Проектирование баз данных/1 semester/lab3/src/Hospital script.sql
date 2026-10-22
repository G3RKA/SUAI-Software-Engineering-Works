create database hospital_info;

use hospital_info;

create table Office(
id_office int auto_increment,
office_number int NOT NULL,
primary key(id_office)
);

create table Apparatus(
id_apparatus int auto_increment,
name_of_apparatus varchar(30) NOT NULL,
primary key(id_apparatus)
);

create table TProcedure(
id_type_of_procedure int auto_increment,
id_apparatus int NOT NULL,
name_of_procedure varchar(30) NOT NULL,
price_of_type_of_procedure int NOT NULL,
primary key(id_type_of_procedure),
foreign key (id_apparatus) REFERENCES Apparatus(id_apparatus) on delete restrict on update cascade
);

create table Patient(
id_patient int auto_increment,
surname varchar(20) NOT NULL,
name varchar(20) NOT NULL,
patronym varchar(20) NULL,
phone varchar(10) NOT NULL,
primary key(id_patient)
);

create table Doctor(
id_doctor int auto_increment,
surname varchar(20) NOT NULL,
name varchar(20) NOT NULL,
patronym varchar(20) NULL,
phone varchar(10) NOT NULL,
primary key(id_doctor)
);

create table Procedure_Session(
id_procedure int auto_increment,
id_type_of_procedure int NOT NULL,
id_doctor int NOT NULL,
id_patient int NOT NULL,
id_office int NOT NULL,
date_of_procedure date NOT NULL,
price_of_procedure int NOT NULL,
primary key(id_procedure),
foreign key (id_type_of_procedure) REFERENCES TProcedure(id_type_of_procedure) on delete restrict on update cascade,
foreign key (id_doctor) REFERENCES Doctor(id_doctor) on delete restrict on update cascade,
foreign key (id_patient) REFERENCES Patient(id_patient) on delete restrict on update cascade,
foreign key (id_office) REFERENCES Office(id_office) on delete restrict on update cascade
);

create table Consultation_Session(
id_consult int auto_increment,
id_doctor int NOT NULL,
id_patient int NOT NULL,
id_office int NOT NULL,
date_of_consult date NOT NULL,
price_of_consult int NOT NULL,
primary key(id_consult),
foreign key (id_doctor) REFERENCES Doctor(id_doctor) on delete restrict on update cascade,
foreign key (id_patient) REFERENCES Patient(id_patient) on delete restrict on update cascade,
foreign key (id_office) REFERENCES Office(id_office) on delete restrict on update cascade
);