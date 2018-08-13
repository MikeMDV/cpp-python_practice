/*              Author: Michael Marven
 *        Date Created: 03/18/18
 *  Date Last Modified: 03/18/18
 *
 */

#include <iostream>
#include <limits>

#include "CommonDefs.h"

/* Algorithm
 *     - Print the usage statement to stdout
 */
void printUsage()
{
    std::cout << "Usage:" << "\n"
              << "    tri_test x_largest_values [file_path]" << "\n\n"
              << "    x_largest_values - Positive integer for number of largest"
              << " values from rightmost "
              << "                       column [range: 1 - " 
              << std::numeric_limits<int>::max() << "]" << "\n"
              << "    file_path        - Must be the absolute file path" 
              << "\n\n";
}


