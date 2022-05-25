#!/bin/sh


num=$1
command=$2
mytype=$3


while test $num -ne 0
do 
    if test $command == "A"
    then
    
        if test "$mytype" == "1000"
        then
            cat gen1000A | time --format="%U" ./sortA > /dev/null
        elif test "$mytype" == "10000"
        then
            cat gen10000A | time --format="%U" ./sortA > /dev/null
        elif test "$mytype" == "100000"
        then
            cat gen100000A | time --format="%U" ./sortA > /dev/null
        fi
        
        
    elif test $command == "D"
    then 
        if test "$mytype" == "1000"
        then
            cat gen1000D | time --format="%U" ./sortA > /dev/null
        elif test "$mytype" == "10000"
        then
            cat gen10000D | time --format="%U" ./sortA > /dev/null
        elif test "$mytype" == "100000"
        then
            cat gen100000D | time --format="%U" ./sortA > /dev/null
        fi
        
    elif test $command == "R"
    then 
        if test "$mytype" == "1000"
        then
            cat gen1000R | time --format="%U" ./sortA > /dev/null
        elif test "$mytype" == "10000"
        then
            cat gen10000R | time --format="%U" ./sortA > /dev/null
        elif test "$mytype" == "100000"
        then
            cat gen100000R | time --format="%U" ./sortA > /dev/null
        fi
    
        
    fi

    ((num--))
done
