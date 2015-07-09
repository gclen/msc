#!/bin/bash

mkdir png_files
for FILE in $PWD/*.pdf
do
    convert -density 150 $FILE -quality 90 $( echo $FILE | sed 's/.pdf/.png/')
    mv $( echo $FILE | sed 's/.pdf/.png/') png_files
done

