#include <math.h>
#include <Servo.h>

#define PI 3.1415926535

using namespace std;

//Initializations
#define bigSoundTop A0
#define bigSoundLeft A1
#define bigSoundRight A2
#define servoPinLeft 4
#define servoPinRight 5
#define servoPinGo 6
Servo servoLeft;
Servo servoRight;
Servo servoGo;

void setup()
{
    pinMode(bigSoundTop, INPUT);
    pinMode(bigSoundLeft, INPUT);
    pinMode(bigSoundRight, INPUT);
    servoRight.attach(servoPinRight);
    servoLeft.attach(servoPinLeft);
    servoGo.attach(servoPinGo);
    Serial.begin(9600);
}

void loop()
{
    //Initializes all values to 0 in order to reset the loop on each iteration
    float avrTopVal = 0;
    float avrLeftVal = 0;
    float avrRightVal = 0;
    double finalVeci = 0;
    double finalVecj = 0;
    double finalVecTheta = 0;
    double vectorTi = 0;
    double vectorLi = 0;
    double vectorRi = 0;
    double vectorTj = 0;
    double vectorLj = 0;
    double vectorRj = 0;
    double finalDirectionTheta = 0;
    double finalDirection = 0;
    double vecTop = 0;
    double vecLeft = 0;
    double vecRight = 0;
    int i = 0;
    //Serial.println(analogRead(bigSoundTop));

    //Taking 100 values from sound sensors and adding them all up
    for (i = 0; i < 100; ++i)
    {
        vecTop += analogRead(bigSoundTop);
        vecLeft += analogRead(bigSoundLeft);
        vecRight += analogRead(bigSoundRight);
    }

    //Serial.println(vecTop);
    //Serial.println(vecLeft);
    //Serial.println(vecRight);
    //delay(10000);
    
    //Averaging those values
    avrTopVal = vecTop / 100;
    avrLeftVal = vecLeft / 100;
    avrRightVal = vecRight / 100;

    //Calculates vector i and j directions for all 3 sensors
    vectorTi = avrTopVal * cos(90 * PI / 180);
    vectorTj = avrTopVal * sin(90 * PI / 180);
    vectorLi = avrLeftVal * cos(210 * PI / 180);
    vectorLj = avrLeftVal * sin(210 * PI / 180);
    vectorRi = avrRightVal * cos(330 * PI / 180);
    vectorRj = avrRightVal * sin(330 * PI / 180);

    //Calculates final vector i and j 
    finalVeci = vectorTi + vectorLi + vectorRi;
    finalVecj = vectorTi + vectorLj + vectorRj;

    //Calculates the theta for the final total vector and adds 180 to get the final direction of travel
    finalVecTheta = atan((finalVecj / finalVeci));
    /*if(finalVecTheta > 360)
    {
      finalVecTheta = finalVecTheta - 360;
    }
    else*/
    finalDirectionTheta = finalVecTheta + 180;
    //Serial.println(finalDirectionTheta);
}
