use hospital_info;

drop trigger if exists insert_before;
drop trigger if exists insert_after;
drop trigger if exists update_before;
drop trigger if exists update_after;
drop trigger if exists delete_before;
drop trigger if exists delete_after;

delimiter //

-- insert
create trigger insert_before before insert on consultation_session for each row
begin
    if not exists (select * from Doctor where id_doctor=new.id_doctor) then
		signal sqlstate '45000' set message_text = "Ошибка: Указанного доктора не существует";
    end if;
    if not exists (select * from Patient where id_patient=new.id_patient) then
		signal sqlstate '45000' set message_text = "Ошибка: Указанного пациента не существует";
    end if;    
    if not exists (select * from Office where id_office=new.id_office) then
		signal sqlstate '45000' set message_text = "Ошибка: Указанного кабинета не существует";
    end if;     
end; //

create trigger insert_after after insert on Apparatus for each row
begin
    insert into Apparatus_Logs(id_apparatus, name_of_apparatus, action_name, action_time) values (new.id_apparatus, new.name_of_apparatus, 'insert', now());
end; //

-- update
create trigger update_before before update on consultation_session for each row
begin
    if not exists (select * from Doctor where id_doctor=new.id_doctor) then
		signal sqlstate '45000' set message_text = "Ошибка: Указанного доктора не существует";
    end if;
    if not exists (select * from Patient where id_patient=new.id_patient) then
		signal sqlstate '45000' set message_text = "Ошибка: Указанного пациента не существует";
    end if;  
    if not exists (select * from Office where id_office=new.id_office) then
		signal sqlstate '45000' set message_text = "Ошибка: Указанного кабинета не существует";
    end if;       
end; //

create trigger update_after after update on Apparatus for each row
begin
   insert into Apparatus_Logs(id_apparatus, name_of_apparatus, action_name, action_time) values (new.id_apparatus, new.name_of_apparatus, 'update', now());
end; //

-- delete
create trigger delete_before before delete on Patient for each row
begin
    if exists (select * from consultation_session where id_patient=old.id_patient) then
		signal sqlstate '45000' set message_text = "Ошибка: На указаннного пациента есть ссылка в приёмах";
    end if;  
    if exists (select * from procedure_session where id_patient=old.id_patient) then
		signal sqlstate '45000' set message_text = "Ошибка: На указаннного пациента есть ссылка в процедурах";
    end if;    
end; //

create trigger delete_after after delete on Procedure_session for each row
begin
	update Doctor set procedure_count = (procedure_count - 1) where id_doctor=old.id_doctor;
end; //

delimiter ;