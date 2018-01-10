--Nicholas Fong COEN 280 HW 2: Find actors with a Matt Damon number of 2
--Matt Damon is P17
--Finds the movies Matt Damon is in, then the actors in those movies, then the movies those actors are in, then the actors in those movies. Then it removes people with a Damon number of 0 or 1 by repeating the query and removing those people, and then finds their names
SELECT DISTINCT r.pid, p.first_name, p.last_name
from roles r, person p
WHERE p.pid = r.pid AND r.mid IN (SELECT DISTINCT r.mid
      FROM roles r
      WHERE r.pid IN (SELECT DISTINCT r.pid
      	    FROM roles r
      	    WHERE r.mid IN (SELECT r.mid
      	    	  FROM roles r
      	    	  WHERE r.pid = 'P17'))) AND r.pid NOT IN (SELECT DISTINCT r.pid
      	    FROM roles r
      	    WHERE r.mid IN (SELECT r.mid
      	    	  FROM roles r
      	    	  WHERE r.pid = 'P17'));