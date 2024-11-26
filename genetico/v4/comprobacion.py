import numpy as np
import matplotlib.pyplot as plt


# Genes de tu mejor individuo
'''
genes = {
    'a': -2.826319,
    'b': 4.778893,
    'c': 8.361766,
    'd': -2.940458,
    'e': 5.777459,
    'f': 8.428907,
    'g': 0.948820,
    'h': 7.277139,
    'i': 9.429304
}
'''
genes = {
    'a' : 1.987060,
    'b' : -1.499374,
    'c' : 8.140812,
    'd' : 3.006989,
    'e' : 0.498978,
    'f' : 7.286294,
    'g' : 0.997040,
    'h' : -1.004364,
    'i' : -9.423200
    }

# Función objetivo
def funcion_objetivo(x):
    return np.sin(x) + 2 * np.sin(1.5 * x - 5) + 3 * np.sin(x / 2 + 1)

# Función generada por tu individuo
def funcion_individuo(x, genes):
    return (genes['a'] * np.sin(genes['b'] * x + genes['c']) +
            genes['d'] * np.sin(genes['e'] * x + genes['f']) +
            genes['g'] * np.sin(genes['h'] * x + genes['i']))

# Generar valores de x
x_min = -500.0
x_max = 500.0
num_puntos = 1000
x_values = np.linspace(x_min, x_max, num_puntos)

# Calcular valores de y para ambas funciones
y_objetivo = funcion_objetivo(x_values)
y_individuo = funcion_individuo(x_values, genes)

# Calcular errores
errores = np.abs(y_objetivo - y_individuo)
error_total = np.sum(errores)
error_promedio = np.mean(errores)

# Imprimir errores
print(f"Error Total Calculado: {error_total}")
print(f"Error Promedio Calculado: {error_promedio}")

# Graficar funciones
plt.figure(figsize=(12, 6))
plt.plot(x_values, y_objetivo, label='Función Objetivo')
plt.plot(x_values, y_individuo, label='Función del Individuo', linestyle='--')
plt.xlabel('x')
plt.ylabel('y')
plt.title('Comparación entre la Función Objetivo y la Función del Individuo')
plt.legend()
plt.grid(True)
plt.show()

# Graficar error absoluto
plt.figure(figsize=(12, 6))
plt.plot(x_values, errores, label='Error Absoluto')
plt.xlabel('x')
plt.ylabel('Error Absoluto')
plt.title('Error Absoluto entre las Funciones')
plt.legend()
plt.grid(True)
plt.show()