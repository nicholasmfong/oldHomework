--Nicholas Fong COEN 280 HW 2: Find pairs of male and female actors that act together in at least 2 films, finding the total number of films together in descending order
--p1 and r1 refer to the male actor, p2 and r2 refer to the female actor
SELECT r1.pid AS male_pid, r2.pid AS female_pid, COUNT(*) AS films_together
FROM person p1, person p2, roles r1, roles r2
WHERE r1.mid = r2.mid AND r1.pid != r2.pid AND p1.pid = r1.pid AND p2.pid = r2.pid AND p1.gender = 'M' AND p2.gender = 'F'
GROUP BY r1.pid, r2.pid
HAVING COUNT(*) > 1
ORDER BY films_together DESC;