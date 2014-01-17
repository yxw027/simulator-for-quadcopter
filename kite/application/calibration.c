#define POSITION 12
https://code.google.com/p/picquadcontroller/source/browse/trunk/calibrate.h
enum AXIS {
    AXIS_X = 0,
    AXIS_Y,
    AXIS_Z,
    AXIS_3D,
};

void calibration(enum sensor_type type)
{
    int i;

    float samples[6][AXIS_3D];
    //switch (type) {
    for (i = 0; i < POSITION; i++) {
        W[i][0] = x^2;  //x^2
        H[i][0] = x;    //x
        H[i][1] = y;    //y
        H[i][2] = z;    //z
        H[i][3] = -y * y;//-y^2
        H[i][4] = -z * z;//-z^2
        H[i][5] = 1;    //1
    }
    Ht;
    HtH = Ht * H;
    HtHi = HtH.inverse(); //6x6
    X[6][1];

    float offset[3], scalar[3], acc[3], samples[6][6];
    /* offset */
    offset[0] = X[0][0] / 2;
    offset[1] = X[1][0] / 2 / X[3][0];
    offset[2] = X[2][0] / 2 / X[4][0];
    /* scale factor */
    scalar[0] = sqrt(X[5] + offset[0]*offset[0] + X[3]*offset[1]*offset[1] + X[4]*offset[2]*offset[2]);
    scalar[1] = sqrt(scalar[0] / sqrt(X[3][0]));
    scalar[2] = sqrt(scalar[0] / sqrt(X[4][0]));

    //calculate calibration variance
    float variance = 0;
    for (i = 0; i < POSITON; i++) {
        acc[0] = samples[i][0] - offset[0] / scalar[0];
        acc[1] = samples[i][1] - offset[1] / scalar[1];
        acc[2] = samples[i][2] - offset[2] / scalar[2];

        variance += fabs(sqrt(acc[0]*acc[0]+acc[1]*acc[1]+acc[2]*acc[2]) - 1);
    }
    variance = 100.00f * error / POSITION;
    printf("calibration result:");
    if (variance < MAX_CAL_variance) {
        printf();
        save_config();
    } else {
        printf("calibration failed\n");
    }
    }
}
