# !/bin/bash

ls | grep ".txt"
ls | grep "^[a.h]" | xargs mv -t fd/

stat practice.sh
chmod +x practice.sh
stat practice.sh

ls | wc -l

who | awk '{print $1}' | sort | uniq
#takes the 1st column
ls -l | awk '{print $5}'
# prints the 5th column
ls -l | awk '{print $9,$5}'|sort

cat A2_02_1A.sh | grep "error"
cat -n A2_02_1A.sh | grep "error" # with output line

ls | sort

ls | xargs cat | grep "a" # searches a in content of all files
ls | grep "a" | xargs cat | grep "a" # searches a in content of all files which has a in name
ls | grep "^[a]" | xargs cat | grep "a" # now beginning with a

ls | grep "a" | xargs cat # prints the files
ls | grep "a" | cat # prints the names of the files

# thus without xargs cat gets the values from stdin(piped input) whreas when used xargs, cat uses those in args to generate o/p


ps aux | grep ps aux # for single word grep pattern without quote works but not for multiword, grep thinkd 2 different arguments
ps aux | grep "ps aux" # hence quote


