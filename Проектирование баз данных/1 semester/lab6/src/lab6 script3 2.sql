use hospital_info;

select Patient.*
from Patient
where not exists (
    select Apparatus.id_apparatus
    from Apparatus
    where Apparatus.name_of_apparatus like 'Д%' and
    not exists (
        select *
        from Procedure_Session 
        inner join TProcedure on Procedure_Session.id_type_of_procedure=TProcedure.id_type_of_procedure
        where Procedure_Session.id_patient = Patient.id_patient
        and Apparatus.id_apparatus = TProcedure.id_apparatus
    )
);