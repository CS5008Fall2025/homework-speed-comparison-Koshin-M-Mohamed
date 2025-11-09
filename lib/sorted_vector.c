/**
 * Contains functions for the sorted vector struct
 *
 * @author: Koshin Mohamed
 * @class: CS 5008
 * @term: Fall 2025
**/

#include "vector.h"
#include "movie.h"


/**
 * adds a movie to the sorted vector.
 * 
 * Based on the movie (compare_movies), it will find the correct index
 * using a linear search.
 * 
 * The moment it finds that the movie to add is greater than the
 * current movie, it will insert it at that next index calling vector_insert.
 * 
 * 
 * @param vector the vector to add the movie to
 * @param movie the movie to add
*/
void add_to_sorted_vector(SortedMovieVector * vector, Movie * movie) {
 if (vector == NULL || movie == NULL) return;

    int index = 0;
    while (index < vector->size && compare_movies(vector->movies[index], movie) < 0) {
        index++;
    }

    // vector_insert handles resizing + shifting automatically
    vector_insert(vector, movie, index);

}

/**
 * Finds a movie in the sorted vector based on the title only of the movie.
 *
 * strcasecmp is used to compare the titles, so the search is case insensitive.
 *
 * For example: int cmp = strcasecmp(title, movie->title);
 *
 * You will want to implement this as a binary search. It can be done with a loop
 * or using a helper recursive function (your choice). You are free
 * to add the helper function above if you need one. 
 *
 * @param vector the vector to search
 * @param title the title of the movie to find
 * @return the movie if found, NULL otherwise
 */
Movie * find_in_sorted_vector(SortedMovieVector * vector, const char * title) {
   if (vector == NULL || title == NULL) return NULL;

    for (int i = 0; i < vector->size; i++) {
        int cmp = strcasecmp(vector->movies[i]->title, title);
        if (cmp == 0) return vector->movies[i];
        if (cmp > 0) break;
    }
    return NULL;
}

/**
 * Checks if the sorted vector contains a movie with the given title.
 *
 * Very similar to find_in_sorted_vector, but instead of just finding
 * the movie will call vector_remove(vector, index) to remove the movie
 * returning the resulted removed movie.
 *
 * You will want to implement this as a binary search. It can be done with a loop
 * or using a helper recursive function (your choice). You are free
 * to add the helper function above if you need one.
 *
 * @param vector the vector to check
 * @param title the title to check for
 * @return the movie removed, NULL otherwise
 */
Movie* sorted_vector_remove(SortedMovieVector *vector, const char *title){
 if (vector == NULL || title == NULL) return NULL;

    for (int i = 0; i < vector->size; i++) {
        int cmp = strcasecmp(vector->movies[i]->title, title);
        if (cmp == 0) {
            return vector_remove(vector, i);
        }
        if (cmp > 0) break;
    }
    return NULL;
}
