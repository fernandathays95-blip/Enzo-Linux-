/*
 * 3d_ui_logic.c
 *
 * Pequena engine 3D ASCII:
 * - Desenha um cubo rotacionando
 * - Aceita controles W/A/S/D para mover o cubo (simula toques/drag)
 * - Q para sair
 *
 * Compilação (Termux / Linux):
 *   clang 3d_ui_logic.c -o 3d_ui_logic -lm
 * ou
 *   gcc 3d_ui_logic.c -o 3d_ui_logic -lm
 *
 * Execução:
 *   ./3d_ui_logic
 *
 * Observações:
 * - Usa terminal em modo raw (termios) para leitura sem bloquear.
 * - Deve rodar em terminais que suportem ANSI escape codes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <termios.h>
#include <fcntl.h>
#include <time.h>

#define SCREEN_W 80
#define SCREEN_H 30
#define FPS_USEC 40000   // ~25 FPS

/* terminal raw mode helpers */
static struct termios orig_termios;

void disable_raw_mode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enable_raw_mode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disable_raw_mode);

    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON); // no echo, no canonical
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

/* non-blocking keyboard check */
int kbhit() {
    struct timeval tv = { 0L, 0L };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(STDIN_FILENO+1, &fds, NULL, NULL, &tv) > 0;
}

int readch() {
    char c = 0;
    if (read(STDIN_FILENO, &c, 1) == 1) return (int)c;
    return -1;
}

/* 3D math simple structs */
typedef struct { double x, y, z; } v3;
typedef struct { int x, y; } v2;

/* cube vertices */
v3 cube_vertices[8] = {
    {-1, -1, -1},
    { 1, -1, -1},
    { 1,  1, -1},
    {-1,  1, -1},
    {-1, -1,  1},
    { 1, -1,  1},
    { 1,  1,  1},
    {-1,  1,  1},
};

/* cube edges (pairs of vertex indices) */
int cube_edges[][2] = {
    {0,1},{1,2},{2,3},{3,0}, // back face
    {4,5},{5,6},{6,7},{7,4}, // front face
    {0,4},{1,5},{2,6},{3,7}  // connections
};

/* projection parameters */
double cam_dist = 5.0;
double scale = 10.0;

/* screen buffer */
char screen[SCREEN_H][SCREEN_W+1];

/* clear buffer */
void clear_screen_buf() {
    for (int y=0;y<SCREEN_H;y++){
        for (int x=0;x<SCREEN_W;x++) screen[y][x] = ' ';
        screen[y][SCREEN_W] = '\0';
    }
}

/* set char if inside bounds */
void put_char(int x, int y, char c) {
    if (x>=0 && x<SCREEN_W && y>=0 && y<SCREEN_H) screen[y][x] = c;
}

