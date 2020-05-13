OUT=tests/output/`basename ${0%.sh}`.out
EOUT=tests/output/`basename ${0%.sh}`.eout
rm -f $OUT $EOUT tests/output/tmp tests/output/etmp

./lobo_shell.x &> $OUT << 'EOF'
echo someText > fakeFile.txt
chmod u+g+o-rx fakeFile.txt
cat fakeFile.txt
EOF

echo someText > fakeFile2.txt
touch error2.txt
chmod u+g+o-rx fakeFile.txt
cat fakeFile.txt 2> $EOUT

# remove all unnecesary output from the printf statements, if any
cat $OUT | tail -1 > test9.txt # tail -1 because the error is the last line
cat test9.txt > $OUT
rm test9.txt

diff $OUT $EOUT && echo "PASSED $0" || echo "TEST FAILED $0"
