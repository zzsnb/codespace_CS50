/*List the titles of the five highest rated movies (in order) that Chadwick Boseman starred in, starting with the highest rated*/


/*JOIN the TABLE ratings and movies*/
SELECT title
  FROM movies
  JOIN ratings
    ON id = movie_id
 WHERE movie_id IN (

       SELECT movie_id
         FROM stars
        WHERE person_id =(

              SELECT id
                FROM people
               WHERE name = 'Chadwick Boseman'
         )
 )
 ORDER BY rating DESC
 LIMIT 5;



/* Find the movies thae Chadwick Boseman starred in*/

