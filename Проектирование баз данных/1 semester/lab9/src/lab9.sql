SELECT DISTINCT o.id_office, o.office_number
FROM Office o
JOIN Procedure_Session ps ON o.id_office = ps.id_office
JOIN TProcedure tp ON ps.id_type_of_procedure = tp.id_type_of_procedure
JOIN Apparatus a ON tp.id_apparatus = a.id_apparatus
WHERE a.name_of_apparatus LIKE '%магнит%_';

SELECT DISTINCT 
    d.id_doctor,
    d.surname AS doctor_surname,
    d.name AS doctor_name,
    d.patronym AS doctor_patronym
FROM Doctor d
JOIN Consultation_Session cs1 ON d.id_doctor = cs1.id_doctor
JOIN Consultation_Session cs2 ON d.id_doctor = cs2.id_doctor
WHERE cs1.id_patient != cs2.id_patient
  AND cs1.id_office = cs2.id_office
  AND cs1.date_of_consult = cs2.date_of_consult;
  
SELECT 
    a.id_apparatus,
    a.name_of_apparatus
FROM Apparatus a
LEFT JOIN TProcedure tp ON a.id_apparatus = tp.id_apparatus
LEFT JOIN Procedure_Session ps ON tp.id_type_of_procedure = ps.id_type_of_procedure
WHERE ps.id_procedure IS NULL;