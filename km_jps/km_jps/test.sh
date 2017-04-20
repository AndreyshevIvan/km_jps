#!/bin/bash

projectConfiguration="Release"; #Possible options: Debug, Release
inputDir="./input";
i=0;

for inputFile in $inputDir/*
do
	cp "$inputDir/input$i.txt" ./input.txt;
	echo "Test #$i";
	../$projectConfiguration/km_jps.exe;
	echo "";
	((i++))
done

rm "./input.txt";
