#!/bin/bash

HTTP_404="HTTP/1.1 404 Not Found"
HTTP_400="HTTP/1.1 400 Bad Request"
HTTP_200="HTTP/1.1 200 OK"

# Read input file
read myvar

http_method=$(echo $myvar | awk '{print $1}')
resource=$(echo $myvar | awk '{print $2}')
if [ $resource == "/status" ]
then rows=$(cat messages.dat | wc -l)
     echo -e $HTTP_200'\n'Content-Type: application/json'\n\n'{'"''record_count''"'': ''"'$rows'"' }
     exit 0
fi

recepient=$(echo $resource | awk -F/ '{print $3}')
name=$(echo $recepient | grep -E [[:alpha:]] | grep -E [[:digit:]])
chekiar=$(echo $?)

if [ $chekiar == 0 ]
then echo $HTTP_400
     exit 1
fi

RECID=$(id -u $recepient >& /dev/null)

check=$(echo $?)
if [ $check == 1 ]
then echo $HTTP_404
     exit 1
fi
RECID=$(id -u $recepient)

ISTHERE=$(cat messages.dat | grep -E ^$RECID?)
cheque=$(echo $?)

if [ $cheque == 1 ]
then echo -e $HTTP_200'\n'Content-Type: application/json'\n\n'{}
     exit 0
fi

MAIL=$(cat messages.dat | grep -E ^$RECID? | sort -t',' -k 3 | head -n 1)

echo $HTTP_200
echo "Content-Type: application/json"

SENDER=$(echo $MAIL | cut -f 2 -d ',')

ID_SENDER=$(id -un $SENDER)
MESSAGE=$(echo $MAIL | cut -f 4 -d ',')

TIME=$(echo $MAIL | cut -f 3 -d ',')

TIMECONVERT=$(date --rfc-3339=seconds -d @$TIME)

echo -e '{\n\t"sender": ''"'$ID_SENDER'"'',\n\t"message": ''"'$MESSAGE'"'',\n\t"timestamp": ''"'$TIMECONVERT'"''\n}'
