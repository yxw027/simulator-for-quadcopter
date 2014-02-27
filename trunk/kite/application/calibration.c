#define POSITION 12
https://code.google.com/p/picquadcontroller/source/browse/trunk/calibrate.h
enum AXIS {
    AXIS_X = 0,
    AXIS_Y,
    AXIS_Z,
    AXIS_3D,
};

{
    float Y[6][3]; float W[6][4]; float U[4][6]; float V[4][4] = { 0 }; float P[][];
    int i, j, k;

    Y[0][0] = 0; Y[0][1] = 0; Y[0][2] = 1;
    Y[1][0] = 0; Y[1][1] = 0; Y[1][2] = -1;
    Y[2][0] = 0; Y[2][1] = 1; Y[2][2] = 0;
    Y[3][0] = 0; Y[3][1] = -1; Y[3][2] = 0;
    Y[4][0] = 1; Y[4][1] = 0; Y[4][2] = 0;
    Y[5][0] = -1; Y[5][1] = 0; Y[5][2] = 0;

    W[0][0] = ; W[0][1] = ; W[0][2] = ; W[0][3] = 1;
    W[1][0] = ; W[1][1] = ; W[1][2] = ; W[1][3] = 1;
    W[2][0] = ; W[2][1] = ; W[2][2] = ; W[2][3] = 1;
    W[3][0] = ; W[3][1] = ; W[3][2] = ; W[3][3] = 1;
    W[4][0] = ; W[4][1] = ; W[4][2] = ; W[4][3] = 1;
    W[5][0] = ; W[5][1] = ; W[5][2] = ; W[5][3] = 1;

    // U = transpose(W)
    for (i = 0; i < 6; i++)
        for (j = 0; j < 4; j++)
            U[j][i] = W[i][j];
    // V = U * W
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            for (k = 0; k < 6; k++)
                V[i][j] += U[i][k] * W[k][j];

    // P = inverse(V)
    
    //P = V * U
    // X = P * Y
}


void calibration(enum sensor_type type)
{
    int i;

    float samples[6][AXIS_3D];
    //switch (type) {
    // populate W and H matrix
    for (i = 0; i < POSITION; i++) {
        W[i][0] = samples[i].x * samples[i].x;  //x^2
        H[i][0] = samples[i].x;    //x
        H[i][1] = samples[i].y;    //y
        H[i][2] = samples[i].z;    //z
        H[i][3] = -(samples[i].y * samples[i].y);//-y^2
        H[i][4] = -(samples[i].z * samples[i].z);//-z^2
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
