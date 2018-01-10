--Nicholas Fong COEN 280 HW 2: Actors never unemployed for more than 2 years
--Assume that this means that all movies an actor participated in are within 2 years of each other
SELECT p.pid, p.first_name, p.last_name, r.mid, m.release_year
FROM person p, roles r, movie m
WHERE p.pid = r.pid AND m.mid = r.mid;
--I'm not sure how to finish this, but I would group the movies based on the actor, and then calculate the differences between them, then filter out the ones with a difference >= 3 years