use hospital_info;

select office.*, count(Procedure_Session.id_office) as count from Procedure_Session 
right join office on Procedure_Session.id_office = office.id_office
group by office.id_office
having count(*) < 
(select avg(proc.proc_count) from 
(select count(ps.id_procedure) as proc_count from Procedure_Session ps right join office o on ps.id_office = o.id_office group by o.id_office) proc)