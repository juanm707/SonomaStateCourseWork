OUT=tests/output/`basename ${0%.sh}`.out
EOUT=tests/output/`basename ${0%.sh}`.eout
rm -f $OUT $EOUT tests/output/tmp tests/output/etmp

./lobo_shell.x >$OUT << 'EOF'
cat < /usr/share/dict/words | grep "ish" > tests/output/tmp
cat tests/output/tmp
EOF

cat < /usr/share/dict/words | grep "ish" > tests/output/etmp
cat tests/output/etmp >> $EOUT

if [ ! -f tests/output/tmp ] || [ ! -s tests/output/tmp ]; then
    echo "TEST FAILED $0"
    exit 1
fi
rm -f tests/output/tmp tests/output/etmp

diff $OUT $EOUT && echo "PASSED $0" || echo "TEST FAILED $0"

