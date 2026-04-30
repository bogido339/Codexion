#!/bin/bash

PROGRAM="./codexion"

# Check that the executable file exists
if [ ! -f "$PROGRAM" ]; then
    echo "Error: $PROGRAM not found! Please run 'make' first."
    exit 1
fi

TOTAL=0
PASSED=0
FAILED=0

# Color settings
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Test running function
function run_test() {
    local expected=$1
    shift
    local args="$@"

    ((TOTAL++))
    
    # Run the program with a 5-second timeout to detect deadlocks
    # Output is redirected to /dev/null to keep the screen clean
    timeout 20 $PROGRAM $args > /dev/null 2>&1
    local exit_code=$?

    local is_pass=false

    if [ "$expected" == "ERROR" ]; then
        # We expect failure (exit code should not be 0, and should not be 124 (timeout))
        if [ $exit_code -ne 0 ] && [ $exit_code -ne 124 ]; then
            is_pass=true
        fi
    elif [ "$expected" == "SUCCESS" ]; then
        # We expect success (exit code 0, and if it's 124 that means a deadlock occurred)
        if [ $exit_code -eq 0 ]; then
            is_pass=true
        fi
    fi

    if [ "$is_pass" = true ]; then
        echo -e "${GREEN}[PASS]${NC} Test $TOTAL | Expected: $expected | Args: $args"
        ((PASSED++))
    else
        echo -e "${RED}[FAIL]${NC} Test $TOTAL | Expected: $expected | Args: $args (Exit Code: $exit_code)"
        ((FAILED++))
    fi
}

echo "========================================"
echo "       CODEXION 100 TEST CASES          "
echo "========================================"

# --- CATEGORY 1: MISSING / EXTRA ARGUMENTS (Tests 1-9) ---
run_test ERROR 
run_test ERROR "5"
run_test ERROR "5 800"
run_test ERROR "5 800 200"
run_test ERROR "5 800 200 200"
run_test ERROR "5 800 200 200 200"
run_test ERROR "5 800 200 200 200 5"
run_test ERROR "5 800 200 200 200 5 10"
run_test ERROR "5 800 200 200 200 5 10 fifo extra"

# --- CATEGORY 2: INVALID TYPES / STRINGS (Tests 10-20) ---
run_test ERROR "a 800 200 200 200 5 10 fifo"
run_test ERROR "5 b 200 200 200 5 10 fifo"
run_test ERROR "5 800 c 200 200 5 10 fifo"
run_test ERROR "5 800 200 d 200 5 10 fifo"
run_test ERROR "5 800 200 200 e 5 10 fifo"
run_test ERROR "5 800 200 200 200 f 10 fifo"
run_test ERROR "5 800 200 200 200 5 g fifo"
run_test ERROR "5 800 200 200 200 5 10 something"
run_test ERROR "5 800 200 200 200 5 10 FIFO"
run_test ERROR "5 800 200 200 200 5 10 edf2"
run_test ERROR "5 800 200 200 200 5 10 "

# --- CATEGORY 3: NEGATIVE AND ZERO VALUES (Tests 21-32) ---
run_test ERROR "-1 800 200 200 200 5 10 fifo"
run_test ERROR "0 800 200 200 200 5 10 edf"
run_test ERROR "5 -800 200 200 200 5 10 fifo"
run_test ERROR "5 0 200 200 200 5 10 edf"
run_test ERROR "5 800 -200 200 200 5 10 fifo"
run_test ERROR "5 800 0 200 200 5 10 edf"
run_test ERROR "5 800 200 -200 200 5 10 fifo"
run_test ERROR "5 800 200 0 200 5 10 edf"
run_test ERROR "5 800 200 200 -200 5 10 fifo"
run_test ERROR "5 800 200 200 0 5 10 edf"
run_test ERROR "5 800 200 200 200 -5 10 fifo"
run_test ERROR "5 800 200 200 200 0 10 edf"

# --- CATEGORY 4: VALID EDGE CASES / COOLDOWN ZERO / INT_MAX (Tests 33-40) ---
run_test SUCCESS "+5 800 +200 200 200 +5 0 fifo"
run_test ERROR "2147483648 800 200 200 200 5 10 fifo"
run_test ERROR "5 2147483648 200 200 200 5 10 edf"
run_test ERROR "5 800 2147483648 200 200 5 10 fifo"
run_test ERROR "5 800 200 2147483648 200 5 10 edf"
run_test ERROR "5 800 200 200 2147483648 5 10 fifo"
run_test ERROR "5 800 200 200 200 2147483648 10 edf"
run_test ERROR "5 800 200 200 200 5 2147483648 fifo"

