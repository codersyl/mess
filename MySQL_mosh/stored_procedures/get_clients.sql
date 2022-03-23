DROP PROCEDURE IF EXISTS get_clients;

USE sql_invoicing;
DELIMITER $$
CREATE PROCEDURE get_clients()
BEGIN
	SELECT *
	FROM sql_invoicing.clients;
END$$
DELIMITER ;