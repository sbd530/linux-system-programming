#!/bin/bash

function test1()
{
    if [ -z "$1" ]; then
        echo "param1 is missing"
        return 1
    fi
    if [ -z "$2" ]; then
        echo "param2 is missing"
        return 2
    fi
    # local variables
    local param1="$1"
    local param2="$2"
    echo "this is test1"
    echo "$param1 $param2!!"

    # return value = Integer 0 ~ 255 
    return 0
}

# fuctionName "param1" "param2"
test1 "hello" "world"
# get return value
test1_result="$?" 
echo "test1 returns $test1_result"
echo ""

# command substitution
result=$(test1 "h")
echo "test1 returns \"$result\""
# 화면에 출력될 표준출력을 반환
# test1 returns "param2 is missing"
