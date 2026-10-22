SELECT DISTINCT p.*
FROM Patient p
WHERE NOT EXISTS (
    -- Находим аппараты, начинающиеся на 'Д'
    SELECT a.id_apparatus
    FROM Apparatus a
    WHERE a.name_of_apparatus LIKE 'Д%'
    AND NOT EXISTS (
        -- Проверяем, что у пациента есть процедура с этим аппаратом
        SELECT 1
        FROM Procedure_Session ps
        JOIN TProcedure tp ON ps.id_type_of_procedure = tp.id_type_of_procedure
        WHERE ps.id_patient = p.id_patient
        AND tp.id_apparatus = a.id_apparatus
    )
);

SELECT p.*
FROM Patient p
JOIN Procedure_Session ps ON p.id_patient = ps.id_patient
JOIN TProcedure tp ON ps.id_type_of_procedure = tp.id_type_of_procedure
JOIN Apparatus a ON tp.id_apparatus = a.id_apparatus
WHERE a.name_of_apparatus LIKE 'Д%'
GROUP BY p.id_patient
HAVING COUNT(DISTINCT a.id_apparatus) = (
    SELECT COUNT(*)
    FROM Apparatus a2
    WHERE a2.name_of_apparatus LIKE 'Д%'
);