import numpy as np
import matplotlib.pyplot as plt

# Genes del mejor individuo
a, b, c, d, e, f, g, h, i = -1.324198, 4.778893, 1.445051, -0.319529, 3.274941, 0.743736, 0.591754, -5.272073, 5.059664

# Función objetivo
def funcion_objetivo(x):
    return np.sin(x) + 2 * np.sin(1.5 * x - 5) + 3 * np.sin(x / 2 + 1)

# Función individuo
def funcion_individuo(x):
    return (a * np.sin(b * x + c) +
            d * np.sin(e * x + f) +
            g * np.sin(h * x + i))

# Generar datos
x = np.linspace(-500, 500, 1000)
y_objetivo = funcion_objetivo(x)
y_individuo = funcion_individuo(x)

# Graficar
plt.plot(x, y_objetivo, label="Función Objetivo", linewidth=2)
plt.plot(x, y_individuo, label="Función Individuo", linestyle="--")
plt.legend()
plt.title("Comparación entre Función Objetivo e Individuo")
plt.xlabel("x")
plt.ylabel("y")
plt.grid()
plt.show()