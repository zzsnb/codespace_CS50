/*Find the IDs of movies released in 2004
Find the IDs of people who starred in those movies
Find the names of people with those people IDs*/

SELECT name
  FROM people
 WHERE id IN (

    SELECT person_id
      FROM stars
     WHERE movie_id IN (

        SELECT id
          FROM movies
         WHERE year = 2004
    )
)ORDER BY birth;
