#!/bin/bash

SUCCESS=0
FAIL=0
COUNTER=0
DIFF_RES=""

declare -a tests=(
"VAR s test_0_grep.txt "
"VAR s test_1_grep.txt "
"VAR s test_2_grep.txt "
"VAR s test_3_grep.txt "
"VAR s test_4_grep.txt "
"VAR s test_5_grep.txt "
"VAR s test_6_grep.txt "
"VAR for s21_grep.c s21_grep.h Makefile "
"VAR for s21_grep.c "
"VAR nt s21_grep.c s21_grep.h Makefile "
"VAR int s21_grep.c "
)

testing()
{
    t=$(echo $@ | sed "s/VAR/$var/")
    ./s21_grep $t > test_s21_grep.log
    grep $t > test_sys_grep.log
    DIFF_RES="$(diff -s test_s21_grep.log test_sys_grep.log)"
    (( COUNTER++ ))
    if [ "$DIFF_RES" == "Files test_s21_grep.log and test_sys_grep.log are identical" ]
    then
      (( SUCCESS++ ))
      echo "\033[31m$FAIL\033[0m/\033[32m$SUCCESS\033[0m/$COUNTER \033[32msuccess\033[0m grep $t"
    else
      (( FAIL++ ))
      echo "\033[31m$FAIL\033[0m/\033[32m$SUCCESS\033[0m/$COUNTER \033[31mfail\033[0m grep $t"
    fi
    rm test_s21_grep.log test_sys_grep.log
}


# 1 параметр
for var1 in e i c l s  
do
    for i in "${tests[@]}"
    do
        var="-$var1"
        testing $i
    done
done

## 2 параметра
#for var1 in e i c l n h s o v
#do
#    for var2 in e i c l n h s o v
#    do
#        if [ $var1 != $var2 ]
#        then
#            for i in "${tests[@]}"
#            do
#                var="-$var1 -$var2"
#                testing $i
#            done
#        fi
#    done
#done
#
## 3 параметра
#for var1 in v c l n h o
#do
#    for var2 in v c l n h o
#    do
#        for var3 in v c l n h o
#        do
#            if [ $var1 != $var2 ] && [ $var2 != $var3 ] && [ $var1 != $var3 ]
#            then
#                for i in "${tests[@]}"
#                do
#                    var="-$var1 -$var2 -$var3"
#                    testing $i
#                done
#            fi
#        done
#    done
#done
#
## 2 сдвоенных параметра
#for var1 in v c l n h o
#do
#    for var2 in v c l n h o
#    do
#        if [ $var1 != $var2 ]
#        then
#            for i in "${tests[@]}"
#            do
#                var="-$var1$var2"
#                testing $i
#            done
#        fi
#    done
#done
#
## 3 строенных параметра
#for var1 in v c l n h o
#do
#    for var2 in v c l n h o
#    do
#        for var3 in v c l n h o
#        do
#            if [ $var1 != $var2 ] && [ $var2 != $var3 ] && [ $var1 != $var3 ]
#            then
#                for i in "${tests[@]}"
#                do
#                    var="-$var1$var2$var3"
#                    testing $i
#                done
#            fi
#        done
#    done
#done

echo "\033[31mFAIL: $FAIL\033[0m"
echo "\033[32mSUCCESS: $SUCCESS\033[0m"
echo "ALL: $COUNTER"

if [[ "$FAIL" -gt "0" ]]
then
    echo "AUTOTEST NOT PASSED"
    exit 1
else
    echo "AUTOTEST PASSED"
fi
