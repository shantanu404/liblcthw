echo "Running unit tests:"

for i in test/*_tests
do
    if test -f $i
    then
        if $VALGRIND ./$i 2>> tests/tests.log
        then
            echo $i PASS
        else
            echo "ERROR in test $i: here is tests/tests.log"
            echo "---------"
            tail tests/test.log
            exit 1
        fi
    fi
done

echo ""
