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
            if (i % 4 == 0)
                cout << a[i] << endl;
            else
                cout << a[i] << " ";
        }
        cout << endl;
    }
    void printSecond() {
        cout << "Second massive: " << endl;
        for (int i = 0; i < size2; ++i) {
            if (i % 4 == 0)
                cout << b[i] << endl;
            else
                cout << b[i] << " ";
        }
        cout << endl;
    }
    void printOut() {
        cout << "Out massive: " << endl;
        for (int i = 0; i < Nout; ++i) {
            if (i % 4 == 0)
                cout << c[i] << endl;
            else
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

    void simpleConvolution() {
        for (int i = 0; i < Nout; ++i) {
            double sum = 0;
            for (int k = 0; k < size1; ++k) {
                if (i - k >= 0) {
                    sum += a[k] * b[i - k];
                    count_operations += 3;
                }
                    
            }
            c[i] = sum;
        }
    }

    double* makeZeros(double* mas, int size) {
        double* temp = new double[this->Nout];
        for (int i = 0; i < this->Nout - size; ++i) {
            temp[i] = 0;
        }

        for (int i = this->Nout - size; i < this->Nout; ++i) {
            temp[i] = mas[i - (this->Nout - size)];
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
        furA.dis_fur();
        //furA.printMas();
        furB.dis_fur();
        //furB.printMas();
        furA.Mul(furB.mas);
        //furA.printMas();
        furA.back_dis_fur();
        //furA.printMas();
        for (int i = 0; i < n; ++i) {
            c[i] = furA.mas[i].R;
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

    conv.simpleFurieConvolution();

    conv.printFirst(conv.Nout);
    conv.printSecond(conv.Nout);
    conv.printOut();
    conv.printOperations();
    conv.countNull();
    
}