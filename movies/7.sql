/*List all movies released in 2010 and their ratings, in descending order by rating*/
SELECT title,rating
  FROM ratings
   JOIN movies
    ON id = movie_id
 WHERE year = '2010'
ORDER BY rating DESC,title ASC;
