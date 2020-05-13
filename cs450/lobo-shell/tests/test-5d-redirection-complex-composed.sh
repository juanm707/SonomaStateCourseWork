OUT=tests/output/`basename ${0%.sh}`.out
EOUT=tests/output/`basename ${0%.sh}`.eout
rm -f $OUT $EOUT tests/output/tmp tests/output/etmp

./lobo_shell.x >$OUT << 'EOF'
wc -l < /usr/share/dict/words
whoami > tests/output/tmp
wc -w < /usr/share/dict/words >> tests/output/tmp
cat tests/output/tmp
EOF

wc -l < /usr/share/dict/words > $EOUT
whoami > tests/output/etmp
wc -w < /usr/share/dict/words >> tests/output/etmp
cat tests/output/etmp >> $EOUT

rm -f tests/output/tmp tests/output/etmp

diff $OUT $EOUT && echo "PASSED $0" || echo "TEST FAILED $0"

