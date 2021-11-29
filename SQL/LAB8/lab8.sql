/*
select kolona1, kolona2, ..... 
from име на таблица от която искаме да вземем данните
join имена-таблица2
on employees.pos_id = positions.pos_id 
where задаваме критерии за търсене 
group by спписък от полета
order by списък от полета за сортировка (намаляващ - desc и нарастващ - asc)
*/
 
 
-- да се изведе цялата информация от таблицата countries
 
SELECT * FROM countries; -- * - абсолютно всички колони изкарва
SELECT country_id AS ID, country_name AS Country FROM countries;
 
-- конкатенция на колони 
-- да се изведе конкатинирано първо име и фамилия на служителите
SELECT first_name || ' ' ||  last_name AS fullname FROM employees; -- || ЗНАК ЗА КОНКАТЕНАЦИЯ
 
-- агрегатни функции - max, min, avg, sum, count
-- да се намери най-високата заплата във фирмата
SELECT MAX(salary) AS MAX_salary FROM employees;
SELECT MIN(salary) AS MIN_salary FROM employees;
SELECT round(avg(salary),3) AS AVG_salary FROM employees;
SELECT SUM(salary) AS SUM_salary FROM employees;
 
-- да прресметнем броя на служителите 
 
SELECT COUNT(employee_id) FROM employees;
 
-- да се пресметне броя на служителите за всеки отдел
SELECT COUNT(department_id) AS empl_numb, department_id
FROM employees
GROUP BY department_id;
 
-- да се изведе информация за страницате, които имат 3-то ид на региона
SELECT * FROM countries
WHERE region_id=3;
 
-- да се изведе информация за служителите - първо име, фамилия, заплата, дата на назначаване и позиция която заема служителя с ST_CLERK job_id
SELECT first_name, last_name, salary, hire_date, job_id FROM employees
WHERE job_id = 'ST_CLERK'; -- =  tyrsi cqlostno sywpadenie
 
-- да се изведе информация за служителите - първо име, фамилия, заплата, дата на назначаване и позиция която 
--заема служителя имащ 'ne' във фамилията си
SELECT first_name, last_name, salary, hire_date, job_id FROM employees
WHERE last_name LIKE '%ne%';
/*
'%ne'  - търси в края 
'ne%' - търси в началото
'%ne%'  - търси навсякъде
*/
--да изведем изформация за служителите s data назначение за периода 01-01-2005 и 31-12-2006
SELECT first_name, last_name, salary, hire_date, job_id FROM employees
WHERE hire_date >= '2005-01-01' AND hire_date <= '2006-12-31'
ORDER BY hire_date;
 
SELECT first_name, last_name, salary, hire_date, job_id FROM employees
WHERE hire_date BETWEEN '2005-01-01' AND  '2005-12-31'
ORDER BY hire_date;
 
-- да се изведе информация за служителите, работещи в отдели с номера 20,40,60
SELECT first_name, last_name, hire_date, department_id FROM employees
WHERE department_id = 20 OR department_id = 40 OR department_id = 60
ORDER BY first_name, hire_date ;
 
 
SELECT first_name, last_name, hire_date, department_id FROM employees
WHERE department_id IN(30,40,60) AND first_name = 'Alexander' 
ORDER BY first_name, last_name;
