#!/bin/bash

USERFILE=/home/ale/support/newusers

for USER in $(cat $USERFILE); do
        FIRSTNAME=$(echo $USER | cut -c 1 | tr 'A-Z' 'a-z')
        LASTNAME=$(echo $USER | cut -d: -f2 | tr 'A-Z' 'a-z')

        #Remove Account
        ACCTNAME=$FIRSTNAME$LASTNAME
        userdel -r $ACCTNAME
        echo "$ACCTNAME eliminato"
done
