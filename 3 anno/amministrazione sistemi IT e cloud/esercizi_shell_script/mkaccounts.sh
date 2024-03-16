#!/bin/bash

# Variables
NEWUSERSFILE=/tmp/support/newusers

#Loop

for ENTRY in $(cat $NEWUSERSFILE); do
        FIRSTNAME=$(echo $ENTRY | cut -d: -f1)
        LASTNAME=$(echo $ENTRY | cut -d: -f2)
        TIER=$(echo $ENTRY | cut -d: -f4)

        #Make account name
        FIRSTINITIAL=$(echo $FIRSTNAME | cut -c 1 | tr 'A-Z' 'a-z')
        LOWERLASTNAME=$(echo $LASTNAME | tr 'A-Z' 'a-z')

        #Create Account
        ACCTNAME=$FIRSTINITIAL$LOWERLASTNAME
        echo $ACCTNAME
        useradd $ACCTNAME -c "$FIRSTNAME $LASTNAME"
done

# Count the number of the line
TOTAL=$(cat $NEWUSERSFILE | wc -l)

#Count the member of the variuos TIER
TIER1COUNT=$(grep -c :1$ $NEWUSERSFILE)
TIER2COUNT=$(grep -c :2$ $NEWUSERSFILE)
TIER3COUNT=$(grep -c :3$ $NEWUSERSFILE)

#Calculate the percentages
TIER1PCT=$(( $TIER1COUNT * 100 / $TOTAL))
TIER2PCT=$(( $TIER2COUNT * 100 / $TOTAL))
TIER3PCT=$(( $TIER3COUNT * 100 / $TOTAL))

#Print the report
echo "\"Tier 1\",\"$TIER1COUNT\",\"$TIER1PCT%\""
echo "\"Tier 2\",\"$TIER2COUNT\",\"$TIER2PCT%\""
echo "\"Tier 3\",\"$TIER3COUNT\",\"$TIER3PCT%\""
