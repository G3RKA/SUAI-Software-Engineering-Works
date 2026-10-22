CREATE OR REPLACE FUNCTION check_med_staff()
RETURNS TRIGGER AS $$
BEGIN
	IF NOT EXISTS (SELECT 1 FROM medical_staff WHERE id_personal = NEW.id_personal) THEN
		RAISE EXCEPTION 'Указанного сотрудника не существует';
	END IF;

	RETURN NEW;
END
$$ LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER check_staff_consult
BEFORE INSERT OR UPDATE ON consultation_session
FOR EACH ROW EXECUTE FUNCTION check_med_staff();

CREATE OR REPLACE TRIGGER check_staff_procedure
BEFORE INSERT OR UPDATE ON procedure_session
FOR EACH ROW EXECUTE FUNCTION check_med_staff();

CREATE OR REPLACE FUNCTION check_staff_delete()
RETURNS TRIGGER AS $$
BEGIN
	IF EXISTS (SELECT 1 FROM consultation_session WHERE id_personal = OLD.id_personal) THEN
		RAISE EXCEPTION 'На сотрудника записаны приёмы';
	END IF;

	IF EXISTS (SELECT 1 FROM procedure_session WHERE id_personal = OLD.id_personal) THEN
		RAISE EXCEPTION 'На сотрудника записаны процедуры';
	END IF;

	RETURN OLD;
END
$$ LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER check_staff_consult_delete
BEFORE DELETE ON doctor
FOR EACH ROW EXECUTE FUNCTION check_staff_delete();

CREATE OR REPLACE TRIGGER check_staff_procedure_delete
BEFORE DELETE ON nurse
FOR EACH ROW EXECUTE FUNCTION check_staff_delete();

CREATE OR REPLACE FUNCTION check_staff_update()
RETURNS TRIGGER AS $$
BEGIN
	IF (NEW.id_personal IS DISTINCT FROM OLD.id_personal) THEN

		IF EXISTS (SELECT 1 FROM consultation_session WHERE id_personal = OLD.id_personal) THEN
			RAISE EXCEPTION 'На сотрудника записаны приёмы';
		END IF;
	
		IF EXISTS (SELECT 1 FROM procedure_session WHERE id_personal = OLD.id_personal) THEN
			RAISE EXCEPTION 'На сотрудника записаны процедуры';
		END IF;

	END IF;

	RETURN NEW;
END
$$ LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER check_staff_consult_update
BEFORE UPDATE ON doctor
FOR EACH ROW EXECUTE FUNCTION check_staff_update();

CREATE OR REPLACE TRIGGER check_staff_procedure_update
BEFORE UPDATE ON nurse
FOR EACH ROW EXECUTE FUNCTION check_staff_update();