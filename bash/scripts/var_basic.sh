#!/bin/bash

hello="hoi"
Hello="Hoi"
HELLO="HOI"

echo "$hello"
echo "${Hello}"
echo "${HELLO}"

E="aaa"
EE="bbb"
EEE="ccc"

# 변수 뒤에 바로 문자를 붙이려면 ${}를 쓴다.
echo "$E"
echo "$EE"
echo "${E}EE"

# 띄어쓰기가 포함된 문자열엔 ""로 반드시 래핑한다.
# TEST=hello world
TEST="hello wrold"
echo $TEST

# variable type
declare -i x 
x=123
echo $x
x="Hello"
echo $x
# -> 0
x=1111
echo $x

