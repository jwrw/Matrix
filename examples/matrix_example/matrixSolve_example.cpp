#include <Arduino.h>

#include <Matrix.h>
#include "MatrixSolve.h"

float array1[4][4] = {{16,19,2,7},{5,34,77,1},{23,37,38,7},{9,33,10,0}};
float array2[4][1] = {{5},{6},{7},{8}};
//create float type matrices
Matrixf  A(4,4,(float*)array1);
Matrixf  B(4,1,(float*)array2);

void setup() {
    Serial.begin(115200);
}

void loop() {
    delay(3000);

    Serial.println("A: ");
    A.show(4);
    Serial.println("B: ");
    B.show(4);

    Matrixf Acopy = Matrixf (A);
    Serial.println("Acopy: ");
    Acopy.show(4);

    Matrixf BB = solveFor(A,B);
    Serial.println("BB (solution): ");
    BB.show(4);

    Serial.println("Check - Original A x Result should be B: ");
    (Acopy * BB).show(4);

    Serial.println("--------------------------------------");
}

