/*              Author: Michael Marven
 *        Date Created: 03/18/18
 *  Date Last Modified: 03/30/18
 *
 */

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
#include <cstdio>
#include <iterator>
#include <queue>
#include <utility>
#include <limits>

#include "ExternalSort.h"

/* Algorithm
 *     - Assign the x largest vals parameter to m_largestVals
 */
ExternalSort::ExternalSort(int largestVals)
    : m_largestVals(largestVals)
{

}

/* Algorithm
 *     - Delete the temp files that were created
 */
ExternalSort::~ExternalSort()
{
    std::string fileName;

    for (int i = 1; i <= m_numOfRuns; i++)
    {
        fileName = getTempFileName(i);
        const char * fName = fileName.c_str();
        std::remove(fName);
    }

    fileName = "sorted.txt";
    std::ifstream file(fileName);
    if (file)
    {
        file.close();
        const char * fName = fileName.c_str();
        std::remove(fName);
    }

}

/* Algorithm
 *     - Get k runs consisting of INPUT_LINES number of lines each
 *       - Get a line of input
 *       - Create an istringstream from the input string
 *       - Get the id and value from the istringstream
 *       - Emplace value and id pairs into multimap which will sort the values
 *         in descending order as the pairs are entered into the multimap 
 *     - Open temp file and write contents of multimap
 *     - Close temp file after writing
 *     - Check for input eof after close rather than in the while loop condition
 *       to prevent the last line of input from being read twice
 *     - Store k number of runs in m_numOfRuns
 *
 */
void ExternalSort::readData(std::istream& in)
{
    // Uncomment below to print process update for user
    //std::cout << "Reading input..." << "\n";

    int lineCount;
    int k = 0;
    std::string input;
    std::string idInput;
    std::string intInput;
    
    while (true)
    {
        lineCount = INPUT_LINES;
        std::multimap<int, std::string, std::greater<int> > inputMap;
        while (lineCount > 0 && std::getline(in, input))
        {
            std::istringstream ss(input);
            std::getline(ss, idInput, ' ');
            std::getline(ss, intInput);
            int intVal = getIntFromString(intInput);
            
            inputMap.emplace(intVal, idInput);
            lineCount--;
        }

        k++;

        std::string tempFile = getTempFileName(k);
        std::ofstream out(tempFile);
        auto lastElement = inputMap.end();
        --lastElement; // Sets iter to last element position
        for (auto it = inputMap.begin(); it != inputMap.end(); it++)
        {
            if (it != lastElement)
            {
                out << it->second << " " << it->first << "\n";
            }
            else
            {
                out << it->second << " " << it->first;
            }
        }

        // Close file for clarity
        out.close();

        if (in.eof())
        {
            break;
        }
    }

    m_numOfRuns = k;
}

/* Algorithm
 *     - If only one sorted temp file exists, return the name of the temp file
 *     - Otherwise merge the temp files into one sorted file
 *       - Create a vector of ifstream objects to read the temp files
 *       - While the vector contains open temp files to read from
 *         - Read small chunks of each file and place values into priority queue
 *         - Write queue contents to sorted file, leaving a buffer of values 
 *           remaining in the queue
 *         - Delete any ifstream objects that reached EOF
 *       - Once all temporary files have been read, write remaining data from 
 *         queue to file
 *       - Return file name of sorted file
 *
 *     Note: Values are sorted in descending order as they are placed in the  
 *           priority queue and the data is removed and written in the same 
 *           sorted order. A buffer is needed to ensure that the next values
 *           read from the temp files after writing are sorted correctly since 
 *           there is no way to guarantee that if the queue was emptied, the  
 *           last pair in the queue is greater than the first pairs to be read 
 *           in all of the temp files. 
 *
 */
