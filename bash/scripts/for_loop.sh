#!/bin/bash
echo "============= for loop start ==============="
# for
# 1. basic
for animal in dog cat pig
do
    echo "Animal: $animal"
done
COLORS="red orange yellow blue"
for color in $COLORS 
do
    echo "Color: $color"
done
# 2. range
for i in {0..3} 
do
    echo "Number in range: $i"
done
for i in {0..11..3} # increment 3
do
    echo "Number in range with increment: $i"
done
# 3. C-style
for ((i = 0 ; i <= 3 ; i++)); do
    echo "Number in C-style: $i"
done
for ((;;)); do
    echo "Infinite loop"
    sleep 1
done
echo "============= for loop end ==============="