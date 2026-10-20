#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;

// Mock plot function for visualization
void PutPixel(int x, int y) {
    //printf("(%d, %.0f) ", x, y);
    printf("(%d, %d)  ", x, y);
}

// ==================================================
// 1. FLOATING POINT PROTOTYPES (StepThreshold 1 & 2)
// ==================================================

// Basic floating-point step approach for shallow lines
void drawLine_UnitStep1_naiveFloat_shallow(int x1, int y1, int x2, int y2) {
    int dx = (x2 - x1);  // Difference in x-coordinates
    int dy = (y2 - y1);  // Difference in y-coordinates
    int sx = 1;
    int sy = 1;

    float xpery, yperx;     // calculate increment limitfloat xlimit, ylimit;
    float xlimit, ylimit;
    int x = x1;
    int y = y1;

    printf("\n drawLine_UnitStep1_naiveFloat_shallow: \n");

	xpery = (float)abs(dx)/abs(dy)*sx;
	xlimit = x1 + xpery/2*sx;     // Initial threshold
	//printf("%f %f", xpery, xlimit);

	while (1) {
			//printf("(%d %d)%f ", x, y, xlimit);
			PutPixel(x, y);

			if (x == x2)    break;


			//next (x,y)
			x += sx;
			if (x <= (int)xlimit) {
					y = y;
			} else {
					y += sy;

					xlimit += xpery*sx;     //update xlimit
			}

	}
}

// Basic floating-point step approach for any case lines
void drawLine_UnitStep1_naiveFloat_octants(int x1, int y1, int x2, int y2) {
    int dx = (x2 - x1);  // Difference in x-coordinates
    int dy = (y2 - y1);  // Difference in y-coordinates
    int sx = (x1 < x2) ? 1 : -1;  // Step direction for x (left or right)
    int sy = (y1 < y2) ? 1 : -1;  // Step direction for y (up or down)

    float xpery, yperx;     // calculate increment limitfloat xlimit, ylimit;
    float xlimit, ylimit;
    int x = x1;
    int y = y1;

    printf("\n drawLine_UnitStep1_naiveFloat_octants: \n");

    // If the line is shallow (dx > dy)
    if (abs(dx) > abs(dy)) {
        xpery = abs(dx)/abs(dy)*sx;
        xlimit = x1 + xpery/2*sx;

        while (1) {
            PutPixel(x, y);

            if (x == x2)    break;

            x += sx;
            if (x <= floor(xlimit)) {
            } else {
                y += sy;

                xlimit += xpery*sx;     //update xlimit
            }
        }
    }
    // If the line is steep (dy > dx)
    else {
        yperx = abs(dy)/abs(dx)*sy;
        ylimit = y1 + yperx/2*sy;

        while (1) {
            PutPixel(x, y);

            if (y == y2)    break;

            y += sy;
            if (y <= floor(ylimit)) {
            } else {
                x += sx;

                ylimit += yperx*sy;     //update ylimit
            }
        }
    }
}


// drawLine_UnitStep2_Float_shallow() is similar previous drawLine_UnitStep1_naiveFloat_shallow(), and using float arithmetic.
// updated Basic floating-point step approach for shallow lines
void drawLine_UnitStep2_Float_shallow(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
	
	printf("\n drawLine_UnitStep2_Float_shallow: \n");

    // Safety check for vertical lines (dy = 0)
    if (dy == 0) {
        printf("Error: dy is zero, slope 's' is undefined.\n");
        return;
    }

    float s = dx / dy;          // Inverse slope
    float xs = x1 + (s / 2.0);  // Initial threshold

    float y = y1;

    // Integer x moves from x1 to x2 (inclusive)
    for (int x = (int)x1; x <= (int)x2; ) {

        // 2.1 Print current coordinates
        PutPixel(x, y);

        // 2.2 x++ is handled by the for-loop increment

        // 2.3 & 2.4 Logic
        // Note: Based on your step 2.4, if x hits the threshold,
        // y increments and the threshold shifts.
        x++;
        if (x > xs) {
            y++;
            xs = xs + s; // Update threshold for the next y-level
        }
    }
}

// drawLine_UnitStep2_Float_shallow_VER2() is another version of drawLine_UnitStep2_Float_shallow() using condition (x > xs) and (x >= xs) respectively.
// updated version2 Basic floating-point step approach for shallow lines
void drawLine_UnitStep2_Float_shallow_VER2(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
	
	printf("\n drawLine_UnitStep2_Float_shallow_VER2: \n");

    // Safety check for vertical lines (dy = 0)
    if (dy == 0) {
        printf("Error: dy is zero, slope 's' is undefined.\n");
        return;
    }

    float s = dx / dy;          // Inverse slope
    float xs = x1 + (s / 2.0);  // Initial threshold

    float y = y1;

    // Integer x moves from x1 to x2 (inclusive)
    for (int x = (int)x1; x <= (int)x2; x++) {

        // 2.1 Print current coordinates
        PutPixel(x, y);

        // 2.2 x++ is handled by the for-loop increment

        // 2.3 & 2.4 Logic
        // Note: Based on your step 2.4, if x hits the threshold,
        // y increments and the threshold shifts.
        if (x >= xs) {
            y++;
            xs = xs + s; // Update threshold for the next y-level
        }
    }
}


