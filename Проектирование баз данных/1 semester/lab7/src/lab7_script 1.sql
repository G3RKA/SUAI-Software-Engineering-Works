use hospital_info;

drop procedure if exists InsertProcedureType;

Delimiter //

create definer=`root`@`localhost` procedure InsertProcedureType(
name_procedure varchar(30),
name_apparatus varchar(30),
price_of_procedure int,
out procedure_id int
)
begin

declare apparatus_id int;
select id_type_of_procedure into procedure_id from TProcedure where name_of_procedure=name_procedure;

if procedure_id is null then

	select id_apparatus into apparatus_id from Apparatus where name_of_apparatus=name_apparatus;

	if apparatus_id is null then
		insert into Apparatus (name_of_apparatus) values (name_apparatus);
		set apparatus_id = last_insert_id();
	end if;

	insert into TProcedure(id_apparatus, name_of_procedure, price_of_type_of_procedure) values (apparatus_id, name_procedure, price_of_procedure);

	set procedure_id = last_insert_id();
    
end if;

end //

Delimiter ;