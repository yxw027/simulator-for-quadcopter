void normalize(double vector[], int size)
{
    int i;
    double mag = 0.0;

    for (i = 0; i < size; i++)
        mag += vector[i] * vector[i];

    mag = sqrt(mag);

    for (i = 0; i < size; i++)
        vector[i] /= mag;
}