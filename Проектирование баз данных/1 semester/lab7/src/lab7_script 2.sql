use hospital_info;

drop function if exists GetConsultPricesForPatient;

Delimiter //

create definer=`root`@`localhost` function GetConsultPricesForPatient(
 patient_id int
)
returns int
reads sql data
begin

declare consult_prices int;
declare p_name varchar(20);
select name into p_name from Patient where id_patient=patient_id;

if p_name is not null then
    select sum(price_of_consult) into consult_prices from Consultation_Session where id_patient=patient_id;
    if consult_prices is null then
		set consult_prices = 0;
    end if;    
end if;

return consult_prices;

end //

Delimiter ;