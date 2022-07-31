#!/bin/bash
# Special parameters
# $0 : 호출된 스크립트 이름
# $# : 파라미터의 개수
# $* : 파라미터 전체. 파라미터 전체 목록을 하나의 word로 취급
# $@ : 파라미터 전체. 파라미터 전체 목록을 각각의 word로 취급
# $? : exit status
# ## : shell의 PID

if [ $# -ne 3 ]; then
    echo "usage: $0 ARG1 ARG2 ARG3"
    # exit status = 1
    exit 1
fi

echo "param is $1"
echo "PID is $$"

echo "number of args is $#"

for arg in "$@"
do
    echo "$arg in \$@"
done
# a in $@
# b in $@
# c in $@

for arg in "$*"
do
    echo "$arg in \$*"
done
# a b c in $*