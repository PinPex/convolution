#pragma once

#define _USE_MATH_DEFINES

#include <math.h>
class Furie {
public:
    struct complex {
        double R; //Real
        double M; //Mnemonic
    };
    int n;
    complex* mas;

    Furie(int size, double* massive) {
        mas = new complex[size];
        n = size;
        for (int i = 0; i < size; ++i) {
            mas[i].R = massive[i];
            mas[i].M = 0;
        }
    }

    void dis_fur() {
        complex* res = new complex[n];
        double R, M, n1 = n;
        for (int k = 0; k < n; ++k) {
            R = M = 0;
            double cs;
            double sn;

            for (int j = 0; j < n; ++j) {
                double k1 = k, j1 = j, tmp = -2;
                cs = cos(tmp * M_PI * k1 * j1 / n1);
                sn = sin(tmp * M_PI * k1 * j1 / n1);
                R += cs * mas[j].R - sn * mas[j].M;
                M += cs * mas[j].M + sn * mas[j].R;
            }
            res[k].M = M / n1;
            res[k].R = R / n1;
        }
        mas = res;
    }

    void printMas() {
        for (int i = 0; i < n; ++i) {
            std::cout << mas[i].R << " " << mas[i].M << "i " << std::endl;
        }
        std::cout << std::endl;
    }

    void Mul(complex* massive) {
        complex* result = new complex[n];
        for (int i = 0; i < n; ++i) {
            result[i].R = mas[i].R * massive[i].R - mas[i].M * massive[i].M;
            result[i].M = mas[i].R * massive[i].M + mas[i].M * massive[i].R;
        }
        mas = result;
    }

    void back_dis_fur() {
        complex* res = new complex[n];
        double R = 0, M = 0, temp, n1 = n;
        for (int k = 0; k < n; ++k) {
            R = M = temp = 0;
            double cs;
            double sn;

            for (int j = 0; j < n; ++j) {
                double k1 = k, j1 = j, tmp = 2;
                cs = cos(tmp * M_PI * k1 * j1 / n1);
                sn = sin(tmp * M_PI * k1 * j1 / n1);

                R += cs * mas[j].R - sn * mas[j].M;
                M += cs * mas[j].M + sn * mas[j].R;
            }
            res[k].M = M;
            res[k].R = R;
        }
        mas = res;
    }

};