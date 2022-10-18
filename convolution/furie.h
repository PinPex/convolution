#pragma once

#define _USE_MATH_DEFINES

#include <math.h>
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
            }
            output[k] /= n;
        }
    }

    void reverse_DFT() {
        complex* output = new complex[n];
        for (int k = 0; k < n; k++) {//(x+iy)*(cos+i*sin); re=x*cos-y*sin; im=x*sin+y*cos
            output[k].real = output[k].im = 0;
            for (int i = 0; i < n; i++) {
                complex tmp;
                tmp.im = 2 * M_PI * k * i / n;
                output[k] += exp(tmp) * mas[i];
            }
        }
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
    }

};