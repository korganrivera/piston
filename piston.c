/*  Find compatible shell, o-ring, and piston to make a piston pump.
 *
 *  ---------------------------------So---------------------------------
 *          -------------------------Si-------------------------
 *                -------------------Po-------------------
 *                              ---- Pi-----
 *          gap
 *           |
 *          <-->
 *  |       |     | .    .      |
 *  |       |   (---.---).-----------|
 *  |       |     | .    .      |
 *  h       g   f e d   cb      a
 *                      -------------Ri-------------
 *              ---------------------Ro---------------------
 *
 */

#include <stdio.h>
#define PIPE_MAX 49
#define RING_MAX 31
#define GAP_MAX 0.0003937008 * 50
#define RING_EXPOSURE_MAX 0.55

int main(void){

    // inside diameter, outside diameter, thickness. Inches.
    double pipe[PIPE_MAX][3] = {
        { 0.489,  0.625, 0.068},
        { 0.715,  0.875, 0.080},
        { 0.921,  1.125, 0.102},
        { 0.622,  0.840, 0.109},
        { 0.824,  1.050, 0.113},
        { 1.049,  1.315, 0.133},
        { 0.742,  1.050, 0.154},
        { 0.957,  1.315, 0.179},
        { 0.957,  1.315, 0.179},
        { 1.278,  1.660, 0.191},
        { 1.278,  1.660, 0.191},
        { 1.363,  1.660, 0.140},
        { 1.532,  1.660, 0.064},
        { 0.930,  1.050, 0.060},
        { 1.189,  1.315, 0.063},
        { 1.033,  1.315, 0.133},
        { 0.609,  0.840, 0.109},
        { 0.810,  1.050, 0.113},
        { 0.716,  0.840, 0.062},
        { 0.609,  0.840, 0.109},
        { 1.033,  1.315, 0.133},
        { 1.380,  1.660, 0.140},
        { 1.610,  1.900, 0.145},
        { 2.067,  2.375, 0.154},
        { 3.068,  3.500, 0.216},
        { 4.026,  4.500, 0.237},
        { 6.065,  6.625, 0.280},
        { 0.302,  0.540, 0.119},
        { 0.423,  0.675, 0.126},
        { 0.546,  0.840, 0.147},
        { 1.500,  1.900, 0.200},
        { 1.939,  2.375, 0.218},
        { 2.323,  2.875, 0.276},
        { 2.900,  3.500, 0.300},
        { 3.826,  4.500, 0.337},
        { 4.813,  5.563, 0.375},
        { 5.761,  6.625, 0.432},
        { 7.625,  8.625, 0.500},
        { 9.564, 10.750, 0.593},
        {11.376, 12.750, 0.687},
        {12.500, 14.000, 0.750},
        {14.314, 16.000, 0.843},
        { 5.047,  5.563, 0.258},
        { 7.981,  8.625, 0.322},
        {10.020, 10.750, 0.365},
        {11.938, 12.750, 0.406},
        {13.126, 14.000, 0.437},
        {15.000, 16.000, 0.500},
        { 3.000,  3.250, 0.125}
    };

    // inside diameter, outside diameter, thickness. Inches.
    double ring[RING_MAX][3] = {
        {1.7500, 2.0000, 0.1250},
        {0.5625, 0.7500, 0.0938},
        {2.2500, 2.6250, 0.1875},
        {2.3750, 2.7500, 0.1875},
        {3.1250, 3.5000, 0.1875},
        {3.6250, 3.8750, 0.1250},
        {0.6250, 0.8125, 0.0938},
        {3.7500, 4.0000, 0.1250},
        {3.8750, 4.1250, 0.1250},
        {5.6250, 5.8750, 0.1250},
        {0.6875, 0.8750, 0.0938},
        {0.7500, 0.9375, 0.0938},
        {0.7500, 1.0000, 0.1250},
        {0.8750, 1.0625, 0.0938},
        {0.9375, 1.1875, 0.1250},
        {0.3125, 0.5625, 0.1250},
        {0.5625, 0.6875, 0.0625},
        {0.1875, 0.3125, 0.0625},
        {0.6250, 0.7500, 0.0625},
        {1.6250, 2.0000, 0.1875},
        {0.2188, 0.3438, 0.0625},
        {0.2500, 0.3750, 0.0625},
        {0.0002, 0.4375, 0.2187},
        {0.1250, 0.2500, 0.0625},
        {0.6875, 0.8125, 0.0625},
        {0.3750, 0.5000, 0.0625},
        {0.2500, 0.4375, 0.0938},
        {0.3750, 0.5625, 0.0938},
        {0.3125, 0.5000, 0.0938},
        {0.4375, 0.6250, 0.0938},
        {0.5000, 1.0625, 0.5625}
    };

    double Si, So, St, Pi, Po, Pt, Ri, Ro, Rt, gap;
    double a, b, c, d, e, f, g, h;
    double best_gap, best_exposed_ring;
    double exposed_ring;

    unsigned s, r, p;
    unsigned best_s, best_r, best_p;
    unsigned reason[5] = {0};
    unsigned solutions = 0;

    best_s = PIPE_MAX;
    best_p = PIPE_MAX;
    best_r = RING_MAX;
    best_gap = GAP_MAX;
    best_exposed_ring = RING_EXPOSURE_MAX;

    for(s = 0; s < PIPE_MAX; s++){
        for(r = 0; r < RING_MAX; r++){
            for(p = 0; p < PIPE_MAX; p++){

                Si = pipe[s][0];
                So = pipe[s][1];
                St = pipe[s][2];
                Ri = ring[r][0];
                Ro = ring[r][1];
                Rt = ring[r][2];
                Pi = pipe[p][0];
                Po = pipe[p][1];
                Pt = pipe[p][2];

                a = Pi / 2;
                b = a + Pt / 2;
                c = Ri / 2;
                d = c + Rt / 2;
                e = Po / 2;
                f = Ro / 2;
                g = Si / 2;
                h = So / 2;

                gap = g - f;

                // ring must be below piston surface but no deeper than halfway.
                // e > c >= b
                if(e <= c) {
                    reason[0]++;
                    continue;
                }

                if(c < b){
                    reason[1]++;
                    continue;
                }

                // At most, RING_EXPOSURE_MAX % of ring can be outside of piston.
                exposed_ring = (f - e) / Rt;
                if(exposed_ring > RING_EXPOSURE_MAX){
                    reason[2]++;
                    continue;
                }

                // 0 <= gap <= 0.0003937008
                if(gap > GAP_MAX){
                    reason[3]++;
                    continue;
                }

                // make sure ring isn't bigger than inside of shell.
                if(gap < 0){
                    reason[4]++;
                    continue;
                }

                printf("shell:%u ring:%u piston:%u gap:%.5f ringexp:%.3f\n", s, r, p, gap, exposed_ring);
                solutions++;

                if(gap < best_gap){
                    best_gap = gap;
                    best_s = s;
                    best_r = r;
                    best_p = p;
                    best_exposed_ring = exposed_ring;
                }
            }
        }
    }
    printf("ring too big for piston: %u\n", reason[0]);
    printf("ring too deep in piston: %u\n", reason[1]);
    printf("ring not buried enough: %u\n", reason[2]);
    printf("gap too wide: %u\n", reason[3]);
    printf("ring too big for shell: %u\n", reason[4]);
    printf("solutions found: %u\n", solutions);

    printf("best solution:\n\ts:%u\n\tr:%u\n\tp:%u\n\tgap:%.5f in. (%.5f mm)\n\tring_exp:%.5f\n", best_s, best_r, best_p, best_gap, best_gap * 25.4, best_exposed_ring);
}
