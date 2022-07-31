#!/bin/bash
# Indirect expansion
# ${!parameter}
# parameter 값을 이름으로 하는 변수의 값을 사용

ABC="hello"
XYZ="world"

indirect="ABC"

echo "$ABC" # hello
echo "$XYZ" # world

echo "${!indirect}" # hello