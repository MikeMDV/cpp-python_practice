#ifndef COMMON_DEFS_H
#define COMMON_DEFS_H

/*              Author: Michael Marven
 *        Date Created: 03/18/18
 *  Date Last Modified: 03/21/18
 *
 */

#include <iostream>
#include <string>


/* Brief desc. - Prints a usage statement to stdout
 *
 */
void printUsage();

/* Brief desc. - A struct for a comparison function for pairs of strings and 
 *               ints 
 * Details     - For use with STL algorithms; Will return true when Pair 1 has
 *               a lesser int than pair 2;
 *
 */
struct lesser_int 
{
    inline bool operator() (const std::pair<std::string, int>& pair_1, 
                            const std::pair<std::string, int>& pair_2)
    {
        return (pair_1.second < pair_2.second);
    }
};

#endif // COMMON_DEFS_H
