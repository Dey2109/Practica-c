# ORRERY PRIME

Simulador interactivo de un sistema gravitacional de **N cuerpos**, con una interfaz visual en HTML, CSS y JavaScript. El proyecto también incluye una versión nativa en C basada en raylib y una herramienta para generar y graficar trayectorias mediante CSV.

> Proyecto educativo y experimental. La simulación utiliza unidades y parámetros simplificados; no pretende ser una efeméride astronómica de precisión.

## Características

- Simulación gravitacional de varios cuerpos en 2D.
- Creación, selección, edición y eliminación de cuerpos.
- Controles de masa, velocidad, paso temporal y suavizado gravitatorio.
- Integradores y modos de colisión configurables desde la interfaz.
- Cámara, zoom, seguimiento, cuadrícula y visualización del campo gravitatorio.
- Personalización visual: paletas, estelas, brillo y etiquetas.
- Presets de sistemas y herramientas para guardar/cargar configuraciones.
- Exportación de imágenes y datos desde la interfaz.

## Estructura

| Archivo | Descripción |
| --- | --- |
| `index.html` | Aplicación web principal. Incluye HTML, CSS y JavaScript en un solo archivo. |
| `main.c` | Versión nativa interactiva en C usando raylib. |
| `sim_csv.c` | Simulador en C que calcula trayectorias y las guarda en `orbitas.csv`. |
| `grafica.py` | Lee `orbitas.csv` y dibuja las trayectorias con Matplotlib. |
| `orbitas.csv` | Datos de trayectorias de tres cuerpos. |
| `orbita.csv` | Datos CSV de una trayectoria individual de ejemplo. |

## Requisitos

### Aplicación web

- Navegador moderno con soporte para Canvas 2D.
- Conexión a Internet para cargar las fuentes de Google Fonts. Sin conexión, se utilizarán fuentes alternativas del sistema.

No requiere instalación de dependencias. Abre `index.html` directamente en el navegador. También puedes servir la carpeta con un servidor local, por ejemplo:

```bash
python -m http.server 8000
```

Después visita `http://localhost:8000`.

### Simulador CSV y gráfica

- Compilador C compatible con C99 (GCC o Clang).
- Python 3.9 o posterior.
- Matplotlib.

Instala Matplotlib:

```bash
python -m pip install matplotlib
```

Compila el simulador:

```bash
gcc -std=c99 -O2 sim_csv.c -o sim_csv -lm
```

En Windows con MinGW-w64:

```bash
gcc -std=c99 -O2 sim_csv.c -o sim_csv.exe -lm
```

Ejecuta el programa desde la carpeta del proyecto:

```bash
./sim_csv
```

En Windows:

```powershell
.\sim_csv.exe
```

El programa genera o sobrescribe `orbitas.csv` en el directorio de trabajo. Luego grafica los resultados:

```bash
python grafica.py
```

**Importante:** ejecuta `sim_csv` antes de `grafica.py` si quieres generar un conjunto nuevo de datos. El CSV debe conservar una fila por instante y dos columnas (`x`, `y`) por cuerpo.

### Aplicación nativa con raylib

`main.c` necesita tener instalada la biblioteca [raylib](https://www.raylib.com/) y un compilador C configurado. La compilación depende de cómo hayas instalado raylib y de tu sistema operativo.

Con GCC y una instalación de raylib correctamente configurada, el comando suele tener esta forma:

```bash
gcc -std=c99 -O2 main.c -o nbody -lraylib -lopengl32 -lgdi32 -lwinmm
```

En otros sistemas, consulta las instrucciones de compilación de raylib para las bibliotecas del sistema correspondientes.

## Controles de la versión nativa

- `ESPACIO`: pausar o reanudar.
- `R`: reiniciar la simulación.
- Rueda del ratón: acercar o alejar la vista.
- Cerrar la ventana: salir.

## Notas técnicas

- La simulación web y los programas en C son implementaciones independientes; sus parámetros y resultados no tienen por qué coincidir exactamente.
- `sim_csv.c` escribe una fila completa por paso de simulación, con las coordenadas de todos los cuerpos.
- `grafica.py` comprueba que el CSV exista y que cada fila tenga la cantidad esperada de valores antes de graficar.
- El suavizado gravitatorio evita que la aceleración crezca sin límite cuando dos cuerpos se aproximan demasiado.

## Solución de problemas

**`matplotlib` no está instalado**

```bash
python -m pip install matplotlib
```

**No se encuentra `orbitas.csv`**

Ejecuta primero `sim_csv` desde la carpeta del proyecto.

**El compilador no encuentra `raylib.h`**

Instala raylib y configura las rutas de inclusión y enlazado para tu compilador. La versión web no necesita raylib.

**La página no carga las tipografías**

Comprueba tu conexión a Internet. La aplicación seguirá funcionando con fuentes de respaldo.

## Licencia

No se ha especificado una licencia en este repositorio. Si deseas permitir que otras personas reutilicen, modifiquen o distribuyan el proyecto, añade un archivo `LICENSE` con la licencia que elijas.
