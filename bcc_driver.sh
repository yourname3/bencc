#!/bin/bash

input_file="$1"
dash=""

# --lexer, etc arguments
if [[ "$input_file" == "--*" ]]; then
    dash="$1"
    input_file="$2"
fi

if ! [[ -f "$input_file" ]]; then
    echo "no such input file $input_file"
    exit 1
fi

program_name="${input_file%.c}"
preprocessed="$program_name.i"
assembly="$program_name.S"

gcc -E -P "$input_file" > "$preprocessed"

./bencc $dash "$preprocessed" > "$assembly"
status="$?"
rm "$preprocessed"
if [[ "$status" -ne 0 ]]; then
    exit "$status"
fi

gcc "$assembly" -o "$program_name"
rm "$assembly"
