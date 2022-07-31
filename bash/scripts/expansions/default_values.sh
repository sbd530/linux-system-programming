#!/bin/bash
# Default values
# ${parameter:-word} : parameter가 설정되어 있지 않거나 NULL이면 word값 사용
# ${parameter:=word} : parameter가 설정되어 있지 않거나 NULL이면 word값 사용. 그리고 paramater에 그 값 설정
# ${parameter:?word} : parameter가 설정되어 있지 않거나 NULL이면 에러 발생 & 메시지를 출력
# ${parameter:+word} : parameter가 NULL이 아닌 값으로 설정되어 있으면 word 값으로 치환

echo "${STR1:-hello}" # hello

echo "${STR2:=hi}" # hi
echo "${STR2}" # hi

STR3="aaa"
echo "${STR3:+hello}"

echo "${STR4:?STR3 is missing}" # ./default_values.sh: line 16: STR4: STR3 is missing
# echo $?
# 1