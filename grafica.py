"""Grafica las trayectorias guardadas por sim_csv.c en orbitas.csv."""

import csv
from pathlib import Path

import matplotlib.pyplot as plt


CSV_FILE = Path(__file__).with_name("orbitas.csv")


def cargar_orbitas(path):
    """Devuelve las columnas x/y de cada cuerpo y valida el CSV."""
    if not path.is_file():
        raise FileNotFoundError(
            f"No se encontro {path.name}. Ejecuta primero el simulador sim_csv."
        )

    with path.open("r", newline="", encoding="utf-8") as archivo:
        lector = csv.reader(archivo)
        try:
            encabezado = next(lector)
        except StopIteration as exc:
            raise ValueError(f"{path.name} esta vacio.") from exc

        if len(encabezado) < 2 or len(encabezado) % 2 != 0:
            raise ValueError("El CSV debe contener pares de columnas x,y por cuerpo.")

        columnas = [[] for _ in encabezado]
        for numero_fila, fila in enumerate(lector, start=2):
            if len(fila) != len(encabezado):
                raise ValueError(
                    f"Fila {numero_fila}: se esperaban {len(encabezado)} "
                    f"valores y se encontraron {len(fila)}."
                )
            try:
                valores = [float(valor) for valor in fila]
            except ValueError as exc:
                raise ValueError(
                    f"Fila {numero_fila}: contiene un valor que no es numerico."
                ) from exc

            for columna, valor in zip(columnas, valores):
                columna.append(valor)

    if not columnas[0]:
        raise ValueError(f"{path.name} no contiene datos de simulacion.")

    return columnas


def main():
    columnas = cargar_orbitas(CSV_FILE)

    for indice in range(0, len(columnas), 2):
        plt.plot(
            columnas[indice],
            columnas[indice + 1],
            linewidth=0.7,
            label=f"Cuerpo {indice // 2 + 1}",
        )

    plt.axis("equal")
    plt.title("Sistema gravitacional de N cuerpos")
    plt.xlabel("Posicion X")
    plt.ylabel("Posicion Y")
    plt.grid(alpha=0.2)
    plt.legend()
    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    main()
