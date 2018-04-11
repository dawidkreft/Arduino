/* 
 *  Example how use LSM6DS33 in arduino project
 *
 */

#include <LSM6.h>           // Libary from arduino tools
#include <Wire.h>
LSM6 imu;

const float pi = 3.141592; 
char report[140];
int ax, ay, az;
float  angle_x,  angle_y;

void setup() {
    Serial.begin(9600);
    Wire.begin();
  
    if (!imu.init()){
      Serial.println("Blad z podlczączeniem IMU!");
      while (1);
    }
   imu.enableDefault();
}


void loop() {
  
     imu.read();
     ax=imu.g.x;   ay=imu.g.y;  az=imu.g.z;
      
     // Calculate of roll and pitch in deg
     angle_x = atan2(ax, sqrt(square(ay) + square(az)))/(pi/360);
     angle_y = atan2(ay, sqrt(square( ax) + square(az)))/(pi/360);  
     
     snprintf(report, sizeof(report), "Accelerometer : %6d %6d %6d    Gyroscope: %6d %6d %6d",
     imu.a.x, imu.a.y, imu.a.z,
     ax, ay, az   );
    
     Serial.println(report);
     Serial.print( "Kat x : ") ; Serial.print(angle_x) ; Serial.print( "  ,kat y : " ); Serial.println(angle_y);

     delay(100);
}
