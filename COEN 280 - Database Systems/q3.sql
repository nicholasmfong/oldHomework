--Nicholas Fong COEN 280 HW 2: Director, movie title, and year of leap year drama movies
--Assume that leap years are the ones divisible by 4, ignoring the special rules for leap years
SELECT p.first_name, p.last_name, p.pid, m.name AS movie_title, m.release_year
FROM person p, movie m, genres g
WHERE p.pid = m.director AND MOD(m.release_year,4) = 0 AND g.mid = m.mid AND g.genre = 'Drama';