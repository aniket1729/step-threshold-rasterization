#define MODE_CG 1
#define MODE_VIEWER 2
#define MODE_PRINT 3

#define CURRENT_MODE MODE_VIEWER

#if CURRENT_MODE == MODE_CG
    #include <stdio.h>
    #include <conio.h>
    #include <graphics.h>
    #include <stdlib.h>
    // https://graphicsh.online/compiler
#elif CURRENT_MODE == MODE_VIEWER
    #include <iostream>
    #include <cstdlib>
    using namespace std;
#else
    #include <iostream>
    #include <cmath>
    using namespace std;
#endif

#if CURRENT_MODE == MODE_CG
#elif CURRENT_MODE == MODE_VIEWER
    const int WHITE = 0;
    const int YELLOW = 1;
    const int LIGHTGREEN = 2;
#else
    const int WHITE = 0;
    const int YELLOW = 1;
    const int LIGHTGREEN = 2;
#endif
void InitGraphics();
void CloseGraphics();
void PutPixel(int x, int y, int color);
void ShowMessage(const char* msg);


/* Step-Threshold Line Drawing Algorithm */
/* Handles all 8 octants, steep/shallow slopes, and negative directions. */
void drawLineStepThreshold(int x1, int y1, int x2, int y2,
                           int color)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int x = x1;
    int y = y1;

    int twoDx, twoDy, P, i;

    if (x1 == x2 && y1 == y2) {
        PutPixel(x, y, color);
        return;
    }

    /* Shallow line: X is the driving axis */
    if (dx >= dy) {
        twoDy = 2 * dy;
        twoDx = 2 * dx;
        P = twoDy - dx;

        for (i = 0; i <= dx; i++) {
            PutPixel(x, y, color);

            if (P >= 0) {
                y += sy;
                P -= twoDx;
            }
            x += sx;
            P += twoDy;
        }
    }
    /* Steep line: Y is the driving axis */
    else {
        twoDx = 2 * dx;
        twoDy = 2 * dy;
        P = twoDx - dy;

        for (i = 0; i <= dy; i++) {
            PutPixel(x, y, color);

            if (P >= 0) {
                x += sx;
                P -= twoDy;
            }
            y += sy;
            P += twoDx;
        }
    }
}

int main()
{
    InitGraphics();

    ShowMessage("Shallow line (100,100) to (280,120)");
    drawLineStepThreshold(100, 100, 280, 120, WHITE);

    ShowMessage("Steep line (100,100) to (120,200)");
    drawLineStepThreshold(100, 100, 120, 200, YELLOW);

    ShowMessage("Negative slope (100,150) to (150,100)");
    drawLineStepThreshold(100, 150, 150, 100, LIGHTGREEN);

    CloseGraphics();

    return 0;
}


void InitGraphics() {
#if CURRENT_MODE == MODE_CG
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"C:\\TC\\BGI");

#elif CURRENT_MODE == MODE_VIEWER
    cout << "CLEAR\n";
#else
#endif
}

void CloseGraphics() {
#if CURRENT_MODE == MODE_CG
    getch();
    closegraph();

#elif CURRENT_MODE == MODE_VIEWER
    cout << "END\n";

#else
#endif
}

/* Custom callback or render function for plotting a pixel */
void PutPixel(int x, int y, int color) {
#if CURRENT_MODE == MODE_CG
    putpixel(x, y, color);
#elif CURRENT_MODE == MODE_VIEWER
    cout << "P " << x << " " << y << " " << color << '\n';

#else
    cout << "(" << x << ", " << y << ") ";
#endif
}

void ShowMessage(const char* msg) {
#if CURRENT_MODE == MODE_CG
    int x_pos = 20;
    static int y_pos = 20;
    outtextxy(x_pos, y_pos, (char*)msg);
    y_pos += 20;

#elif CURRENT_MODE == MODE_VIEWER
    static int y = 20;
    cout << "T " << y << " " << msg << '\n';
    y += 25;

#else
    cout << "\n\n" << msg << ":\n";
#endif
}
