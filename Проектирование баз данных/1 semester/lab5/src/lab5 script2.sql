use hospital_info;

select distinct Doctor.* from Consultation_Session as s_1
inner join Consultation_Session as s_2 on s_1.id_doctor=s_2.id_doctor 
inner join Doctor on s_1.id_doctor=Doctor.id_doctor
WHERE s_1.date_of_consult=s_2.date_of_consult 
AND s_1.id_office=s_2.id_office 
AND s_1.id_patient != s_2.id_patient;