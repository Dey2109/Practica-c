#include <stdio.h>
#include <math.h>

#define N      3
#define G      1.0
#define DT     0.001
#define PASOS  13000
#define SUAV   0.05     // softening: evita divisiones por cero

typedef struct {
    double x, y, vx, vy, m;
} Cuerpo;

int main(void) {
#define N 3
#define DT 0.001
#define PASOS 13000
Cuerpo c[N] = {
    {  0.97000436, -0.24308753,  0.46620368,  0.43236573, 1.0 },
    { -0.97000436,  0.24308753,  0.46620368,  0.43236573, 1.0 },
    {  0.0,         0.0,        -0.93240737, -0.86473146, 1.0 },
};

    FILE *f = fopen("orbitas.csv", "w");
    for (int i = 0; i < N; i++)
        fprintf(f, "x%d,y%d%s", i, i, (i == N-1) ? "\n" : ",");

    for (int paso = 0; paso < PASOS; paso++) {
        double ax[N] = {0}, ay[N] = {0};

        // 1) calcular TODAS las aceleraciones
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (i == j) continue;
                double dx = c[j].x - c[i].x;
                double dy = c[j].y - c[i].y;
                double r2 = dx*dx + dy*dy + SUAV*SUAV;
                double r  = sqrt(r2);
                double a  = G * c[j].m / r2;
                ax[i] += a * dx / r;
                ay[i] += a * dy / r;
            }
        }

        // 2) DESPUÉS mover todos
        for (int i = 0; i < N; i++) {
            c[i].vx += ax[i] * DT;
            c[i].vy += ay[i] * DT;
            c[i].x  += c[i].vx * DT;
            c[i].y  += c[i].vy * DT;
            fprintf(f, "%.6f,%.6f%s", c[i].x, c[i].y, (i == N-1) ? "\n" : ",");
        }

        if (paso % 2000 == 0) printf("paso %d / %d\n", paso, PASOS);
    }

    fclose(f);
    printf("Listo! orbitas.csv\n");
    return 0;
}