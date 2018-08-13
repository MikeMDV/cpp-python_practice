/*              Author: Michael Marven
 *        Date Created: 03/18/18
 *  Date Last Modified: 03/18/18
 *
 */

// Program for external sort practice

#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>

#include "ExternalSort.h"

int main(int argc, char * argv[])
{   
    // Check if correct amount of arguments are present
    if (!(argc == 2 || argc == 3))
    {
        printUsage();
        return 0;
    }

    // Ensure integer for x largest values is in correct range
    int largestVals;
    try
    {
        largestVals = std::stoi(argv[1]);
        if (largestVals < 1)
        {
            throw largestVals;
        }
    }
    catch (const std::invalid_argument& e)
    {
        printUsage();
        return 0;
    }
    catch (const std::out_of_range& e)
    {
        printUsage();
        return 0;
    }
    catch (int i)
    {
        printUsage();
        return 0;
    }

    // Create ExternalSort object
    ExternalSort sorter(largestVals);

    // Read data from stdin or file and create sorted tmp files
    if (argc == 3)
    {
        std::ifstream file(argv[2]);
        if (file)
        {
            sorter.readData(file);
        }
        else
        {
            printUsage();
            return 0;
        }
    }
    else
    {
        sorter.readData(std::cin);
    }

    // Merge sorted tmp files if necessary and return sorted file name
    std::string sortedFile = sorter.mergeTmpFiles();

    // Retrieve id's associated with the x largest values from the sorted list
    std::vector<std::string> idsWithLargestVals = 
        sorter.getLargestVals(sortedFile);

    // Print the id's
    sorter.printIds(idsWithLargestVals);


    return 0;
}