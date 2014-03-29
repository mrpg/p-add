p-add
=====

You can use p-add to add up *n* fractions to *m*<*n* output fractions (partial sums).

Compilation
-----------

	make

Usage
-----

	./p-add [number of parallel threads]

The number of parallel threads will also be the number of output fractions. p-add reads
from and writes to stdin in the same file format, so you could invoke it like that:

	cat millions-of-fractions.txt | ./p-add 10000 | ./p-add 40 | ./p-add 1 > result.txt

After this chain has finished (probably within a few seconds), you will end up with a single
big fraction that is, while not having lost any of its initial precision, the sum of all
fractions in the original file. That's great division of labor! You cannot fulfill this
task faster on normal hardware.

File format
-----------

	Numerator of first fraction
	Denominator of first fraction
	Numerator of second fraction
	Denominator of second fraction
	Numerator of third fraction
	Denominator of third fraction
	...

Example
-------

test.txt:

	1
	2
	3
	5
	8
	9
	11
	17
	22
	23

We invoke p-add:

	$ cat test.txt | ./p-add 1
	126419
	35190

Your local mathematician will confirm that 1/2+3/5+8/9+11/17+22/23 equals 126419/35190
(≈ 3.5925).
