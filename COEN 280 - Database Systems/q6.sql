--Nicholas Fong COEN 280 HW 2: Rating span sorted from highest to lowest then by movie title
SELECT r.mid, m.name, MAX(r.rating) - MIN(r.rating) AS rating_span
FROM rating r, movie m
WHERE m.mid = r.mid
GROUP BY r.mid, m.name
ORDER BY rating_span DESC, m.name ASC;