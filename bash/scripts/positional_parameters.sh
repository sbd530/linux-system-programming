#!/bin/bash
# Positional parameters
# $1, $2, $3, ${10} 두자리수 이상은 {}
# 스크립트 실행시 파라미터를 받아올 수 있음
# 함수 실행 시 파라미터를 받아올 수 있음
# shift command : 파라미터 포인터를 한칸 넘김

# Special parameters
# $0 : 호출된 스크립트 이름
# $# : 파라미터의 개수
# $* : 파라미터 전체. 파라미터 전체 목록을 하나의 word로 취급
# $@ : 파라미터 전체. 파라미터 전체 목록을 각각의 word로 취급
# $? : exit status
# ## : shell의 PID

echo "number of args is $#"
echo "\$* : $*"
echo "\$@ : $@"
# shift
# echo "\$1 is $1"
# echo "\$2 is $2"
# echo "\$3 is $3"

for arg in "$@"
do
    echo "$arg in \$@"
done

while [ "$#" -gt 0 ]
do
    echo "$1 by while"
    shift
done

