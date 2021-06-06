We have made the profile on the instruction LW.
LW’s addresses [word’s address] are given in file LW-sAddrs.txt as the hexadecimal format. In MIPS, 32-bits comprise the word. The content of the corresponding address is the starting address of the word. Theaddress sequence can be repeat. Let’s consider the designed CPP iterated 10,000 times, and the LW-sAddrs.txt contains 10-address. In each iteration, the program fetched a block. The block size set a prior.

So, at the 11-th iteration (or less than the 11-th iteration, which depends on block size) and onwards LW’s
address sequence can repeats.data (hex) information in a table format at the end of 2nd repetition. 

The user can choose the following cache organization:
```
1. Fully associative cache (Marks: 6)
	a. Block size
		i. 1-word
		ii. 2-word
	b. Replacement algorithms
		i. FIFO (Marks: 7)
		ii. LRU (Marks: 10)
2. Direct mapped cache (Marks: 5)
	a. Block size
		i. 1-word
		ii. 2-word

3. Set associative cache (Marks: 7)
	a. No of ways
	i. Block size
		1. 1-word
		2. 2-word
	b. Replacement algorithms
		i. FIFO
		ii. LRU
```
