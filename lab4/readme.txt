Justin McCaffrey
CSE 2561 - M 8:00
Lab 4

This program accepts 4 command line arguments:
lab4 <customer info file> <transaction file> <output file> <sorting order>
EX:"lab4 customer_info.txt transactions.txt out.txt 0"
Customer info is taken from the file and transactions are added up for each customer.
Info is then output to the output file sorted bases on the argument.
0-Sort by ID
1-Sort by first name
2-Sort by last name

**All files must be formatted properly(like the sample ones) for the program to work correcty**

To compile, run "gcc -g -o lab4 lab4.c -lm"
Then run "lab4" and follow the instructions.
