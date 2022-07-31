#!/bin/bash
# substring expansion
# ${parameter:offset}
# ${parameter:offset:length}

A="0123456789ABCDEF"

echo "\$A is $A"

echo "${A:5}" # 56789ABCDEF
echo "${A:5:2}" # 56
echo "${A:5: -5}" # 56789A

