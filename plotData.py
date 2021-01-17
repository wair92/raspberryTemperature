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
        retVal.append( element )
    return retVal;

with open(sys.argv[1] + sys.argv[2] + ".txt") as f:
    lines = f.readlines()
    x_orig = [line.split()[0] for line in lines]
    y = [line.split()[1] for line in lines]

fig, ax = plt.subplots()

y2=average7(y)
x = [datetime.datetime.strptime(d, '%H:%M:%S') for d in x_orig]
dates = mpl.dates.date2num(x)
y_min = min(y2)
y_max = max(y2)
x_max = y2.index(max(y2))
x_min = y2.index(min(y2))

line1, = ax.plot( dates, y, marker='o', markersize=2, ls='', color="lightgray", label='Measured')
line2, = ax.plot( dates, y2, marker='o', markersize=2, ls='', color="green", label='7 Average')
max_point, = ax.plot( [dates[x_max]], [y_max], "ro", label='Max')
min_point, = ax.plot( [dates[x_min]], [y_min], "bo", label='Min')

ax.annotate("{:10.2f}".format(y_max), xy=(dates[x_max], y_max), xytext=(dates[x_max], y_max))
ax.annotate("{:10.2f}".format(y_min), xy=(dates[x_min], y_min), xytext=(dates[x_min], y_min))

first_legend = ax.legend(handles=[line1, line2, max_point, min_point], loc='best')
plt.gca().add_artist(first_legend)

plt.xlabel("Time")
plt.ylabel("Temperature [C]")
#plt.ylim([15, 30])
ax.grid()
my_fmt = mpl.dates.DateFormatter('%H:%M:%S')
plt.gcf().autofmt_xdate()
plt.gca().xaxis.set_major_formatter(my_fmt)
now = datetime.datetime.now()
plt.title("Generated {}/{:02d}/{:02d} {:02d}:{:02d}, current temperature: {:10.2f}".format( now.year, now.month, now.day, now.hour, now.minute , y2[-1] ))
plt.savefig(sys.argv[1] + sys.argv[2] + '.png', dpi = 600)
