#!/bin/bash

# -a : AND
# -o : OR
# [ expr1 ] && [ expr2 ] : AND
# [ expr1 ] || [ expr2 ] : OR
# [[ expr1 && expr2 ]] : AND
# [[ expr1 || expr2 ]] : OR


A="1111"
B="222"
C="333"

if [ "$A" -gt "$B" -a "$A" -gt "$C" ]; then
    echo "\$A is the max"
else
    echo "not A"
fi

if [ "$A" -gt "$B" ] && [ "$A" -gt "$C" ]; then
    echo "\$A is the max"
else
    echo "not A"
fi

if [[ "$A" -gt "$B" && "$A" -gt "$C" ]]; then
    echo "\$A is the max"
else
    echo "not A"
fi