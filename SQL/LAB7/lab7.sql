--създаване на таблица
 
 
CREATE TABLE Positions
(
pos_id INTEGER NOT NULL,
pos_name VARCHAR(20),
pos_salary NUMBER (7,2),
depatrmen_id INT
);
 
 
-- добавяне на P.K.
ALTER TABLE Positions ADD CONSTRAINT pos_PK PRIMARY KEY (pos_id);
 
-- добавяне на колона 
ALTER TABLE Positions ADD  depatrmen_id VARCHAR (20);
 
-- промяна на тип на колона
ALTER TABLE Positions MODIFY depatrmen_id INT;
 
-- изтриване на таблица
DROP TABLE Positions;
 
CREATE TABLE employees
(
empl_id INT NOT NULL,
empl_name VARCHAR(20),
empl_lastN VARCHAR(30),
empl_hire_date DATE,
pos_id INT,
PRIMARY KEY(empl_id)
);
 
-- създаване на връзка между две таблица P.K. => F.K.
 
ALTER TABLE employees  -- име на таблица, в която е F.K.
ADD CONSTRAINT  employees_pos_FK  -- име на правилото 
FOREIGN KEY (pos_id) -- име на колона, която е Ф.К за таблицата
REFERENCES positions(pos_id); -- име на таблица, където е нашия П.К. и съответно самаа колона П.К.
 
--добавяне на информация в таблицитте
INSERT INTO positions (pos_id,pos_name,pos_salary)
VALUES(1,'Sales manager', 1300.00);
 
INSERT INTO positions
VALUES(3,'Cleaner', 800.00);
 
INSERT INTO employees (empl_id, empl_name, empl_lastN, empl_hire_date, pos_id)
VALUES ( 4, 'Petq', 'Zheleva', '2016-03-02', 2);
 
-- редакттиране на записи
UPDATE positions -- име на таблица, в която искаме да направим промяна
SET pos_name = 'Programmer', -- колона, в която искаме да променяме = нова стойност
    pos_salary = 1500.00
WHERE pos_id = 2; --задаваме условие, по което да се направи промяната
 
 
UPDATE employees 
SET empl_name = 'Dimityr',
    empl_lastn = 'Stoyanov',
    empl_hire_date = '2010-12-02',
    pos_id = 3
WHERE empl_id = 1;
 
-- изтриване на записи от таблица
 
DELETE FROM employees -- таблица, от която искаме да изтрием
WHERE empl_id =2; -- условие, по което задаваме какво да се изтрие, ако се пропусне ова условие се изрива всички данни в таблицата
