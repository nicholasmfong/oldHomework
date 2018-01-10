--Nicholas Fong COEN 280 HW 2: direction name and # movies directed for directors who directed over 5 movies in descending order
SELECT p.first_name, p.last_name, p.pid, COUNT(p.pid) AS movies_directed
FROM person p, movie m
WHERE p.pid = m.director
GROUP BY p.pid, p.first_name, p.last_name
HAVING COUNT(p.pid) > 4
ORDER BY movies_directed DESC;