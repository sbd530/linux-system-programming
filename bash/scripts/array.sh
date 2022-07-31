#!/bin/bash
#### Indexed Array
# 선언 : declare -a array_var
# 선언 + 초기화 : array_var=(abc, def, xyz)
# 값 추가 : array_var+=(aaa)
# element 삭제 : unset array_var[1]
# key 전체 목록 : ${!array_var[@]}
# 전체 element : ${array_var[@]}
# n번째 element : ${array_var[n]}
# element 개수 : ${#array_var[@]}
# s번째 element부터 n개의 element : ${array_var[@]:s:n}

declare -a ARR1
ARR1+=(hello world there)
echo "ARR1] number of elems is ${#ARR1[@]}"
ARR1+=(1234)
echo "ARR1] number of elems is ${#ARR1[@]}"

ARR2=(hello world there 1234)
echo "ARR2] number of elems is ${#ARR2[@]}"

for elem in "${ARR2[@]}"
do
    echo "elem : ${elem}"
done

unset ARR2[1]

for key in "${!ARR2[@]}"
do
    echo "key : ${key}, elem : ${ARR2[$key]}"
done
###########################################################

#### Associative Array
# 선언 : declare -A array_var
# 초기화 : array_var=([key1]=hello [key2]=world)
# 값 추가 : array_var+=([key3]=aaa)
# element 삭제 : unset array_var[key]
# key 전체 목록 : ${!array_var[@]}
# 전체 element : ${array_var[@]}
# 특정 element : ${array_var[key]}
# element 개수 : ${#array_var[@]}

declare -A A_ARR
A_ARR=([a]=hello [b]=world [c]=there [d]=1234)

echo "A_ARR] number of elems is ${#A_ARR[@]}"

for elem in "${A_ARR[@]}"
do
    echo "elem : ${elem}"
done

unset A_ARR[b]
A_ARR+=([e]=9999)

for key in "${!A_ARR[@]}"
do
    echo "key : ${key}, elem : ${A_ARR[$key]}"
done