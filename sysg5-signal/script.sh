#!/bin/bash

restart () 
{
read -p 'Restart ? (y/n) : ' next
echo "$next"
while [[ $next = 'y' ]]
do
    echo "$i. ${tableau[$i]}"
    ./${tableau[$i]}
    read -p 'Restart ? (y/n) : ' next
done
}

if [ -e '/usr/bin/gcc' ] && [ -e '/usr/bin/make' ]
then
    let "i = 0"
    let "max = 8"
    tableau=('read_time_out.exe' 'read_time_out2.exe' 'blocage_signal_sans_masque.exe' 'blocage_signal_avec_masque.exe' 'nb_signal.exe' 'file_attente_signal.exe' 'bascule.exe' 'bascule_viable.exe') 

    make

    read -p 'Start ?' 
    while [ $i -lt $max ]
    do
        echo "$i. ${tableau[$i]}"
        ./${tableau[$i]}
        restart
        let "i = i +1"
    done
else
    echo 'Il manque gcc ou make'
fi
