#!/bin/bash

ls -1 *.{cpp,h} | ./genlist.py > list.tex
pdflatex -shell-escape listing.tex