/* simple line drawing (Bresenham) */
void draw_line(int x0, int y0, int x1, int y1, char c) {
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;
    while (1) {
        put_char(x0, y0, c);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

/* rotate point by angles */
v3 rotate_point(v3 p, double ax, double ay, double az) {
    double cx = cos(ax), sx = sin(ax);
    double cy = cos(ay), sy = sin(ay);
    double cz = cos(az), sz = sin(az);
    v3 r = p;
    // rotate X
    double y1 = r.y * cx - r.z * sx;
    double z1 = r.y * sx + r.z * cx;
    r.y = y1; r.z = z1;
    // rotate Y
    double x2 = r.x * cy + r.z * -sy;
    double z2 = r.x * sy + r.z * cy;
    r.x = x2; r.z = z2;
    // rotate Z
    double x3 = r.x * cz - r.y * sz;
    double y3 = r.x * sz + r.y * cz;
    r.x = x3; r.y = y3;
    return r;
}

/* project 3D point to 2D screen */
v2 project(v3 p) {
    v2 out;
    double z = p.z + cam_dist;
    if (z == 0) z = 0.0001;
    double px = (p.x / z) * scale + (SCREEN_W / 2);
    double py = (p.y / z) * scale + (SCREEN_H / 2);
    out.x = (int)round(px);
    out.y = (int)round(py);
    return out;
}

/* draw cube with rotation and translation */
void draw_cube(double ax, double ay, double az, v3 trans) {
    v2 proj[8];
    for (int i=0;i<8;i++){
        v3 p = cube_vertices[i];
        // scale cube slightly
        p.x *= 1.0; p.y *= 0.6; p.z *= 1.0;
        // rotate
        v3 r = rotate_point(p, ax, ay, az);
        // translate
        r.x += trans.x; r.y += trans.y; r.z += trans.z;
        proj[i] = project(r);
    }
    // draw edges
    for (int e=0;e<12;e++){
        int a = cube_edges[e][0];
        int b = cube_edges[e][1];
        draw_line(proj[a].x, proj[a].y, proj[b].x, proj[b].y, '#');
    }
    // draw vertices
    for (int i=0;i<8;i++){
        put_char(proj[i].x, proj[i].y, 'o');
    }
}

/* print buffer to terminal */
void render() {
    // move cursor to top-left
    printf("\033[H");
    for (int y=0;y<SCREEN_H;y++){
        printf("%s\n", screen[y]);
    }
    fflush(stdout);
}

/* main loop */
int main() {
    enable_raw_mode();

    // Hide cursor
    printf("\033[?25l");
    // Clear screen and position
    printf("\033[2J\033[H");

    double ax=0.0, ay=0.0, az=0.0;
    v3 trans = {0.0, 0.0, 0.0};

    // instructions
    printf("Enzo Linux 3D UI — ASCII Demo\n");
    printf("Controles: W/S Up/Down | A/D Left/Right | Z/X depth | Q sair\n");
    printf("Pressione qualquer tecla para começar...\n");
    // wait for key
    while(!kbhit()) usleep(100000);
    (void) readch();

    struct timespec prev, curr;
    clock_gettime(CLOCK_MONOTONIC, &prev);

    int running = 1;
    while (running) {
        // timing
        clock_gettime(CLOCK_MONOTONIC, &curr);
        long elapsed_us = (curr.tv_sec - prev.tv_sec) * 1000000L + (curr.tv_nsec - prev.tv_nsec) / 1000L;
        if (elapsed_us < FPS_USEC) {
            usleep(FPS_USEC - elapsed_us);
            clock_gettime(CLOCK_MONOTONIC, &curr);
        }
        prev = curr;

        // input handling (non-blocking)
        while (kbhit()) {
            int c = readch();
            if (c == -1) break;
            if (c == 'q' || c == 'Q') { running = 0; break; }
            if (c == 'w' || c == 'W') trans.y -= 0.1;
            if (c == 's' || c == 'S') trans.y += 0.1;
            if (c == 'a' || c == 'A') trans.x -= 0.1;
            if (c == 'd' || c == 'D') trans.x += 0.1;
            if (c == 'z' || c == 'Z') trans.z += 0.2;
            if (c == 'x' || c == 'X') trans.z -= 0.2;
            // arrow keys support (escape sequences)
            if (c == 27) { // ESC
                // try to read two more bytes
                int c1 = readch();
                int c2 = readch();
                if (c1 == 91) {
                    if (c2 == 65) { // up
                        trans.y -= 0.1;
                    } else if (c2 == 66) { // down
                        trans.y += 0.1;
                    } else if (c2 == 67) { // right
                        trans.x += 0.1;
                    } else if (c2 == 68) { // left
                        trans.x -= 0.1;
                    }
                }
            }
        }

        // update rotation
        ax += 0.03;
        ay += 0.02;
        az += 0.015;

        // prepare buffer
        clear_screen_buf();
        // draw cube
        draw_cube(ax, ay, az, trans);

        // HUD (top)
        char hud[SCREEN_W+1];
        snprintf(hud, sizeof(hud), "Enzo 3D UI — pos:(%.2f,%.2f,%.2f)  rot:(%.2f,%.2f,%.2f)  (Q to quit)",
                 trans.x, trans.y, trans.z, ax, ay, az);
        for (int i=0;i<SCREEN_W && hud[i];i++) {
            put_char(i, 0, hud[i]);
        }

        // render
        render();
    }

    // restore terminal
    disable_raw_mode();
    // show cursor
    printf("\033[?25h");
    // move cursor after screen
    printf("\033[%d;1H", SCREEN_H + 3);
    printf("3D UI demo finalizado. Saindo...\n");
    return 0;
}
