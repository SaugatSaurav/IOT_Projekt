set datafile separator ","
set title "Temperaturverlauf: 01 September bis 07 September"
set xlabel "Uhrzeit (Stunde)"
set ylabel "Temperatur (°C)"
set grid

# Zeitformat einstellen
set xdata time
set timefmt "%H:%M"
set format x "%H:%M"

# Achsenbereiche und Intervalle
set xrange ["08:00":"21:00"]
set xtics 3600

# Automatische Y-Skalierung, Werte liegen zwischen ca. 21 und 28
set yrange [21:30]
set ytics 21,1,30

# Legende und Ausgabe
set key outside right
set terminal pngcairo size 1600,800 enhanced font 'Arial,12'
set output "combined_temp_sep_plot.png"

plot "combined_temp_sep.csv" using 1:2 with linespoints lt 1 lw 2 lc rgb "red" title "Montag", \
     "combined_temp_sep.csv" using 1:3 with linespoints lt 2 lw 2 lc rgb "blue" title "Dienstag", \
     "combined_temp_sep.csv" using 1:4 with linespoints lt 3 lw 2 lc rgb "green" title "Mittwoch", \
     "combined_temp_sep.csv" using 1:5 with linespoints lt 4 lw 2 lc rgb "orange" title "Donnerstag", \
     "combined_temp_sep.csv" using 1:6 with linespoints lt 5 lw 2 lc rgb "purple" title "Freitag", \
     "combined_temp_sep.csv" using 1:7 with linespoints lt 6 lw 2 lc rgb "brown" title "Samstag", \
     "combined_temp_sep.csv" using 1:8 with linespoints lt 7 lw 2 lc rgb "black" title "Sonntag"





