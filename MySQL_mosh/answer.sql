


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
SELECT *
FROM	order_items
WHERE order_id = 2
ORDER BY quantity * unit_price DESC;


# p17
SELECT *
FROM	customers
ORDER BY points DESC
LIMIT 3;

