use hospital_info;

select Patient.* from Procedure_Session
inner join Patient on Procedure_Session.id_patient=Patient.id_patient
inner join TProcedure on Procedure_Session.id_type_of_procedure=TProcedure.id_type_of_procedure
inner join Apparatus on Apparatus.id_apparatus=TProcedure.id_apparatus
where Apparatus.name_of_apparatus LIKE 'Д%'
group by Patient.id_patient
having COUNT(distinct Apparatus.id_apparatus) = (select COUNT(*) from Apparatus as ap where ap.name_of_apparatus like 'Д%');