#!/bin/bash

export NUM=$1

echo $1 | grep -E '[0-9]|[0-9][0-9]|[0-9][0-9][0-9].[[^:alpha:]]' | grep -v '[[:alpha:]]' > /dev/null

if [ $? = 0 ]
then if [ $1 -lt 100 ]
     then echo "The provided number is less than 100"

     elif [ $1 = 100 ]
     then echo "The number provided is equal to 100"

     else
	 echo "The provided number is greater than 100"
	 fi

else
    exit 1
fi
