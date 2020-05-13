#! /bin/bash

# This script test the functions of your lab03. The idea is that you create one main function for each
# BinSearchTree function that you want to test. For example, 

# a main function that tests "bool BinSearchTree::areIdentical( TreeNode *lRoot, TreeNode *aRoot );"
# mainForAreIdentical.cpp  

# a main function that tests "BinSearchTree *BinSearchTree::differenceOf( BinSearchTree *bst );""
# mainForDifference.cpp

# a main function that tests "bool BinSearchTree::iterFind( int v );"
# mainForFind.cpp

# This script iterates over all files that start with string "main" (mainForAreIdentical.cpp,
# mainForDifference.cpp, mainForFind.cpp, etc.), compiles each file with your BinSearchTree.cpp, 
# uses listOfNumbers.input (an argument to your main function) for input, run the resulting
# executable, and stores the output in a file with extension .output. Then, it compare this
# output file with ours. If there are differences, it displays them. Otherwise, it just prints "OK." 

rm -f *.o
> output
if [[ ! -e TreeNode.hpp ]]; then
    echo "Missing TreeNode.hpp. Terminating..."
    exit 1
fi

basePath="/home/faculty/cs315/public_html/labs/lab03/lab03testFiles"

cp $basePath/listOfNumbers.input .

#  Copy dontTest.txt once as students will have to change it to test their functions.
if [[ ! -e dontTest.txt ]]; then   
    cp $basePath/dontTest.txt .
fi    

for main in $(ls $basePath/main*.cpp); do
    mainNoPath=$(echo $main | sed 's+.*/++')
    cp $main $mainNoPath
    echo Testing $mainNoPath
    if [[ ! -e $mainNoPath ]]; then
	echo "Missing $mainNoPath (perhaps there is a permission problem? Terminating..."
	exit 1
    fi

    if [[ ! -e listOfNumbers.input ]]; then
	echo "Missing listOfNumbers (perhaps there is a permission problem? Terminating..."
	exit 1
    fi

    # Don't test the files that are in "dontTest.txt."

    if [[ -e dontTest.txt ]]; then
	if cat dontTest.txt | grep $mainNoPath > /dev/null ; then
	    echo Skipped this one as its name appears in dontTest.txt
	    echo Skipped this one as its name appears in dontTest.txt > $mainNoPath.output
	    continue;
	fi
    fi
    > $mainNoPath.output
    g++  -std=c++11 -Wall $mainNoPath BinSearchTree.cpp -o $mainNoPath.x
    if (( $? != 0 )); then
	echo "Unable to compile $mainNoPath... Skipping..."
	continue
    fi
    ./$mainNoPath.x listOfNumbers.input >> $mainNoPath.output
    if ! diff $mainNoPath.output $main.output > /dev/null; then
	echo "Diff results using your $mainNoPath.output."
	echo Your output
	cat $mainNoPath.output
	echo ""
	echo Our output
	cat $main.output
	echo
	echo
    else
	echo "OK"
    fi
    rm ./$mainNoPath.x

done
