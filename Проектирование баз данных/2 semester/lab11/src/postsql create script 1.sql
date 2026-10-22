CREATE TYPE PersonData AS (
    surname VARCHAR(20),
    name VARCHAR(20),
    patronym VARCHAR(20),
    phone VARCHAR(10)

);

CREATE TABLE Medical_Staff (
    id_personal SERIAL PRIMARY KEY,
    person PersonData NOT NULL
);

CREATE TABLE Doctor (
	PRIMARY KEY (id_personal)
) INHERITS (Medical_Staff);

CREATE TABLE Nurse (
	PRIMARY KEY (id_personal)
) INHERITS (Medical_Staff);

CREATE TABLE Patient (
    id_patient SERIAL PRIMARY KEY,
    person PersonData NOT NULL
);

CREATE TABLE Office (
    id_office SERIAL PRIMARY KEY,
    office_number INT NOT NULL
);

CREATE TABLE Apparatus (
    id_apparatus SERIAL PRIMARY KEY,
    name_of_apparatus VARCHAR(30) NOT NULL
);

CREATE TABLE Procedure_Type (
    id_type_of_procedure SERIAL PRIMARY KEY,
    name_of_procedure VARCHAR(30) NOT NULL,
    price_of_type_of_procedure INT NOT NULL,
    id_apparatus INT NOT NULL,
    CONSTRAINT fk_apparatus 
        FOREIGN KEY (id_apparatus) REFERENCES Apparatus(id_apparatus) 
        ON DELETE RESTRICT ON UPDATE RESTRICT
);

CREATE TABLE Consultation_Session (
    id_consult SERIAL PRIMARY KEY,
    id_personal INT NOT NULL,
    id_patient INT NOT NULL,
    id_office INT NOT NULL,
    price_of_consult INT NOT NULL,
    date_of_consult DATE NOT NULL,
    CONSTRAINT fk_patient_consult 
        FOREIGN KEY (id_patient) REFERENCES Patient(id_patient) 
        ON DELETE RESTRICT ON UPDATE RESTRICT,

    CONSTRAINT fk_office_consult 
        FOREIGN KEY (id_office) REFERENCES Office(id_office) 
        ON DELETE RESTRICT ON UPDATE RESTRICT
);

CREATE TABLE Procedure_Session (
    id_procedure SERIAL PRIMARY KEY,
    id_personal INT NOT NULL,
    id_patient INT NOT NULL,
    id_office INT NOT NULL,
    id_type_of_procedure INT NOT NULL,
    price_of_procedure INT NOT NULL,
    date_of_procedure DATE NOT NULL,

    CONSTRAINT fk_patient_proc 
        FOREIGN KEY (id_patient) REFERENCES Patient(id_patient) 
        ON DELETE RESTRICT ON UPDATE RESTRICT,

    CONSTRAINT fk_office_proc 
        FOREIGN KEY (id_office) REFERENCES Office(id_office) 
        ON DELETE RESTRICT ON UPDATE RESTRICT,

    CONSTRAINT fk_type_proc 
        FOREIGN KEY (id_type_of_procedure) REFERENCES Procedure_Type(id_type_of_procedure) 
        ON DELETE RESTRICT ON UPDATE RESTRICT
);