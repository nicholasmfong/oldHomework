--Nicholas Fong COEN 280 HW 2: Actors/Actresses that collaborated with Steven Speilberg the most
SELECT p.first_name, p.last_name, p.pid, COUNT(r.pid) AS collaborations
FROM movie m, roles r, person p
WHERE r.pid = p.pid AND m.director = 'P32' AND r.mid = m.mid
GROUP BY p.pid, p.first_name, p.last_name
HAVING COUNT(r.pid) > 2
ORDER BY collaborations DESC;