#include "raylib.h"
#include <math.h>

#define N         3
#define G         1.0
#define DT        0.0005
#define SUBPASOS  40      // pasos de física por frame
#define ESTELA    700     // puntos de rastro
#define SUAV      0.000001

typedef struct { double x, y, vx, vy, m; } Cuerpo;

static const Cuerpo INICIAL[N] = {
    {  0.97000436, -0.24308753,  0.46620368,  0.43236573, 1.0 },
    { -0.97000436,  0.24308753,  0.46620368,  0.43236573, 1.0 },
    {  0.0,         0.0,        -0.93240737, -0.86473146, 1.0 },
};

int main(void) {
    const int W = 1000, H = 800;
    InitWindow(W, H, "N-Cuerpos");
    SetTargetFPS(60);

    Color paleta[8] = { GOLD, SKYBLUE, LIME, ORANGE, PINK, VIOLET, RED, GREEN };
    Cuerpo c[N];
    Vector2 estela[N][ESTELA];
    int guardados = 0, cabeza = 0;
    float zoom = 300.0f;
    int pausa = 0;

    for (int i = 0; i < N; i++) c[i] = INICIAL[i];

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_SPACE)) pausa = !pausa;
        if (IsKeyPressed(KEY_R)) {
            for (int i = 0; i < N; i++) c[i] = INICIAL[i];
            guardados = 0; cabeza = 0;
        }
        zoom *= 1.0f + GetMouseWheelMove() * 0.1f;
        if (zoom < 5.0f) zoom = 5.0f;

        if (!pausa) {
            for (int s = 0; s < SUBPASOS; s++) {
                double ax[N] = {0}, ay[N] = {0};
                for (int i = 0; i < N; i++)
                    for (int j = 0; j < N; j++) {
                        if (i == j) continue;
                        double dx = c[j].x - c[i].x;
                        double dy = c[j].y - c[i].y;
                        double r2 = dx*dx + dy*dy + SUAV;
                        double r  = sqrt(r2);
                        double a  = G * c[j].m / r2;
                        ax[i] += a * dx / r;
                        ay[i] += a * dy / r;
                    }
                for (int i = 0; i < N; i++) {
                    c[i].vx += ax[i] * DT;
                    c[i].vy += ay[i] * DT;
                    c[i].x  += c[i].vx * DT;
                    c[i].y  += c[i].vy * DT;
                }
            }
            for (int i = 0; i < N; i++)
                estela[i][cabeza] = (Vector2){ (float)c[i].x, (float)c[i].y };
            cabeza = (cabeza + 1) % ESTELA;
            if (guardados < ESTELA) guardados++;
        }

        BeginDrawing();
        ClearBackground((Color){ 8, 8, 20, 255 });

        for (int i = 0; i < N; i++) {
            for (int k = 0; k < guardados - 1; k++) {
                int a = (cabeza - guardados + k + ESTELA) % ESTELA;
                int b = (a + 1) % ESTELA;
                Vector2 p = { W/2.0f + estela[i][a].x*zoom, H/2.0f - estela[i][a].y*zoom };
                Vector2 q = { W/2.0f + estela[i][b].x*zoom, H/2.0f - estela[i][b].y*zoom };
                float alfa = (float)k / (float)guardados;
                DrawLineEx(p, q, 1.5f, Fade(paleta[i % 8], alfa * 0.8f));
            }
        }

        for (int i = 0; i < N; i++) {
            Vector2 p = { W/2.0f + (float)c[i].x*zoom, H/2.0f - (float)c[i].y*zoom };
            float radio = 4.0f + 2.0f * (float)log10(1.0 + c[i].m);
            DrawCircleV(p, radio * 2.5f, Fade(paleta[i % 8], 0.15f));
            DrawCircleV(p, radio, paleta[i % 8]);
        }

        DrawText("ESPACIO: pausa   R: reiniciar   RUEDA: zoom", 12, 12, 18, RAYWHITE);
        DrawFPS(W - 90, 12);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}