#include "test_macros.hpp"

#include <matrix/math.hpp>

using namespace matrix;

int main()
{
    float data[9] = {1, 2, 3,
                     4, 5, 6,
                     7, 8, 10
                    };
    SquareMatrix<float, 3> A(data);
    Vector3<float> diag_check(1, 5, 10);

    TEST(isEqual(A.diag(), diag_check));
    TEST(A.trace() - 16 < FLT_EPSILON);

    float data_check[9] = {
        1.01158503f,  0.02190432f,  0.03238144f,
        0.04349195f,  1.05428524f,  0.06539627f,
        0.07576783f,  0.08708946f,  1.10894048f
    };

    float dt = 0.01f;
    SquareMatrix<float, 3> eA = expm(SquareMatrix<float, 3>(A*dt), 5);
    SquareMatrix<float, 3> eA_check(data_check);
    TEST((eA - eA_check).abs().max() < 1e-3f);

    SquareMatrix<float, 2> A_bottomright = A.slice<2,2>(1,1);
    SquareMatrix<float, 2> A_bottomright2;
    A_bottomright2 = A.slice<2,2>(1,1);

    float data_bottomright[4] = {5, 6,
                                 8, 10
                                };
    SquareMatrix<float, 2> bottomright_check(data_bottomright);
    TEST(isEqual(A_bottomright, bottomright_check));
    TEST(isEqual(A_bottomright2, bottomright_check));


    return 0;
}

/* vim: set et fenc=utf-8 ff=unix sts=0 sw=4 ts=4 : */
