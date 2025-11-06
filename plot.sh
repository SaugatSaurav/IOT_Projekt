#!/bin/bash
gnuplot combined_temp_aug_plot.gp
gnuplot combined_hum_aug_plot.gp
gnuplot combined_temp_sep_plot.gp
gnuplot combined_hum_sep_plot.gp

convert combined_temp_aug_plot.png six:-
convert combined_hum_aug_plot.png six:-
convert combined_temp_sep_plot.png six:-
convert combined_hum_sep_plot.png six:-
echo
