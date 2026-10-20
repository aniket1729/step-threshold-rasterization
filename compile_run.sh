#!/bin/bash

#source .venv/bin/activate
rm -f cg_lines
g++ -std=c++17 -Wall -Wextra main.cpp -o cg_lines
python viewer.py
