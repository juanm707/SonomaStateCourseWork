#!/bin/bash
WORD=$1
less /usr/share/dict/words | grep -E ^$WORD$ > /dev/null