import csv
import matplotlib.pyplot as plt

with open("orbitas.csv") as f:
    r = csv.reader(f)
    next(r)
    cols = list(zip(*[[float(v) for v in fila] for fila in r]))

for k in range(len(cols) // 2):
    plt.plot(cols[2*k], cols[2*k+1], linewidth=0.6)

plt.axis("equal")
plt.title("Sistema de N cuerpos")
plt.show()