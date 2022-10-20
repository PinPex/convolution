#pragma once

#define _USE_MATH_DEFINES

#include <math.h>
using namespace std;
class Furie {
public:

    class complex {
    public:
        double real;
        double im;
        complex() {
            this->real = 0;
            this->im = 0;
        }
        complex(double real, double im) : real(real), im(im) {

        }
        complex operator + (complex c2) {
            return complex(this->real + c2.real, this->im + c2.im);
        }
        complex operator * (complex c2) {
            complex result;
            result.real = this->real * c2.real - this->im * c2.im;
            result.im = this->real * c2.im + this->im * c2.real;
            return result;
        }
        complex operator - (complex c2) {
            return complex(this->real - c2.real, this->im - c2.im);
        }
        void operator = (complex c2) {
            this->real = c2.real;
            this->im = c2.im;
        }
        void operator += (complex c2) {
            this->real += c2.real;
            this->im += c2.im;
        }
        void operator /= (double n) {
            this->real /= n;
            this->im /= n;
        }
        void print() {
            printf("%f", this->real);
            if (this->im >= 0) printf(" + ");
            else printf(" - ");
            printf("%fi\n", abs(this->im));
        }
    };

    int count_operations = 0;

    complex exp(complex z) {
        complex result;
        result.real = std::exp(z.real) * cos(z.im);
        result.im = std::exp(z.real) * sin(z.im);
        return result;
    }

    void DFT() {
        complex* output = new complex[n];
        for (int k = 0; k < n; k++) {//(x+iy)*(cos-i*sin); re=x*cos+y*sin; im=-x*sin+y*cos
            output[k].real = output[k].im = 0;
            for (int i = 0; i < n; i++) {
                complex tmp;
                tmp.im = -2 * M_PI * k * i / n;
                output[k] += exp(tmp) * mas[i];
                count_operations += 5;
            }
            output[k] /= n;
        }
        mas = output;
    }

    void reverse_DFT() {
        complex* output = new complex[n];
        for (int k = 0; k < n; k++) {//(x+iy)*(cos+i*sin); re=x*cos-y*sin; im=x*sin+y*cos
            output[k].real = output[k].im = 0;
            for (int i = 0; i < n; i++) {
                complex tmp;
                tmp.im = 2 * M_PI * k * i / n;
                output[k] += exp(tmp) * mas[i];
                count_operations += 5;
            }
        }
        mas = output;
    }

    void half_fast_furie() {
        int p1, p2;

        for (p1 = (int)floor(sqrt(n)); p1 > 0; p1--) {
            p2 = n / p1;
            if (p1 * p2 == n) break;
        }

        complex* A1 = new complex[n];
        complex* A2 = new complex[n];

        for (int j2 = 0; j2 < p2; j2++) {
            for (int k1 = 0; k1 < p1; k1++) {
                int n1 = k1 + p1 * j2;
                for (int j1 = 0; j1 < p1; j1++) {
                    complex tmp;
                    complex exp_;
                    tmp.im = -2 * M_PI * j1 * k1 / p1;
                    exp_.real = std::exp(tmp.real) * cos(tmp.im);
                    exp_.im = std::exp(tmp.real) * sin(tmp.im);

                    A1[n1] += mas[j2 + p2 * j1] * exp_;
                    count_operations += 5;

                }
                A1[n1] /= p1;
            }
        }

        for (int k2 = 0; k2 < p2; k2++) {
            for (int k1 = 0; k1 < p1; k1++) {
                int n1 = k1 + p1 * k2;
                for (int j2 = 0; j2 < p2; j2++) {
                    complex tmp;
                    complex exp_;
                    tmp.im = -2 * M_PI * (j2 * (k1 + p1 * k2)) / n;
                    exp_.real = std::exp(tmp.real) * cos(tmp.im);
                    exp_.im = std::exp(tmp.real) * sin(tmp.im);

                    A2[n1] += A1[k1 + p1 * j2] * exp_;
                    count_operations += 5;
                }
                A2[n1] /= p2;
            }
        }
        delete[] A1;
        mas = A2;
        count_operations = 5 * 3 * n * log2f(n);
    }

