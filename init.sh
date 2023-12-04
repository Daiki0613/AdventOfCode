#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <day_number>"
    exit 1
fi

day_number="$1"
template_directory="template"  # Replace this with the path to your template directory
new_directory="day${day_number}"

# Check if the new directory already exists
if [ -d "$new_directory" ]; then
    echo "Directory $new_directory already exists. Aborting."
    exit 1
fi

# Copy contents of the template directory to the new directory
cp -r "$template_directory" "$new_directory"

echo "Files copied to $new_directory successfully."