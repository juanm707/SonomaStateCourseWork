OUT=tests/output/`basename ${0%.sh}`.out
EOUT=tests/output/`basename ${0%.sh}`.eout
rm -f $OUT $EOUT tests/output/tmp tests/output/etmp

./lobo_shell.x > $OUT << 'EOF'
cat /usr/share/dict/words | head -100 | wc -l
EOF

cat /usr/share/dict/words | head -100 | wc -l > $EOUT

diff $OUT $EOUT && echo "PASSED $0" || echo "TEST FAILED $0"

