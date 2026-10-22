SELECT 
    ps.id_procedure,
    tp.name_of_procedure,
    ps.price_of_procedure
FROM Procedure_Session ps
JOIN TProcedure tp ON ps.id_type_of_procedure = tp.id_type_of_procedure
JOIN Office o ON ps.id_office = o.id_office
WHERE o.office_number = 101
  AND ps.price_of_procedure = (
    SELECT MIN(ps2.price_of_procedure)
    FROM Procedure_Session ps2
    JOIN Office o2 ON ps2.id_office = o2.id_office
    WHERE o2.office_number = 101
);

SELECT 
    ps.id_procedure,
    tp.name_of_procedure,
    ps.price_of_procedure
FROM Procedure_Session ps
JOIN TProcedure tp ON ps.id_type_of_procedure = tp.id_type_of_procedure
JOIN Office o ON ps.id_office = o.id_office
WHERE o.office_number = 101
  AND ps.price_of_procedure <= ALL (
    SELECT ps2.price_of_procedure
    FROM Procedure_Session ps2
    JOIN Office o2 ON ps2.id_office = o2.id_office
    WHERE o2.office_number = 101
);

SELECT 
    o.id_office,
    o.office_number,
    COUNT(ps.id_procedure) as procedure_count
FROM Office o
LEFT JOIN Procedure_Session ps ON o.id_office = ps.id_office
GROUP BY o.id_office, o.office_number
HAVING COUNT(ps.id_procedure) < (
    SELECT AVG(office_procedure_count)
    FROM (
        SELECT COUNT(ps2.id_procedure) as office_procedure_count
        FROM Office o2
        LEFT JOIN Procedure_Session ps2 ON o2.id_office = ps2.id_office
        GROUP BY o2.id_office
    ) as office_counts
);