    void reverse_half_fast_furie() {
        int p1, p2;
        for (p1 = (int)floor(sqrt(n)); p1 > 0; p1--) {
            p2 = n / p1;
            if (p1 * p2 == n) break;
        }
        complex* A1 = new complex[n];
        complex* A2 = new complex[n];

        for (int j2 = 0; j2 < p2; j2++) {
            for (int k1 = 0; k1 < p1; k1++) {
                int n1 = k1 + p1 * j2;
                for (int j1 = 0; j1 < p1; j1++) {
                    complex tmp;
                    complex exp_;
                    tmp.im = 2 * M_PI * j1 * k1 / p1;
                    exp_.real = std::exp(tmp.real) * cos(tmp.im);
                    exp_.im = std::exp(tmp.real) * sin(tmp.im);
                    A1[n1] += mas[j2 + p2 * j1] * exp_;
                    count_operations += 5;
                }
            }
        }
        for (int k2 = 0; k2 < p2; k2++) {
            for (int k1 = 0; k1 < p1; k1++) {
                int n1 = k1 + p1 * k2;
                for (int j2 = 0; j2 < p2; j2++) {
                    complex tmp;
                    complex exp_;
                    tmp.im = 2 * M_PI * (j2 * (k1 + p1 * k2)) / n;
                    exp_.real = std::exp(tmp.real) * cos(tmp.im);
                    exp_.im = std::exp(tmp.real) * sin(tmp.im);
                    A2[n1] += A1[k1 + p1 * j2] * exp_;
                    count_operations += 5;
                }
            }
        }
        delete[] A1;
        count_operations = 5 * 3 * n * log2f(n);
        mas = A2;
    }


    complex* FFT_recursive(complex* mas, int n) {
        if (n == 1) {
            return mas;
        }
        complex* first = new complex[n / 2];
        complex* second = new complex[n / 2];
        complex* output = new complex[n / 2];

        for (int i = 0; i < n / 2; i++) {
            first[i] = mas[2 * i];
            second[i] = mas[2 * i + 1];
        }
        first = FFT_recursive(first, n / 2);
        second = FFT_recursive(second, n / 2);
        for(int i = 0; i < n / 2; ++i){
            complex tmp = second[i] * exp(complex(0, -2 * M_PI * i / n));
            output[i] = first[i] + tmp;
            output[i + n / 2] = first[i] - tmp;
            count_operations += 5;
        }
        delete[] first, second;
        return output;
    }

    bool is_exp_of_2(int n) { return (n & (n - 1)) == 0; }

    complex* FFT(bool mode) {
        if (!is_exp_of_2(n)) return NULL;

        if (mode) {
            for(int i = 0; i < n; ++i){
                mas[i].im = -mas[i].im;
            }
        }
        complex* output = FFT_recursive(mas, n);
        if (mode) {
            for (int i = 0; i < n; ++i) {
                output[i].im = -output[i].im;
            }
        }
        else {
            for (int i = 0; i < n; ++i) {
                output[i] /= n;
            }

        }
        count_operations = 5 * 3 * n * log2f(n);
        return output;
    }



    int n;
    complex* mas;

    Furie(int size, double* massive) {
        mas = new complex[size];
        n = size;
        for (int i = 0; i < size; ++i) {
            mas[i].real = massive[i];
            mas[i].im = 0;
        }
    }


    void printMas() {
        for (int i = 0; i < n; ++i) {
            std::cout << mas[i].real << " " << mas[i].im << "i " << std::endl;
        }
        std::cout << std::endl;
    }

    void Mul(complex* massive) {
        for (int i = 0; i < n; ++i) {
            mas[i] = mas[i] * massive[i];
        }
        for (int i = 0; i < n; ++i) {
            mas[i].real = mas[i].real *  n;
            mas[i].im = mas[i].im *  n;
        }
        count_operations += n * 3;
    }

};