OUT=tests/output/`basename ${0%.sh}`.out
EOUT=tests/output/`basename ${0%.sh}`.eout
rm -f $OUT $EOUT tests/output/tmp tests/output/etmp

# under this umask, we would expect to see 664
umask 002

./lobo_shell.x > $OUT << 'EOF'
whoami > tests/output/tmp
cat tests/output/tmp
EOF

whoami > tests/output/etmp
cat tests/output/etmp > $EOUT

if [ ! -f tests/output/tmp ] || [ ! -s tests/output/tmp ]; then
    echo "TEST FAILED $0"
    exit 1
fi

if [ -z $(find tests/output/tmp -perm 664) ]; then
    echo "TEST FAILED $0"
    exit 2
fi
rm -f tests/output/tmp tests/output/etmp

diff $OUT $EOUT && echo "PASSED $0" || echo "TEST FAILED $0"

