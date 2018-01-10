--Nicholas Fong COEN 280 HW 2: Difference in avg movie rating before 2005 and after 2005
--Assume that movies released after 2005 includes the year 2005
SELECT AVG(avg_rating) AS pre_2005_average_rating
FROM (SELECT m.mid, AVG(r.rating) AS avg_rating
     FROM rating r, movie m
     WHERE m.mid = r.mid AND m.release_year < 2005
     GROUP BY m.mid);

SELECT AVG(avg_rating) AS post_2005_average_rating
FROM (SELECT m.mid, AVG(r.rating) AS avg_rating
     FROM rating r, movie m
     WHERE m.mid = r.mid AND m.release_year >=  2005
     GROUP BY m.mid);