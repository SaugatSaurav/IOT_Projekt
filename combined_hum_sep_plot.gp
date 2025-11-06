set datafile separator ","
set title "Luftfeuchtigkeit: 01 September bis 07 September"
set xlabel "Uhrzeit"
set ylabel "Luftfeuchtigkeit (%)"
set grid

# Zeitformat einstellen
set xdata time
set timefmt "%H:%M"
set format x "%H:%M"

# Achsenbereiche und Intervalle
set xrange ["08:00":"21:00"]
set xtics 3600

# Automatisches Y-Limit (oder festlegen, falls nötig)
set yrange [50:60]
set ytics 50,2,60

# Legende und Ausgabe
set key outside right
set terminal pngcairo size 1600,800 enhanced font 'Arial,12'
set output "combined_hum_sep_plot.png"

plot "combined_hum_sep.csv" using 1:2 with linespoints lt 1 lw 2 lc rgb "red" title "Montag", \
     "combined_hum_sep.csv" using 1:3 with linespoints lt 2 lw 2 lc rgb "blue" title "Dienstag", \
     "combined_hum_sep.csv" using 1:4 with linespoints lt 3 lw 2 lc rgb "green" title "Mittwoch", \
     "combined_hum_sep.csv" using 1:5 with linespoints lt 4 lw 2 lc rgb "orange" title "Donnerstag", \
     "combined_hum_sep.csv" using 1:6 with linespoints lt 5 lw 2 lc rgb "purple" title "Freitag", \
     "combined_hum_sep.csv" using 1:7 with linespoints lt 6 lw 2 lc rgb "brown" title "Samstag", \
     "combined_hum_sep.csv" using 1:8 with linespoints lt 7 lw 2 lc rgb "black" title "Sonntag"


