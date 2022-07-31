#!/bin/bash
# arithmetic expansion
# $(( expr )) -> 값을 리턴

A=5
let 'A=A+3'
echo $A

((A=A+3))
echo $A

A=$((A+3))
echo $A

echo "$A + 22 = $(( A + 22 ))"

B=5
echo "$(( B << 2 ))"
echo "$(( B | 2 ))"
echo "$(( ++B ))"

# 16진수를 10진수로 표현
echo "$(( 0x10 ))" # 16
