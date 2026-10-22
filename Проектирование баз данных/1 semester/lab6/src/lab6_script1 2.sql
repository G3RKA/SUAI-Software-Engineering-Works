use hospital_info;

select TProcedure.*, Procedure_Session.price_of_procedure
from Procedure_Session
inner join office on Procedure_Session.id_office = office.id_office
inner join TProcedure on Procedure_Session.id_type_of_procedure = TProcedure.id_type_of_procedure
where Procedure_Session.price_of_procedure <= all 
(select ps.price_of_procedure from Procedure_Session as ps inner join office as o on ps.id_office = o.id_office where o.office_number = 101) and 
office.office_number = 101