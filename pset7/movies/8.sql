SELECT p.name FROM people AS p WHERE p.id IN
(SELECT person_id FROM stars WHERE movie_id =
(SELECT id FROM movies WHERE title = 'Toy Story'));