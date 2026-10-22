drop user if exists 'new_user'@'localhost';

create user 'new_user'@'localhost' identified by '123';
grant select on hospital_info.* to 'new_user'@'localhost';
grant execute on procedure hospital_info.InsertProcedureType to 'new_user'@'localhost';
grant execute on function hospital_info.GetConsultPricesForPatient to 'new_user'@'localhost';
grant execute on procedure hospital_info.DeletePatient to 'new_user'@'localhost';