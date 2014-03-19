#!/bin/bash

#couleurs

noir='\e[0;30m'
gris='\e[1;30m'
rougefonce='\e[0;31m'
rose='\e[1;31m'
vertfonce='\e[0;32m'
vertclair='\e[1;32m'
orange='\e[0;33m'
jaune='\e[1;33m'
bleufonce='\e[0;34m'
bleuclair='\e[1;34m'
violetfonce='\e[0;35m'
violetclair='\e[1;35m'
cyanfonce='\e[0;36m'
cyanclair='\e[1;36m'
grisclair='\e[0;37m'
blanc='\e[1;37m'

neutre='\e[0;m'

#variables
IGNORE=/dev/null
TIME='/usr/bin/time -f %U'
GENERATE_NBS_EXE=generateNumbers
GENERATE_NBS_SRC=nbr_generator.c
NUMBERS=numbers.txt
MAGNITUDE=64;
MIN_LOOP_BOUND=1
MAX_LOOP_BOUND=10
FACTOR_VAL=5
EXE=TpMultiThread

echo "RESULTS:" > results
touch results
gcc $GENERATE_NBS_SRC -o $GENERATE_NBS_EXE

for i in `seq $MIN_LOOP_BOUND $MAX_LOOP_BOUND`
do
	nbrOfValues=$(echo "$i * $FACTOR_VAL" | bc)
	echo -e "${orange}With $nbrOfValues values ${neutre}"
	echo $nbrOfValues > temp
	echo $MAGNITUDE >> temp
	./$GENERATE_NBS_EXE <temp > $NUMBERS
	echo TEST with $nbrOfValues values:>> results
	$TIME -o tempLog ./$EXE
	cat tempLog >> results
done
rm tempLog temp
echo -e "${bleuclair}---- results ----${neutre}"
cat results
