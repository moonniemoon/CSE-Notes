--да се изведе име на страната и име на региона в който се намира тя
select countries.country_name, regions.region_name from countries
INNER join regions on regions.region_id = countries.region_id;
 
--да се изведе името на отдела и колко служителя работят в него
select count(departments.department_id), department_name
from employees
join departments 
on  departments.department_id = employees.department_id
group by department_name;
 
--да се изведе име,фамилия, име на отдела и поизиция, която заемат служителите 
select emp.first_name, emp.last_name, d.department_name, j.job_title
from employees emp
join departments d
on d.department_id = emp.department_id
join jobs j
on j.job_id = emp.job_id;
 
--да се изведе име на отдела, града, държавата и региона, в който се намират всички отдели с location_id = 1700
select d.department_name, l.city, c.country_name, r.region_name from locations l 
join countries c on c.country_id = l.country_id
join regions r on r.region_id = c.region_id
join departments d on d.location_id = l.location_id
where l.location_id = 1700;
 
--вложени заявки 
-- да се изведе име на служителя с минимлна заплата
select first_name, last_name,  salary from employees
where salary = ( select max(salary) from employees);
 
 
-- да се изкара име, фамилия, заплата на служителтие, които имат заплата по-голяма от тази на служителя с фамилия Abel
select first_name, last_name, salary from employees
where salary >= (select salary from employees where last_name = '&name');
 
-- да се изведе информацията за последните 5 назначени служителя
select * from (select first_name, last_name, hire_date from employees
Order by hire_date desc)
where rownum<=10;
