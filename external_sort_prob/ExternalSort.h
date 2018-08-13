#ifndef EXTERNAL_SORT_H
#define EXTERNAL_SORT_H

/*              Author: Michael Marven
 *        Date Created: 03/18/18
 *  Date Last Modified: 03/30/18
 *
 */

#include <vector>
#include <string>
#include <iostream>

#include "CommonDefs.h"

const int INPUT_LINES = 3000000;

class ExternalSort
{
public:

    // Constructor
    ExternalSort(int largestVals);

    // Destructor
    ~ExternalSort();

    /* Brief desc. - Read data from stdin or file and create k runs of sorted 
     *               data in temp files
     *
     * param[in] in - Input stream; either a file stream or stdin
     *
     * Note - n lines of input are read from the original file and placed into 
     *        a temp file with max size of 3M lines. Multiple temp files are 
     *        used if the original file has more than 3M lines. 
     *        Before the values are written to the temp files, they are inserted
     *        into a multimap and sorted in descending order. In the case of an
     *        original file which is less than 3M lines, n lines are read, 
     *        inserted in the multimap and sorted in memory with O(n log n) 
     *        complexity, and n lines written to the temp file. Assuming the I/O
     *        operations are the limiting factor, the function will have O(2n), 
     *        or O(n) time complexity. In the case of the need for multiple temp
     *        files, each pair is still only read once and written once each, so
     *        the complexity is also O(n) assuming the I/O operations are the 
     *        limiting factor. 
     *        The space complexity is also O(n) since the file
     *        creates a series of temp files equivalent to the size of the 
     *        original file.
     *
     */
    void readData(std::istream& in);

    /* Brief desc. - Merge sorted temp files if necessary and return name of
     *               sorted file
     *
     * Returns - A string with the file name of the sorted file with n pairs 
     *           from the original input
     *
     * Note - n total lines of input are read from the k temp file(s) and placed  
     *        into a priority queue that sorts the pairs in descending order 
     *        upon insertion. Then the pairs are written to a final sorted file.
     *        Each pair is read froma temp file once and written to the final 
     *        sorted file once. Assuming the I/O operations are the limiting 
     *        factor, the function will have O(2n), or O(n) time complexity.
     *        The space complexity is also O(n) since the file
     *        creates a sorted file equivalent to the size of the original file.
     *
     */
    std::string mergeTmpFiles();

    /* Brief desc. - Retrieve the x largest values from the sorted list
     *
     * param[in] fileName - The file name from which to retrieve the largest 
     *                      values
     *
     * Returns - A vector of strings of id numbers associted with the largest
     *           int values
     *
     */
    std::vector<std::string> getLargestVals(std::string fileName);

    /* Brief desc. - Print the id's associated with the x largest values
     * 
     * param[in] idVec - The vector of id strings to be printed to stdout
     *
     */
    void printIds(std::vector<std::string> idVec);

private:

    /* Brief desc. - Retrieve temp file name with number incorporated
     *
     * param[in] num - The number to be incorporated into the temp file name
     *
     * Returns - A string with the temp file name
     */
    std::string getTempFileName(int num);

    /* Brief desc. - Retrieve an int from a string
     *
     * param[in] intStr - The int in string form to be converted
     *
     * Returns - The converted int from the string; returns INT_MIN on error
     */
    int getIntFromString(std::string intStr);

    // Attributes
    int m_largestVals;

    int m_numOfRuns;
};

#endif // EXTERNAL_SORT_H