std::string ExternalSort::mergeTmpFiles()
{
    // Uncomment below to print process update for user
    // std::cout << "Processing data..." << "\n";

    if (m_numOfRuns == 1)
    {
        return getTempFileName(m_numOfRuns);
    }
    else
    {
        std::vector<std::ifstream> tempFileVec;
        std::string fileName;

        for (int i = 1; i <= m_numOfRuns; i++)
        {
            fileName = getTempFileName(i);
            tempFileVec.push_back(std::ifstream(fileName));
        }

        int lineCount;
        std::string input;
        std::string idInput;
        std::string intInput;
        std::priority_queue<std::pair<std::string, int>, 
                            std::vector<std::pair<std::string, int> >,
                            lesser_int> queue;

        std::string sortedFile = "sorted.txt";
        std::ofstream out(sortedFile);

        while (tempFileVec.size() > 0)
        {
            for (unsigned int i = 0; i < tempFileVec.size(); i++)
            {
                lineCount = INPUT_LINES / m_numOfRuns;
                while (lineCount > 0 && std::getline(tempFileVec[i], input))
                {
                    std::istringstream ss(input);
                    std::getline(ss, idInput, ' ');
                    std::getline(ss, intInput);
                    int intVal = getIntFromString(intInput);
                    
                    std::pair<std::string, int> pair(idInput, intVal);
                    queue.emplace(pair);
                    lineCount--;
                }
            }

            // Write map contents to sorted file
            unsigned int buffer = INPUT_LINES / 10;
            unsigned int writeSize = queue.size() - buffer;
            for (unsigned int i = 0; i < writeSize; i++)
            {
                out << queue.top().first << " " 
                    << queue.top().second << "\n";
                queue.pop();
            }

            // Delete any ifstream objects that reached EOF
            unsigned int count = 0;
            while (count < tempFileVec.size() && tempFileVec.size() > 0)
            {
                if (!tempFileVec[count])
                {
                    tempFileVec.erase(tempFileVec.begin() + count);
                }
                else
                {
                    count++;
                }
            }
        }

        // Write any remaining data to sorted file
        while (!queue.empty())
        {
            out << queue.top().first << " " 
                << queue.top().second << "\n";
            queue.pop();
        }

        return sortedFile;

    }

}

/* Algorithm
 *     - Open sorted file with largest x vals and id's
 *     - Read the first m_largestVals lines and extract id's
 *     - Return a vector of strings with the id's
 */
std::vector<std::string> ExternalSort::getLargestVals(std::string fileName)
{
    std::vector<std::string> out;
    std::string input;
    std::string idStr;
    std::string valStr;

    std::ifstream file(fileName);
    if (file)
    {
        for (int i = 0; i < m_largestVals; i++)
        {
            std::getline(file, input);
            std::istringstream ss(input);
            std::getline(ss, idStr, ' ');
            std::getline(ss, valStr);
            out.push_back(idStr);
        }

        file.close();
    }
    else
    {
        std::cout << "Error opening sorted file" << "\n";
    }

    return out;
}

/* Algorithm
 *     - Print the id's to stdout
 */
void ExternalSort::printIds(std::vector<std::string> idVec)
{
    for (unsigned int i = 0; i < idVec.size(); i++)
    {
        std::cout << idVec[i] << "\n";
    }
}

/* Algorithm
 *     - Build a temp file name based on the num parameter
 */
std::string ExternalSort::getTempFileName(int num)
{
    std::string fileName = "tmp";
    std::string fileNum = std::to_string(num);
    fileName += fileNum + ".txt";

    return fileName;
}

/* Algorithm
 *     - Try converting the string to an int
 *     - Return converted value or INT_MIN on error
 */
int ExternalSort::getIntFromString(std::string intStr)
{
    int intVal;
    try
    {
        intVal = std::stoi(intStr);
    }
    catch (const std::invalid_argument& e)
    {
        std::cerr << e.what();
        std::cout << "\n" << "Error: conversion from string to int" << "\n";
        intVal = std::numeric_limits<int>::min();
    }
    catch (const std::out_of_range& e)
    {
        std::cerr << e.what();
        std::cout << "\n" << "Error: conversion from string to int" << "\n";
        intVal = std::numeric_limits<int>::min();
    }

    return intVal;

}


