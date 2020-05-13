var = 30 # when var is 30, this should reach "It is 30!"

if var < 200:
    print "Expression value is less than 200"

    if var == 150:

        print "Which is 150"

    elif var == 100:

        print "Which is 100"

    elif var == 50:

        print "Which is 50"

    elif var < 50:

        print "Expression value is less than 50"

        if var > 0:
            print "Value is positive"

            if var < 25:

                print "It is less than 25"

            elif var == 25:

                print "It is 25!"

            else:
                print "It is greater than 25"

                if var == 30:

                    print "It is 30!"

        elif var < 0:

            print "Value is negative"

        else:

            print "Value is 0"

else:

    print "Could not find true expression, it is > 200"

print "Good bye!"
