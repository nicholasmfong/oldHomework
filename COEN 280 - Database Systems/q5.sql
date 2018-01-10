--Nicholas Fong COEN 280 HW 2: Actors/actresses who acted with 4+ different directors
SELECT p.pid, p.first_name, p.last_name, COUNT(DISTINCT m.director) AS directors
FROM movie m, roles r, person p
WHERE r.pid = p.pid AND m.mid = r.mid
GROUP BY p.pid, p.first_name, p.last_name
HAVING COUNT(DISTINCT m.director) > 3;