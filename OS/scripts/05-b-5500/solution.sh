#!/bin/bash

echo "<table>"
echo "<tr>"
echo "<th>Username</th>"
echo "<th>group</th>"
echo "<th>GECKO</th>"
echo "<th>login shell</th>"
echo "</tr>"

while read LINE
do

	echo "<tr>"
	while read -r FIELD
	do
		echo "<td>$FIELD</td>"
	done < <(echo $LINE | cut -d ":" -f 1,4,5,7 | tr ':' '\n')
	echo "</tr>"

done < /etc/passwd

echo "</table>"