# --- CATEGORY 5: 1 CODER BEHAVIOR (Tests 41-50) ---
run_test SUCCESS "1 800 200 200 200 5 10 fifo"
run_test SUCCESS "1 800 200 200 200 5 10 edf"
run_test SUCCESS "1 100 200 200 200 5 10 fifo"
run_test SUCCESS "1 100 200 200 200 5 10 edf"
run_test SUCCESS "1 800 200 200 200 1 10 fifo"
run_test SUCCESS "1 800 200 200 200 1 10 edf"
run_test SUCCESS "1 800 800 200 200 1 10 fifo"
run_test SUCCESS "1 800 800 200 200 1 10 edf"
run_test SUCCESS "1 60 60 60 60 1 0 fifo"
run_test SUCCESS "1 60 60 60 60 1 0 edf"

# --- CATEGORY 6: 2 CODERS (Tests 51-60) ---
run_test SUCCESS "2 800 200 200 200 5 10 fifo"
run_test SUCCESS "2 800 200 200 200 5 10 edf"
run_test SUCCESS "2 100 200 200 200 5 10 fifo"
run_test SUCCESS "2 100 200 200 200 5 10 edf"
run_test SUCCESS "2 400 200 100 100 5 10 fifo"
run_test SUCCESS "2 400 200 100 100 5 10 edf"
run_test SUCCESS "2 800 200 200 200 1 0 fifo"
run_test SUCCESS "2 800 200 200 200 1 0 edf"
run_test SUCCESS "2 60 60 60 60 1 0 fifo"
run_test SUCCESS "2 60 60 60 60 1 0 edf"

# --- CATEGORY 7: 5 CODERS (Tests 61-70) ---
run_test SUCCESS "5 800 200 200 200 5 10 fifo"
run_test SUCCESS "5 800 200 200 200 5 10 edf"
run_test SUCCESS "5 400 200 100 100 5 10 fifo"
run_test SUCCESS "5 400 200 100 100 5 10 edf"
run_test SUCCESS "5 800 200 200 200 1 10 fifo"
run_test SUCCESS "5 800 200 200 200 1 10 edf"
run_test SUCCESS "5 800 200 200 200 10 5 fifo"
run_test SUCCESS "5 800 200 200 200 10 5 edf"
run_test SUCCESS "5 60 60 60 60 1 0 fifo"
run_test SUCCESS "5 60 60 60 60 1 0 edf"

# --- CATEGORY 8: 10-20 CODERS SCALING (Tests 71-80) ---
run_test SUCCESS "10 800 200 200 200 2 10 fifo"
run_test SUCCESS "10 800 200 200 200 2 10 edf"
run_test SUCCESS "15 800 200 200 200 2 10 fifo"
run_test SUCCESS "15 800 200 200 200 2 10 edf"
run_test SUCCESS "20 800 200 200 200 2 10 fifo"
run_test SUCCESS "20 800 200 200 200 2 10 edf"
run_test SUCCESS "20 400 200 100 100 2 10 fifo"
run_test SUCCESS "20 400 200 100 100 2 10 edf"
run_test SUCCESS "20 60 60 60 60 1 0 fifo"
run_test SUCCESS "20 60 60 60 60 1 0 edf"

# --- CATEGORY 9: 50-100 CODERS STRESS (Tests 81-90) ---
run_test SUCCESS "50 800 200 200 200 1 10 fifo"
run_test SUCCESS "50 800 200 200 200 1 10 edf"
run_test SUCCESS "75 800 200 200 200 1 10 fifo"
run_test SUCCESS "75 800 200 200 200 1 10 edf"
run_test SUCCESS "100 800 200 200 200 1 10 fifo"
run_test SUCCESS "100 800 200 200 200 1 10 edf"
run_test SUCCESS "100 400 200 100 100 1 10 fifo"
run_test SUCCESS "100 400 200 100 100 1 10 edf"
run_test SUCCESS "100 60 60 60 60 1 0 fifo"
run_test SUCCESS "100 60 60 60 60 1 0 edf"

# --- CATEGORY 10: 200 CODERS EXTREME STRESS (Tests 91-100) ---
run_test SUCCESS "200 800 200 200 200 1 10 fifo"
run_test SUCCESS "200 800 200 200 200 1 10 edf"
run_test SUCCESS "200 400 200 100 100 1 10 fifo"
run_test SUCCESS "200 400 200 100 100 1 10 edf"
run_test SUCCESS "200 800 200 200 200 2 0 fifo"
run_test SUCCESS "200 800 200 200 200 2 0 edf"
run_test SUCCESS "200 100 200 200 200 1 10 fifo"
run_test SUCCESS "200 100 200 200 200 1 10 edf"
run_test SUCCESS "200 60 60 60 60 1 0 fifo"
run_test SUCCESS "200 60 60 60 60 1 0 edf"

echo "========================================"
echo "SUMMARY: $PASSED / $TOTAL Tests Passed."
if [ "$FAILED" -gt 0 ]; then
    echo -e "${RED}Failed Tests: $FAILED${NC}"
    exit 1
else
    echo -e "${GREEN}ALL TESTS PASSED SUCCESSFULLY!${NC}"
    exit 0
fi