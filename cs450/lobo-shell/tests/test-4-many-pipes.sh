OUT=tests/output/`basename ${0%.sh}`.out
EOUT=tests/output/`basename ${0%.sh}`.eout
rm -f $OUT $EOUT tests/output/tmp tests/output/etmp

./lobo_shell.x > $OUT << 'EOF'
cat /usr/share/dict/words | grep -i ^o | grep -i c$ | tail -100 | head | wc -c
EOF

cat /usr/share/dict/words | grep -i ^o | grep -i c$ | tail -100 | head | wc -c > $EOUT

diff $OUT $EOUT && echo "PASSED $0" || echo "TEST FAILED $0"

