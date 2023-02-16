#!/bin/bash

MEM=$(free -h | awk '{ print $3; }' | awk 'NR==2 { print; }')
SWAP=$(free -h | awk '{ print $3; }' | awk 'NR==3 { print; }')

echo -n $MEM/$SWAP
