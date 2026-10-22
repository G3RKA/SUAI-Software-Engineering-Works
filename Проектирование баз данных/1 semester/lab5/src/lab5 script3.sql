use hospital_info;

select Apparatus.* from Apparatus 
left outer join TProcedure on Apparatus.id_apparatus=TProcedure.id_apparatus
where TProcedure.id_apparatus is null;