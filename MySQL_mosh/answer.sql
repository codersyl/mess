# p8
SELECT name,
	unit_price,
    unit_price * 1.1 AS "new price"
FROM products;

# p9
SELECT *
FROM orders
WHERE order_date >= '2019-01-01';

# p10
SELECT *
FROM order_items
WHERE order_id = 6 AND (quantity * unit_price > 30);

# p11
SELECT *
FROM products
WHERE quantity_in_stock IN (49, 38, 72);

# p12
SELECT *
FROM	customers
WHERE birth_date BETWEEN '1990-01-01' AND '2000-01-01' ;

# p13
SELECT *
FROM	customers
WHERE 	address LIKE '%trail%' OR 
				address LIKE '%avenue%' OR 
				phone LIKE '%9';

# p14
SELECT *
FROM	customers
-- WHERE 	first_name = 'elka' OR first_name = 'ambur';
-- WHERE last_name REGEXP 'ey$|on$';
-- WHERE last_name REGEXP '^my|se';
WHERE last_name REGEXP 'b[ru]'

# p15
SELECT *
FROM	orders
WHERE shipped_date IS NULL;

# p16
SELECT *, quantity * unit_price AS total_price
FROM	order_items
WHERE order_id = 2
ORDER BY total_price DESC;

# p17
SELECT *
FROM	customers
ORDER BY points DESC
LIMIT 3;

# p18
SELECT order_id, o.product_id, quantity, o.unit_price
FROM	order_items o
JOIN products p
	ON o.product_id = p.product_id
ORDER BY order_id;

# p21
USE sql_invoicing;
SELECT p.date,
		p.invoice_id,
        p.amount,
        c.name AS client_name,
        pm.name AS payment_method
FROM payments p
JOIN clients c
	ON c.client_id = p.client_id
JOIN payment_methods pm
	ON p.payment_method = pm.payment_method_id;

# p24
SELECT p.product_id,
			p.name,
            oi.quantity
FROM products p
LEFT JOIN order_items oi
	ON p.product_id = oi.product_id
ORDER BY p.product_id;

# p25
USE sql_store;
SELECT o.order_date,
				o.order_id,
				c.first_name AS customer,
                s.name AS shipper,
                os.name AS status
FROM orders o
LEFT JOIN customers c
	ON c.customer_id = o.customer_id
LEFT JOIN shippers s
	ON o.shipper_id = s.shipper_id
LEFT JOIN order_statuses os
	ON os.order_status_id = o.status;

# p27
USE sql_invoicing;
SELECT
	p.date,
    c.name AS client_name,
    p.amount,
    pm.name AS payment_method
FROM payments p
JOIN clients c
	USING (client_id)
JOIN payment_methods pm
	ON pm.payment_method_id = p.payment_method;

# p29
USE sql_store;
# implicit
SELECT *
FROM shippers, products;
# explicit 
-- SELECT *
-- FROM shippers sh
-- CROSS JOIN products p;

# p30
USE sql_store;
SELECT customer_id,
	first_name,
    points,
    'Gold' AS type
FROM customers
WHERE points >= 3000
UNION
SELECT customer_id,
	first_name,
    points,
    'Silver' AS type
FROM customers
WHERE points >= 2000 AND points < 3000
UNION
SELECT customer_id,
	first_name,
    points,
    'Bronze' AS type
FROM customers
WHERE points < 2000
ORDER BY first_name;

# p33
USE sql_store;
INSERT INTO products (name, quantity_in_stock, unit_price)
VALUES ('Product1', 1, 1),
	('Product2', 2, 2),
	('Product3', 3, 3);

# p35
USE sql_invoicing;
CREATE TABLE invoices_archived AS
SELECT i.invoice_id,
	i.number,
    c.name AS client_name,
    i.invoice_total,
    i.payment_total,
    i.invoice_date,
    i.due_date,
    i.payment_date
FROM invoices i
JOIN clients c USING (client_id)
WHERE i.payment_date IS NOT NULL;

# p37
USE sql_store;
UPDATE customers
SET
	points = points + 50
WHERE birth_date < '1990-01-01';

# p38
USE sql_store;
UPDATE orders
SET
	comments = 'Gold customer'
WHERE customer_id IN
	(SELECT customer_id
	FROM customers
	WHERE points > 3000);

# p41
USE sql_invoicing;
SELECT
	'First half of 2019' AS date_range,
    SUM(invoice_total) AS total_sales,
	SUM(payment_total) AS total_payments,
   	SUM(invoice_total - payment_total) AS what_we_expect
FROM invoices
WHERE invoice_date BETWEEN '2019-01-01' AND '2019-06-30'
UNION
SELECT
	'Second half of 2019' AS date_range,
    SUM(invoice_total) AS total_sales,
	SUM(payment_total) AS total_payments,
   	SUM(invoice_total - payment_total) AS what_we_expect
FROM invoices
WHERE invoice_date BETWEEN '2019-07-01' AND '2019-12-31'
UNION
SELECT
	'Total' AS date_range,
    SUM(invoice_total) AS total_sales,
	SUM(payment_total) AS total_payments,
   	SUM(invoice_total - payment_total) AS what_we_expect
