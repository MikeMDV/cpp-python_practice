## Problem Statement

Imagine a file in the following fixed format:

<unique_record_identifier><white_space><numeric_value>

e.g.
1637932011 9  
1637932028 350  
1637932037 25  
1637932056 231  
1637932058 109  
1637932066 111  
.  
.  
.  

Write a program that reads from 'stdin' the contents of a file, and optionally accepts the
absolute path of a file from the command line. The file/stdin stream is expected to be in the
above format. The output should be a list of the unique ids associated with the X-largest
values in the rightmost column, where X is specified by an input parameter. For example,
given the input data above and X=3, the following would be valid output:

1637932028  
1637932066  
1637932056  

Note that the output does not need to be in any particular order. Multiple instances of the
same numeric value count as distinct records of the total X. So if we have 4 records with
values: 200, 200, 115, 110 and X=2 then the result must consist of the two IDs that point to
200 and 200 and no more.

**Your solution should take into account extremely large files.**