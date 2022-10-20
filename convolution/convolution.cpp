#include <iostream>
#include "furie.h"
using namespace std;

class Convolution {
private:
    double* a;
    int size1;
    double* b;
    int size2;
    double* c;
    int count_operations = -5;
public:
    int Nout;
    Convolution() {
        cout << "Input size of the first massive: ";
        cin >> size1;
        cout << "Input size of the second massive: ";
        cin >> size2;
        a = new double[size1];
        b = new double[size2];
        Nout = size1 + size2 - 1;
        c = new double[Nout];
    }

    void fillRand() {
        srand(time(0));
        int i;
        for (i = 0; i < size1; ++i) {
            a[i] = double(rand()) / RAND_MAX;
        }
        for (i = 0; i < size2; ++i) {
            b[i] = double(rand()) / RAND_MAX;
        }
    }

    void fillCur() {
        int i;
        cout << "Input first massive of numbers: " << endl;
        for (i = 0; i < size1; ++i) {
            cin >> a[i];
        }
        cout << "Input second massive of numbers: " << endl;
        for (i = 0; i < size2; ++i) {
            cin >> b[i];
        }
    }

    void printFirst() {
        cout << "First massive: " << endl;
        for (int i = 0; i < size1; ++i) {
            cout << fixed << a[i] << " ";
        }
        cout << endl;
    }
    void printSecond(int size) {
        cout << "Second massive: " << endl;
        for (int i = 0; i < size; ++i) {
            cout << fixed << b[i] << " ";
        }
        cout << endl;
    }

    void printFirst(int size) {
        cout << "First massive: " << endl;
        for (int i = 0; i < size; ++i) {
            cout << fixed << a[i] << " ";
        }
        cout << endl;
    }
    void printSecond() {
        cout << "Second massive: " << endl;
        for (int i = 0; i < size2; ++i) {
            cout << fixed << b[i] << " ";
        }
        cout << endl;
    }
    void printOut() {
        cout << "Out massive: " << endl;
        for (int i = 0; i < Nout; ++i) {
            cout << fixed << c[i] << " ";
                
        }
        cout << endl;
    }
    void countNull() {
        count_operations = 0;
    }

    void printOperations() {
        cout << "Count of operations: " << count_operations << endl;
    }

    void choiceFill() {
        int choice;
        cout << "1. Fill Random\n2. Fill current numbers" << endl;
        cin >> choice;
        if (choice == 1)
            this->fillRand();
        if (choice == 2)
            this->fillCur();
    }

    double max(double a, ...) {
        double* p = &a;
        double max = *p;
        p++;
        while (*p) {
            if (*p > max) {
                max = *p;
            }
            p++;
        }
        return max;
    }


    void simpleConvolution() {
        //cout << max(2., 5., 12., 22., 11., 111., 444., 1000.) << endl;
        for (int i = 0; i < Nout; ++i) {
            double sum = 0;
            for (int k = 0; k < size1; ++k) {
                if (i - k >= 0) {
                    sum += a[k] * b[i - k];
                    count_operations += 2;
                }
                else
                    break;
                    
            }
            c[i] = sum;
        }
    }

    double* fillZeros(double* mas, int size) {
        for (int i = 0; i < size; ++i) {
            mas[i] = 0;
        }
        return mas;
    }


    double* makeZeros(double* mas, int size) {
        double* temp = new double[this->Nout];
        temp = fillZeros(temp, this->Nout);

        

        for (int i = 0; i < size; ++i) {
            temp[i] = mas[i];
        }
        return temp;
    }

    void simpleFurieConvolution() {
        double* a1 = makeZeros(a, size1);
        double* b1 = makeZeros(b, size1);
        Furie furA(this->Nout, a1);
        Furie furB(this->Nout, b1);
        furA.DFT();
        furB.DFT();
        furA.Mul(furB.mas);
        furA.reverse_DFT();
        for (int i = 0; i < this->Nout; ++i) {
            c[i] = furA.mas[i].real;
        }
        count_operations = furA.count_operations + furB.count_operations + this->Nout;
    }
    void halfFastFurieConvolution() {
        double* a1 = makeZeros(a, size1);
        double* b1 = makeZeros(b, size1);
        Furie furA(this->Nout, a1);
        Furie furB(this->Nout, b1);
        furA.half_fast_furie();
        furB.half_fast_furie();
        furA.Mul(furB.mas);
        furA.reverse_half_fast_furie();
        for (int i = 0; i < this->Nout; ++i) {
            c[i] = furA.mas[i].real;
        }
        count_operations = furA.count_operations + furB.count_operations + this->Nout;
    }
    void FastFurieConvolution() {
        double* a1 = makeZeros(a, size1);
        double* b1 = makeZeros(b, size1);
        Furie furA(this->Nout, a1);
        Furie furB(this->Nout, b1);
        furA.FFT(0);
        furB.FFT(0);
        furA.Mul(furB.mas);
        furA.FFT(1);
        for (int i = 0; i < this->Nout; ++i) {
            c[i] = furA.mas[i].real;
        }
        count_operations = furA.count_operations + furB.count_operations + this->Nout;
    }

    
};

int main()
{
    Convolution conv;
    conv.choiceFill();
    conv.simpleConvolution();

    conv.printFirst();
    conv.printSecond();
    conv.printOut();
    conv.printOperations();
    conv.countNull();

    cout << endl << endl;
    cout << "//in development//" << endl;
    conv.simpleFurieConvolution();

    conv.printFirst(conv.Nout);
    conv.printSecond(conv.Nout);
    conv.printOut();
    conv.printOperations();
    conv.countNull();
    cout << endl;

    conv.halfFastFurieConvolution();

    conv.printFirst(conv.Nout);
    conv.printSecond(conv.Nout);
    conv.printOut();
    conv.printOperations();
    conv.countNull();
    
}