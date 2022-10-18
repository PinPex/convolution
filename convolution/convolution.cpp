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
    int count_operations = 0;
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
            if (i % 4 == 0)
                cout << a[i] << endl;
            else
                cout << a[i] << " ";
        }
        cout << endl;
    }
    void printSecond(int size) {
        cout << "Second massive: " << endl;
        for (int i = 0; i < size; ++i) {
            if (i % 4 == 0)
                cout << b[i] << endl;
            else
                cout << b[i] << " ";
        }
        cout << endl;
    }

    void printFirst(int size) {
        cout << "First massive: " << endl;
        for (int i = 0; i < size; ++i) {
            cout << a[i] << " ";
        }
        cout << endl;
    }
    void printSecond() {
        cout << "Second massive: " << endl;
        for (int i = 0; i < size2; ++i) {
            cout << b[i] << " ";
        }
        cout << endl;
    }
    void printOut() {
        cout << "Out massive: " << endl;
        for (int i = 0; i < Nout; ++i) {
            cout << c[i] << " ";
                
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
                    count_operations += 3;
                }
                else
                    break;
                    
            }
            c[i] = sum;
        }
    }


    double* makeZeros(double* mas, int size) {
        double* temp = new double[this->Nout];
        memset(temp, 0, sizeof(temp));

        

        for (int i = 0; i < size; ++i) {
            temp[i] = mas[i];
        }

        
        
        delete[] mas;
        return temp;
    }

    void simpleFurieConvolution() {
        this->a = makeZeros(a, size1);
        this->b = makeZeros(b, size2);
        int n = this->Nout;
        Furie furA(n, a);
        //furA.printMas();
        Furie furB(n, b);
        //furB.printMas();
        furA.DFT();
        //furA.printMas();
        furB.DFT();
        //furB.printMas();
        furA.Mul(furB.mas);
        //furA.printMas();
        furA.reverse_DFT();
        //furA.printMas();
        for (int i = 0; i < n; ++i) {
            c[i] = furA.mas[i].real;
        }
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
    conv.simpleFurieConvolution();

    conv.printFirst(conv.Nout);
    conv.printSecond(conv.Nout);
    conv.printOut();
    conv.printOperations();
    conv.countNull();
    
}