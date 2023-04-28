SELECT m.title FROM movies m WHERE m.id IN (
    SELECT s.movie_id FROM stars s WHERE s.person_id IN (
        SELECT p.id FROM people p WHERE p.name = "Johnny Depp"
    )
    INTERSECT
    SELECT s.movie_id FROM stars s WHERE s.person_id IN (
        SELECT p.id FROM people p WHERE p.name = "Helena Bonham Carter"
    )
);
