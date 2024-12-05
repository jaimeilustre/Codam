#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m'

# Create test files
echo "This is test file content" > infile
echo -e "apple\nbanana\napple pie\norange" > infile2
echo "Test with spaces and special chars: $#@!" > infile3

# Cleanup function
cleanup() {
    rm -f outfile outfile_shell test_outfile infile infile2 infile3
}

# Test function
run_test() {
    local test_name="$1"
    local infile="$2"
    local cmd1="$3"
    local cmd2="$4"
    
    ./pipex "$infile" "$cmd1" "$cmd2" "test_outfile"
    pipex_exit=$?
    
    eval "< $infile $cmd1 | $cmd2 > outfile_shell"
    shell_exit=$?
    
    if diff test_outfile outfile_shell > /dev/null && [ $pipex_exit -eq $shell_exit ]; then
        printf "${GREEN}[OK]${NC} %s\n" "$test_name"
    else
        printf "${RED}[KO]${NC} %s\n" "$test_name"
        echo "Expected output (shell):"
        cat outfile_shell
        echo "Your output (pipex):"
        cat test_outfile
        echo "Shell exit code: $shell_exit"
        echo "Pipex exit code: $pipex_exit"
    fi
}

# Error handling tests
test_errors() {
    printf "\n${BLUE}Testing error handling:${NC}\n"
    
    ./pipex "nonexistent" "ls" "wc" "test_outfile" 2>/dev/null
    local exit_code=$?
    if [ $exit_code -ne 0 ]; then
        printf "${GREEN}[OK]${NC} Non-existent input file (exit code: $exit_code)\n"
    else
        printf "${RED}[KO]${NC} Non-existent input file (exit code: $exit_code)\n"
    fi
    
    ./pipex "infile" "invalidcmd" "wc" "test_outfile" 2>/dev/null
    exit_code=$?
    if [ $exit_code -ne 0 ]; then
        printf "${GREEN}[OK]${NC} Invalid command (exit code: $exit_code)\n"
    else
        printf "${RED}[KO]${NC} Invalid command (exit code: $exit_code)\n"
    fi
    
    ./pipex "infile" "ls" "outfile" 2>/dev/null
    exit_code=$?
    if [ $exit_code -ne 0 ]; then
        printf "${GREEN}[OK]${NC} Wrong number of arguments (exit code: $exit_code)\n"
    else
        printf "${RED}[KO]${NC} Wrong number of arguments (exit code: $exit_code)\n"
    fi
}

printf "${BLUE}Starting pipex tests...${NC}\n\n"

# Basic tests
run_test "Basic test" "infile" "cat" "grep test"
run_test "grep | wc" "infile2" "grep apple" "wc -l"
run_test "cat | grep" "infile3" "cat" "grep special"

# Complex tests
run_test "Multiple spaces" "infile" "tr ' ' '_'" "tr '_' '-'"
run_test "Special characters" "infile3" "grep '$'" "wc -w"
run_test "Quoted arguments" "infile2" "grep 'apple pie'" "wc -l"

# Error tests
test_errors

# Cleanup
cleanup

printf "\n${BLUE}Tests completed.${NC}\n"
