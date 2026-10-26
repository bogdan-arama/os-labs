#!/bin/bash
# Lab 3, Part 4 - one-liners over access.log
# fields: 1=date 2=time 3=user 4=result(OK/FAIL) 5=page
# run inside ~/os-lab3:  bash oneliners.sh

# Q1. How many requests failed?
grep -c FAIL access.log

# Q2. How many different pages were requested, and which?
cut -d' ' -f5 access.log | sort -u | nl

# Q3. How many requests did each page get?
cut -d' ' -f5 access.log | sort | uniq -c

# Q4. Which user or users have the most failed requests, and how many?
grep FAIL access.log | cut -d' ' -f3 | sort | uniq -c | sort -rn | awk 'NR==1{max=$1} $1==max'

# Q5. How many requests did user3 make, and how many of them failed?
echo "user3 total: $(grep -cw user3 access.log), failed: $(grep -w user3 access.log | grep -c FAIL)"

# Q6. Print the last 3 failed requests, showing only time and user.
grep FAIL access.log | tail -3 | cut -d' ' -f2,3

# Q7. Which login shells appear in /etc/passwd, and how many accounts use each?
cut -d: -f7 /etc/passwd | sort | uniq -c | sort -rn

# Q8. Why do "ls /etc | wc -l" and "ls -l /etc | wc -l" differ by exactly one?
echo "ls: $(ls /etc | wc -l)  ls -l: $(ls -l /etc | wc -l)  extra line: $(ls -l /etc | head -1)"
