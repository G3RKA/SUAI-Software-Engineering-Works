use hospital_info;

select distinct office.* from Procedure_Session 
inner join TProcedure on Procedure_Session.id_type_of_procedure = TProcedure.id_type_of_procedure
inner join Apparatus on Apparatus.id_apparatus=TProcedure.id_apparatus
inner join Office using (id_office)
where Apparatus.name_of_apparatus like '%магнит_%';
