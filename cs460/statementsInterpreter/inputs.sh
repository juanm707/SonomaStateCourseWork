FILES=./tests/*
for f in $FILES
do

    echo "Using test input $f file..."
    ./statement.x $f
    read -p "Press enter to continue"
done
