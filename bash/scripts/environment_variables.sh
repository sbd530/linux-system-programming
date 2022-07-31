#!/bin/bash

# export variables to declare env_var
# can use env_var in subshells
# can not use env_var in new shells
# ~/.bashrc 에서 환경변수 지정하면 다른 shell에서도 사용가능
# source ~/.bashrc

# CLI 에서 먼저 실행
# export AA="hello"

echo "my pid is $$"
echo "$AA"