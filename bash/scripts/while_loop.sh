#!/bin/bash
# while
index=0
while [ $index -lt 10 ]
do
    echo "index is $index"

    # let "index++"
    ((index++))

    if [ $index -eq 4 ]; then
        continue
    fi

    echo "now index is $index"

    if [ $index -eq 8 ]; then
        break
    fi

done

# until
# index=0
# until [ $index -eq 10 ]
# do
#     echo "index is $index"

#     ((index++))
# done