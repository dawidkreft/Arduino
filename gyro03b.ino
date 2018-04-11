/* 
 *  Example how use L3GD20H in arduino project
 *
 */

#include <L3G.h>                 // libary from arduino 
#include <Wire.h>                // libary from arduino 

#define left 5                      // You can control LED by PWM
#define right 6
L3G gyro;

void setup() {
  pinMode(left, OUTPUT);
  pinMode(right, OUTPUT);
  
  Serial.begin(9600);
  Wire.begin();

  if (!gyro.init()){
    Serial.println("Sprawdz polaczenie!!");
    while (1);
  }
  gyro.enableDefault();

}

const float pi = 3.141592; 
const int sample_no = 100;               // no of samples for aproximation
int16_t ax, ay, az;
float x, y, z;
int  sample;
float _angle_x, angle_x, _angle_y, angle_y;
long ax_sum, ay_sum, az_sum;


void loop() {
    gyro.read();
    ax_sum = ax_sum + ((int)gyro.g.x);
    ay_sum = ay_sum + ((int)gyro.g.y);
    az_sum = az_sum + ((int)gyro.g.z);
    
    sample++;
      
    if (sample == sample_no)              
    {
     // mean values
     x = ax_sum/sample_no;
     y = ay_sum/sample_no;
     z = az_sum/sample_no;
     
     // Calculate of roll and pitch in deg
     angle_x = atan2(x, sqrt(square(y) + square(z)))/(pi/360);
     angle_y = atan2(y, sqrt(square(x) + square(z)))/(pi/360);
     
     // Reset values for next aproximation   
     sample=0;
     ax_sum = 0;
     ay_sum = 0;
     az_sum = 0;
        
     Serial.print(angle_x);
     Serial.print("\t");        // \t = tablator 
     Serial.println(angle_y);
     analogWrite(left ,abs(angle_x));
     analogWrite(right,abs(angle_y));
     delay(500);
    }   
}
