#pragma once

namespace math {
	float Pi{ 3.14 };

    // Function to find 
    // cross product of two vector array. 
    void crossProduct(int vect_A[], int vect_B[], int cross_P[])

    {

        cross_P[0] = vect_A[1] * vect_B[2] - vect_A[2] * vect_B[1];
        cross_P[1] = vect_A[2] * vect_B[0] - vect_A[0] * vect_B[2];
        cross_P[2] = vect_A[0] * vect_B[1] - vect_A[1] * vect_B[0];
    }
}