FROM invoices
WHERE invoice_date BETWEEN '2019-01-01' AND '2019-12-31';

# p42
USE sql_invoicing;
SELECT
	p.date,
	pm.name AS payment_method,
	SUM(amount) AS total_payments
FROM payments p
JOIN payment_methods pm
	ON p.payment_method = pm. payment_method_id
GROUP BY p.date, p.payment_method
ORDER BY p.date;

# p43
USE sql_store;
SELECT
	c.first_name,
    c.last_name,
    SUM(oi.quantity * oi.unit_price) as spend
FROM customers c 
JOIN orders o USING(customer_id)
JOIN order_items oi USING (order_id)
WHERE c.state = 'VA'
GROUP BY o.customer_id
HAVING spend > 100

# p44
USE sql_invoicing;
SELECT
	pm.name AS payment_method,
	SUM(p.amount) AS total
FROM payments p
JOIN payment_methods pm
	ON pm.payment_method_id = p.payment_method
GROUP BY pm.name WITH ROLLUP;

# p46
# 查找价格比 Lettuce 贵的东西
USE sql_store;
SELECT * 
FROM products
WHERE unit_price > (
	SELECT unit_price 
	FROM products 
	WHERE name REGEXP 'Lettuce'
)

# p47
USE sql_invoicing;
SELECT *
FROM clients
WHERE client_id NOT IN (
	SELECT DISTINCT client_id
	FROM invoices
);

# p48
USE sql_store;
SELECT DISTINCT 
	c.customer_id,
    c.first_name,
    c.last_name
FROM customers c
JOIN orders USING (customer_id)
JOIN order_items USING(order_id)
WHERE product_id = 3
ORDER BY customer_id;

# p51
USE sql_invoicing;
SELECT *
FROM invoices i
WHERE invoice_total >  (
	SELECT AVG(invoice_total)
	FROM invoices
    WHERE client_id = i.client_id
);

# p52
USE sql_store;
SELECT *
FROM products p
WHERE NOT EXISTS (
	SELECT product_id
    FROM order_items
    WHERE product_id = p.product_id
)

# p53
USE sql_invoicing;
SELECT
	client_id,
    name,
    (SELECT SUM(invoice_total)
		FROM invoices
        WHERE client_id = c.client_id) AS total_sales,
    (SELECT SUM(invoice_total)/ COUNT(invoice_id)
		FROM invoices) AS average,
    (SELECT total_sales) - (SELECT average) AS difference
FROM clients c;

# p57
USE sql_store;
SELECT *
FROM orders
WHERE YEAR(order_date) = '2019';

# p60
USE sql_store;
SELECT
	CONCAT(first_name, ' ',last_name) AS customer,
    IFNULL(phone, 'Unknown') AS phone
FROM customers;

# p61
USE sql_store;
SELECT
	oi.product_id,
    p.name,
    COUNT(*) AS orders,
    IF(COUNT(*) = 1, 'Once', 'Many times') AS frequency
FROM order_items oi
JOIN products p USING (product_id)
GROUP BY oi.product_id;

# p62
USE sql_store;
SELECT customer_id,
	CONCAT(first_name, ' ', last_name) AS customer,
    points,
    CASE
		WHEN points >= 3000 THEN 'Gold'
        WHEN points < 2000 THEN 'Bronze'
        ELSE 'Silver'
	END AS category
FROM customers
ORDER BY points DESC;

# p63
USE sql_invoicing;
CREATE VIEW clients_balance AS
SELECT
	c.client_id,
    c.name,
    SUM(invoice_total - payment_total) AS balance
FROM clients c
JOIN invoices i USING (client_id)
GROUP BY client_id;

# p69
USE sql_invoicing;
DELIMITER $$
CREATE PROCEDURE get_invoices_with_balance()
BEGIN
	SELECT *
	FROM invoices_with_balance
    WHERE balance > 0;
END$$
DELIMITER ;

# p70
USE sql_invoicing;
DROP PROCEDURE IF EXISTS get_invoices_by_client;
DELIMITER $$
CREATE PROCEDURE `get_invoices_by_client`
(
	p_id INT
)
BEGIN
	SELECT * 
    FROM invoices i 
    WHERE i.client_id = p_id;
END$$
DELIMITER ;
CALL get_invoices_by_client(3);

# p73
USE sql_invoicing;
DROP PROCEDURE IF EXISTS get_payments;
DELIMITER $$
CREATE PROCEDURE `get_payments`
(
	p_client_id INT,
    p_payment_method_id TINYINT
)
BEGIN
	SELECT * 
    FROM payments p
    WHERE client_id = IFNULL(p_client_id, p.client_id) AND
		p.payment_method = IFNULL(p_payment_method_id, p.payment_method);
END$$
DELIMITER ;
-- test
CALL get_payments(NULL, NULL);

# p79
USE sql_invoicing;
DELIMITER $$ 
CREATE TRIGGER payments_after_delete
	AFTER DELETE ON payments
    FOR EACH ROW 
BEGIN
	UPDATE invoices 
    SET payment_total = payment_total - OLD.amount
	WHERE invoice_id = OLD.invoice_id;
END$$ 
DELIMITER ;
-- delete test
DELETE FROM payments
WHERE payment_id = 9;































