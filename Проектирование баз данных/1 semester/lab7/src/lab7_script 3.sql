use hospital_info;

drop procedure if exists DeletePatient;

Delimiter //

create definer=`root`@`localhost` procedure DeletePatient(
patient_id int
)
begin

declare p_name varchar(20);
select name into p_name from Patient where id_patient=patient_id;

if p_name is not null then
	
    delete from Procedure_Session where id_patient = patient_id;

    delete from Consultation_Session where id_patient = patient_id;
    
    delete from Patient where id_patient = patient_id;
    
end if;

end //

Delimiter ;