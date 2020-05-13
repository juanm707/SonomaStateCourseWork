#!/bin/bash

# password starts with an 'a'
SEARCHLOCATION=/usr/share/dict/words
DIGEST='611a600a8dad26b98f18cefec4315a6c92777292'

# openssl dgst -sha1 -hmac JOSHUA ~gondree/public_html/cs340_f19/unverified/whiskey.jpg 

# grep ^a SEARCHLOCATION

for OUTPUT in $(grep ^a $SEARCHLOCATION)
do

    # echo $OUTPUT
    RESULT=$(openssl dgst -sha1 -hmac $OUTPUT ~gondree/public_html/cs340_f19/unverified/whiskey.jpg | grep -oP '(?<== ).*')
    # echo $RESULT
    if [ $RESULT = $DIGEST ]
    then
	echo $OUTPUT
	exit 1
    fi
done
