#!/bin/bash
######### string search and replace
# ${parameter/pattern/string}
# pattern이 /로 시작하면 매치되는 모든 pattern에 적용
# pattern이 #로 시작하면 pattern으로 시작하는 값에 적용
# pattern이 %로 시작하면 pattern으로 끝나는 값에 적용
# string을 주지 않으면 pattern에 매치되는 값은 삭제

A="ABCDEFGABCDEFG"

echo "${A/CD/cd}" # ABcdEFGABCDEFG

echo "${A//CD/cd}" # ABcdEFGABcdEFG

echo "${A//CD/}" # ABEFGABEFG

echo "${A/#ABCD/cd}" # cdEFGABCDEFG

echo "${A/%EFG/cd}" # ABCDEFGABCDcd

echo "#################################################"

######### string case modification
# ${parameter^^pattern} : 대문자화, 모든 글자에 적용
# ${parameter^pattern} : 대문자화, 첫 글자에만 적용
# ${parameter,,pattern} : 소문자화, 모든 글자에 적용
# ${parameter,pattern} : 소문자화 ,첫 글자에만 적용
# pattern이 생략되면 모든 문자 매치(모든 문자 변경)

str="hello world"
STR="HELLO WORLD"

echo "${str^^}" # HELLO WORLD
echo "${str^}" # Hello world
echo "${STR,,}" # hello world
echo "${STR,}" # hELLO WORLD

echo "${str^^[lo]}" # heLLO wOrLd

ARR=("hello" "world")
echo "${ARR[@]^}" # Hello World