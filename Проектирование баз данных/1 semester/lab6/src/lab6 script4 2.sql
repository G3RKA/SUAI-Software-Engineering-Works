use hospital_info;

select distinct Doctor.* from Procedure_Session 
inner join Doctor on Doctor.id_doctor=Procedure_Session.id_doctor
inner join TProcedure on TProcedure.id_type_of_procedure=Procedure_Session.id_type_of_procedure
inner join Apparatus on Apparatus.id_apparatus=TProcedure.id_apparatus
where Apparatus.name_of_apparatus like '%магнит%' except
(select Doctor.* from Consultation_Session 
inner join Doctor on Doctor.id_doctor=Consultation_Session.id_doctor
inner join Office on Consultation_Session.id_office=Office.id_office
where Office.office_number=102)