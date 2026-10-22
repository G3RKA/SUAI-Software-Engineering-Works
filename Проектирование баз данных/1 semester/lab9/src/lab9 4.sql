SELECT DISTINCT d.*
FROM Doctor d
JOIN Procedure_Session ps ON d.id_doctor = ps.id_doctor
JOIN TProcedure tp ON ps.id_type_of_procedure = tp.id_type_of_procedure
JOIN Apparatus a ON tp.id_apparatus = a.id_apparatus
WHERE a.name_of_apparatus LIKE '%магнит%'
  AND d.id_doctor NOT IN (
    SELECT DISTINCT cs.id_doctor
    FROM Consultation_Session cs
    JOIN Office o ON cs.id_office = o.id_office
    WHERE o.office_number = 102
);

SELECT DISTINCT d.*
FROM Doctor d
JOIN Procedure_Session ps ON d.id_doctor = ps.id_doctor
JOIN TProcedure tp ON ps.id_type_of_procedure = tp.id_type_of_procedure
JOIN Apparatus a ON tp.id_apparatus = a.id_apparatus
WHERE a.name_of_apparatus LIKE '%магнит%'
EXCEPT
SELECT DISTINCT d.*
FROM Doctor d
JOIN Consultation_Session cs ON d.id_doctor = cs.id_doctor
JOIN Office o ON cs.id_office = o.id_office
WHERE o.office_number = 102;

SELECT DISTINCT d.*
FROM Doctor d
JOIN Procedure_Session ps ON d.id_doctor = ps.id_doctor
JOIN TProcedure tp ON ps.id_type_of_procedure = tp.id_type_of_procedure
JOIN Apparatus a ON tp.id_apparatus = a.id_apparatus
LEFT JOIN (
    SELECT DISTINCT cs.id_doctor
    FROM Consultation_Session cs
    JOIN Office o ON cs.id_office = o.id_office
    WHERE o.office_number = 102
) AS doctors_in_102 ON d.id_doctor = doctors_in_102.id_doctor
WHERE a.name_of_apparatus LIKE '%магнит%'
  AND doctors_in_102.id_doctor IS NULL;