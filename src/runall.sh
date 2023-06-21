#!/bin/bash

# Create ../results/tests/ directory if it doesn't exist
mkdir -p ../results/tests/

# Run the 4 algorithms (without TT) in parallel with a timeout of 1 hour
timeout 3600 ./alpha-othello 1 0 > ../results/alpha-othello-1-0.txt &
timeout 3600 ./alpha-othello 2 0 > ../results/alpha-othello-2-0.txt &
timeout 3600 ./alpha-othello 3 0 > ../results/alpha-othello-3-0.txt &
timeout 3600 ./alpha-othello 4 0 > ../results/alpha-othello-4-0.txt &

# Wait for the 4 algorithms to finish
sleep 3600

# 10 more minutes for the cpu to cool down
sleep 600

# Run the 4 algorithms (with TT) in parallel with a timeout of 1 hour
timeout 3600 ./alpha-othello 1 1 > ../results/alpha-othello-1-1.txt &
timeout 3600 ./alpha-othello 2 1 > ../results/alpha-othello-2-1.txt &
timeout 3600 ./alpha-othello 3 1 > ../results/alpha-othello-3-1.txt &
timeout 3600 ./alpha-othello 4 1 > ../results/alpha-othello-4-1.txt &