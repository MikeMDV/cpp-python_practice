## README file for external sort programming challenge

### Language

C++

### Operating systems

The program was compiled and tested on:

MacBook Pro laptop
 - Mac OS X 10.11.6
 - Compiled with Apple LLVM version 8.0.0(clang-800.0.42.1)

Amazon AWS EC2 instance
 - Centos 7.4.1708
 - Compiled with g++ version 7.2.1

### Directory structure

The program files, README, and Makefile are located in the michael.marven folder. Inside the michael.marven folder is the test_files folder with several files that can be used for testing

**external_sort_prob**
  - CommonDefs.h
  - CommonDefs.cpp
  - ExternalSort.h
  - ExternalSort.cpp
  - Makefile
  - problem_statement.md
  - README.md
  - ext_sort.cpp
  - **test_files folder**
    - test_file_blank.txt
    - test_file_medium.txt
    - test_file_medium_same_int.txt
    - test_file_medium_sorted.txt
    - test_file_medsmall.txt
    - test_file_small.txt
    - test_file_small_no_int.txt

### Building the files

The program files can be compiled from the external_sort_prob folder by entering `make` on the command line and `make clean` will remove compiled object files and the program binary.

### Usage

`ext_sort x_largest_values [file_path]`

x_largest_values - Positive integer for number of largest values from rightmost column [range: 1 - INT_MAX]

file_path        - Must be the absolute file path

### Tests performed and passed

Entering 0 or more than 3 command line arguments
 - Expected output: Usage statement printed to stdout

Entering an integer for x_largest_values that is less than 1 or greater than INT_MAX
 - Expected output: Usage statement printed to stdout

Entering a word or text character instead of an integer for x_largest_values
 - Expected output: Usage statement printed to stdout

Entering a non-existent file or wrong file path for 2nd arg
 - Expected output: Usage statement printed to stdout

Entering a non-existent file or wrong file path for input redirection of file to stdin
 - Expected output: Shell error statement printed to stdout

Using a file for input that is already sorted (test_file_medium_sorted.txt)
 - Expected output (x = 4):
   1000091057
   1000029441
   1000070639
   1000087266

Using a file in which all integers are the same value (test_file_medium_same_int.txt)
 - Expected output: X number of id's 
   Example (x = 4):
   1000000001
   1000001316
   1000007555
   1000004586

Using a file with a no data (test_file_blank.txt)
 - Expected output: Errors related to failure to convert string to integer

Using a file with no integer values with the id numbers
 - Expected output: Errors related to failure to convert string to integer and x number of id's

Requesting the 4 largest values of test_file_medium.txt
 - Expected output:
   1000091057
   1000029441
   1000070639
   1000087266

Tested with file sizes up to 40,000,000 lines (794.4 MB) on OS X and 8,000,000 lines (150.8 MB) on CentOS 7

### Operation

Since the requirements stated that my solution had to account for extremely large files, I decided to use an external sorting algorithm. The input file is read in runs of up to 3,000,000 lines. The program was tested with line sizes of approximately 20 bytes, consisting of 10 digit id numbers, 1 space, and integer values up to 8 digits. If the input file is smaller than 3M lines, only one read, sort, and write pass is performed and the output is read from the single temp file that is generated.

A run of data read from the input file is entered into a multimap that sorts the data in descending order on insertion into the multimap. Then the run is written to a temp file.

Once the input data has been read, sorted and written to k temp files, the data from the temp files is merged. Smaller chunks are read from each temp file. 3M / k runs of lines are read from each temp file and inserted into a priority queue that sorts the data in descending order upon insertion. The queue is then emptied by repeatedly writing the top value to an output file, then popping the pair off the queue. The queue is not emptied completely since there is no guarantee that the last value in the queue is greater than the first values waiting to be read in each of the temp files. 

The buffer is set at 300,000 pairs, which should be sufficient to properly merge the temp files in cases of randomly distributed values in the input file. But there could be an input file, possibly partially sorted with a limited range of values, that would not be properly sorted and merged even with the buffer. If input files with strange formatting were possibly frequent occurrences, the algorithm could be changed to randomize the input before the initial process of sorting and writing temp files, thus restoring the expected behavior.

The read, queue insertion, and write process is repeated until no data remains in the temp files, at which time the remaining data in the queue is written to the sorted output file.

The program then reads the first x lines from the sorted file to extract the requested id numbers and prints them to stdout.

### Notes

This was the first time that I coded an external sort algorithm. The approximate time I spent on the challenge is broken down below:

  - Research on external sort algorithms and looking up information on bug fixes: 5 hours
  - Coding the program and bug fixes: 8 hours
  - Testing on MacBook Pro and Amazon AWS EC2, and documentation: 4 hours

Each task was integrated with the others rather than in discrete blocks of time.

