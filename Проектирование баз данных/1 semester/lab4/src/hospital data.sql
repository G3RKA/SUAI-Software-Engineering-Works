use hospital_info;

insert into Office (office_number) values  (101), (102), (103), (104), (105), (106);

insert into Apparatus (name_of_apparatus) values ("Магнит"), ("Магнитопульсатор"), ("Магнитостимулятор");

insert into Apparatus (name_of_apparatus) values ("Дарсонваль"), ("Дерматоскоп"), ("Денситометр");

insert into Apparatus (name_of_apparatus) values ("Лазер"), ("Вибромассажер"), ("Лимфодренажер");

insert into TProcedure (id_apparatus, name_of_procedure, price_of_type_of_procedure) values (1, "Магнитотерапия", 200),
(2, "Магнитопульсная реабилитация", 175),
(3, "Магнитостимуляция мыщц", 275),
(4, "Дарсонвализация кожи лица", 215),
(5, "Дерматоскопия новообразований", 345),
(6, "Денситометрия костей", 305),
(7, "Лазерная эпиляция", 285);

insert into Doctor (surname, name, patronym, phone) values ("Иванов", "Алексей", "Петрович", "9123246789"),
("Смирнова", "Марина", "Викторовна", "9876543210"),
("Кузнецов", "Дмитрий", "Сергеевич", "9056677889"),
("Федорова", "Елена", "Анатольевна", "9263344556");

insert into Patient (surname, name, patronym, phone) values ("Павлова", "Ольга", "Михайловна", "9128765432"),
("Морозов", "Михаил", "Андреевич", "9031122334"),
("Григорьева", "Наталья", "Игоревна", "9504455667"),
("Орлов", "Сергей", "Викторович", "9159988776"),
("Васильева", "Анна", "Петровна", "9062233445");

insert into Procedure_Session (id_type_of_procedure, id_doctor, id_patient, id_office, date_of_procedure, price_of_procedure) values 
(1, 4, 5, 3, '2025-08-24', 200),
(1, 2, 2, 3, '2025-08-10', 200),
(3, 2, 2, 1, '2025-07-10', 275),
(2, 2, 4, 5, '2025-08-12', 175);

insert into Consultation_Session (id_doctor, id_patient, id_office, date_of_consult, price_of_consult) values 
(4, 4, 5, '2025-09-10', 125),
(4, 1, 5, '2025-09-10', 125),
(3, 5, 6, '2025-09-11', 125),
(3, 2, 6, '2025-09-11', 125),
(3, 1, 6, '2025-09-11', 125),
(1, 5, 2, '2025-09-09', 125),
(4, 3, 2, '2025-09-05', 125);

insert into Procedure_Session (id_type_of_procedure, id_doctor, id_patient, id_office, date_of_procedure, price_of_procedure) values 
(7, 1, 5, 3, '2025-08-13', 285),
(7, 3, 1, 1, '2025-08-13', 285),
(6, 2, 4, 1, '2025-08-18', 305),
(5, 4, 2, 5, '2025-08-17', 345),
(4, 2, 4, 3, '2025-08-27', 215),
(5, 4, 4, 1, '2025-08-10', 345),
(3, 4, 4, 5, '2025-08-30', 275),
(2, 1, 5, 6, '2025-08-28', 345);