// =====================================================
// 2. INTEGER OPTIMIZED PROTOTYPES (StepThreshold 3 & 4)
// =====================================================
// drawLine_UnitStep3_Integer_shallow() is similar to that of drawLine_UnitStep2_Float_shallow(), but using Integer arithmetic to reduce computation.
// Pure integer basic case implementation
void drawLine_UnitStep3_Integer_shallow(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;

    int y = y1;

    // This 'rem' (remainder) replaces the floating point 'xs'
    // We multiply the fractional part (s/2) by 2*dy to keep it as an integer
    // Initial threshold offset (s/2 * 2dy) = dx
    int threshold = dx;

    // Cumulative distance moved in x, scaled by 2*dy
    int cumulative_x = 0;
	
	printf("\n drawLine_UnitStep3_Integer_shallow: \n");

    for (int x = x1; x <= x2; ) {
        PutPixel(x, y);

        x++;

        // Logical check: has 2*dy * (distance moved) crossed the threshold?
        // This is equivalent to your: if (x > xs)
        cumulative_x += 2 * dy;

        if (cumulative_x > threshold) {
            y++;
            threshold += 2 * dx; // Equivalent to: xs = xs + s
        }
    }
}

// drawLine_UnitStep3_Integer_octants() is a general function from drawLine_UnitStep3_Integer_shallow() of initial example case.
// Pure integer any case implementation
void drawLine_UnitStep3_Integer_octants(int x1, int y1, int x2, int y2) {

	printf("\n drawLine_UnitStep3_Integer_octants: \n");

// 1. Handle the "Single Point" case explicitly
    if (x1 == x2 && y1 == y2) { PutPixel(x1, y1);  return; }

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    // Determine the direction of the steps
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int x = x1;
    int y = y1;


    // We check which axis is longer to decide our "driving" logic
    if (dx >= dy) {
        // --- SHALLOW LINE (Driving axis is X) ---
        int threshold = dx;
        int cumulative = 0;

        for (int i = 0; i <= dx; i++) {
            PutPixel(x, y);

            x += sx;
            cumulative += 2 * dy;

            if (cumulative > threshold) {
                y += sy;
                threshold += 2 * dx;
            }
        }
    } else {
        // --- STEEP LINE (Driving axis is Y) ---
        // We flip the logic: y moves every step, x moves on threshold
        int threshold = dy;
        int cumulative = 0;

        for (int i = 0; i <= dy; i++) {
            PutPixel(x, y);

            y += sy;
            cumulative += 2 * dx;

            if (cumulative > threshold) {
                x += sx;
                threshold += 2 * dy;
            }
        }
    }
}





// drawLine_UnitStep4_advInteger_shallow() is written later based on and similar to drawLine_UnitStep3_Integer_shallow()
// final Pure integer basic case implementation
void drawLine_UnitStep4_advInteger_shallow(int x1, int y1, int x2, int y2) {

	printf("\n drawLine_UnitStep4_advInteger_shallow: \n");

    if (x1 == x2 && y1 == y2) { PutPixel(x1, y1); return; }

    int dx = x2 - x1;
    int dy = y2 - y1;

    // Initial decision variable P
    // Derived from the 0.5 offset: P = 2*dy*(x - x1) - dx
    // At the start, x = x1, so P = -dx
    int P = -dx;

    int y = y1;
    int twoDy = 2 * dy;
    int twoDx = 2 * dx;

    for (int x = x1; x <= x2; x++) {
        PutPixel(x, y);

        // Instead of x >= xs, we check the integer decision variable
        if (P >= 0) {
            y++;
            P -= twoDx; // Adjust threshold for the new y
        }

        P += twoDy; // Equivalent to the horizontal step (x++)
    }
}

// final Pure integer any case implementation
// void drawLine_UnitStep4_advInteger_octants(int x1, int y1, int x2, int y2)
// = void drawLineStepThreshold(int x1, int y1, int x2, int y2)

int main() {
    printf("Evolutionary Step-Threshold Prototypes Loaded Successfully.\n");

    drawLine_UnitStep1_naiveFloat_shallow(0, 0, 100, 100);
    drawLine_UnitStep1_naiveFloat_octants(0, 0, 100, 100);
    drawLine_UnitStep2_Float_shallow(0, 0, 100, 100);
    drawLine_UnitStep2_Float_shallow_VER2(0, 0, 100, 100);
    drawLine_UnitStep3_Integer_shallow(0, 0, 100, 100);
    drawLine_UnitStep3_Integer_octants(0, 0, 100, 100);
    drawLine_UnitStep4_advInteger_shallow(0, 0, 100, 100);
    return 0;
}
