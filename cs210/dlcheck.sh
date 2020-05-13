#!/bin/bash

PLATE=$1

echo $PLATE | cut -f 1 -d "-" | grep -E ^[A-Z]{3}$ > /dev/null
if [ $? == 1 ]
then exit 1
fi

echo $PLATE | cut -f 2 -d "-" | grep -E ^[[:digit:]][[:digit:]][[:digit:]][[:digit:]]$ > /dev/null
if [ $? == 1 ]
then exit 1
fi

echo $PLATE | cut -f 3 -d "-" | grep -E ^[A-D]$ > /dev/null
if [ $? == 1 ]
then exit 1
fi