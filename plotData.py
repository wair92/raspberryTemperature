import sys
import datetime
import matplotlib as mpl
mpl.use('Agg')
import matplotlib.pyplot as plt

plt.plotfile(sys.argv[1] + sys.argv[2] + ".txt",(0,1), delimiter='\t')
plt.xlabel("Time")
plt.ylabel("Temperature [C]")
plt.grid()
my_fmt = mpl.dates.DateFormatter('%H:%M:%S')
plt.gcf().autofmt_xdate()
plt.gca().xaxis.set_major_formatter(my_fmt)
plt.savefig(sys.argv[1] + sys.argv[2] + '.png', dpi = 600)
