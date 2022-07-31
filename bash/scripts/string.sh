#!/bin/bash

# string 변수 표기시에는 꼭 ""를 붙이자.

# = : is equal to
# == : is equal to
# != : is not equal to
A="hello"
B="hello"
if [ "$A" == "$B" ]; then
	echo "TRUE"
else
	echo "FALSE"
fi
# 사전순 비교
# < : is less than
# > : is greater than
# [ str1 \< str2 ];
# [[ str1 < str2 ];
C="hello"
D="world"
if [ "$A" \> "$B" ]; then
	echo "TRUE"
else
	echo "FALSE"
fi

# -z : is null
# -n : is not null
# Empty string("")도 null로 판단
# 할당 안된 변수도 null로 판단
E="hi"
F=""
if [ -z "$E" ]; then
	echo "TRUE"
else
	echo "FALSE"
fi
if [ -z "$F" ]; then
        echo "TRUE"
else
        echo "FALSE"
fi
