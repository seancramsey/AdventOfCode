#!/bin/bash
echo -n '#' > 'test.txt'
for (( i = 0; i < 511; i++ )); do
	echo -n '.' >> 'test.txt'
done
echo >> 'test.txt'
echo >> 'test.txt'
echo '#' >> 'test.txt'
