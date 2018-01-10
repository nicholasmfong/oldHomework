--Nicholas Fong COEN 280 HW 2: First, Last Name of actors in Star Wars movies

SELECT p.first_name, p.last_name, p.pid
FROM person p
WHERE p.pid IN(SELECT UNIQUE r.pid
      	       FROM roles r
	       WHERE r.mid IN(SELECT m.mid
      	       	     	      FROM movie m
	    		      WHERE NOT INSTR(m.name,'Star Wars') = 0));