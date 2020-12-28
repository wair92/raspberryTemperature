import sys
import datetime
import matplotlib as mpl
mpl.use('Agg')
import matplotlib.pyplot as plt

def average7( data ):
    retVal = []
    for x in range( len( data ) ):
        element = 0.0
        i = 0.0
        for y in range (7):
            if( x - y < 0):
                break;
            i = i + 1
            element = element + float( data [x - y])
        element = element / i;
        retVal.append( str(element) )
    return retVal;

with open(sys.argv[1] + sys.argv[2] + ".txt") as f:
    lines = f.readlines()
    x_orig = [line.split()[0] for line in lines]
    y = [line.split()[1] for line in lines]

y2=average7(y)
x = [datetime.datetime.strptime(d, '%H:%M:%S') for d in x_orig]
dates = mpl.dates.date2num(x)
plt.plot(dates, y, color="gray")
plt.plot(dates, y2, color="blue")
plt.xlabel("Time")
plt.ylabel("Temperature [C]")
plt.grid()
my_fmt = mpl.dates.DateFormatter('%H:%M:%S')
plt.gcf().autofmt_xdate()
plt.gca().xaxis.set_major_formatter(my_fmt)
plt.savefig(sys.argv[1] + sys.argv[2] + '.png', dpi = 600)
