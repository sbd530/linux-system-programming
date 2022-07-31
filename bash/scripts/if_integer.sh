#!/bin/bash

ABC=123
BCD=122

# if [ .. ]; then
# ...
# elif [ .. ]; then
# ...
# else
# ...
# fi

# Integer 비교
# -eq ==
# -ne !=
# -gt >
# -ge >=
# -lt <
# -le <=
if [ $ABC -ge $BCD  ]; then
	echo "ABC >= BCD"
	echo "and"
	if [ $ABC -eq $BCD ]; then
		echo "ABC == BCD"
	else
		echo "ABC > BCD"
	fi
else 
	echo "ABC < BCD"
fi
