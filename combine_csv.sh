#!/bin/bash

combine_files() {
  pattern=$1
  output=$2
  base_file=$3

  cut -d, -f1 "$base_file" > "$output"

  echo "Dateien für $pattern:"
  ls $pattern

  for file in $pattern; do
    cut -d, -f2 "$file" > temp_values.txt
    paste -d, "$output" temp_values.txt > temp.csv
    mv temp.csv "$output"
  done

  rm temp_values.txt
  echo "Fertig: $output"
}

combine_files "block_*_hum_aug.csv" "combined_hum_aug.csv" "block_1_hum_aug.csv"
combine_files "block_*_temp_aug.csv" "combined_temp_aug.csv" "block_1_temp_aug.csv"
combine_files "block_*_hum_sep.csv" "combined_hum_sep.csv" "block_1_hum_sep.csv"
combine_files "block_*_temp_sep.csv" "combined_temp_sep.csv" "block_1_temp_sep.csv"
