#!/bin/bash

NUM=$1

curl -s http://api.icndb.com/jokes/$NUM?exlude=%5Bexplicit%5D | python -m json.tool | grep "joke" | cut -f 4 -d '"'