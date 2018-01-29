#include <Stepper.h>
int x; // x axis variable
int y; // y axis variable
int z; // z axis variable
int index = 0;
int rms_index = 0;
double rms;
double data_array[5];
int motor_array[10];
double rms_array[10];
int motor_pos = 0;


const int stepsPerRevolution = 17; //Number of steps per revolution
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);
void setup()
{ 
   Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
    // set the speed at 90 rpm:
   myStepper.setSpeed(90);
}
void loop()
{
  for (int n = 0; n<10 ; n++){
    // Sensor reading and sensor value storing
    z = analogRead(5); // read A5 input pin
    Serial.print("Index = "); // print index value
    Serial.println(index);
    Serial.print("Z = "); // print z adc value
    Serial.println(z);
    data_array[index] = z;
    // After one cycle, calculate rms value for this cycle
     if (index == 4){
        rms = squareAdd(data_array);
        Serial.print("RMS = "); // print rms value
        Serial.println(rms);
        rms_array[rms_index] = rms;
        rms_index++;
        if (rms_index == 10) {
            rms_index = 0;
        }
      // Outputing the desired position according to the rms value
     //mapping(rms);
     motor_pos = motor_position (rms_index);
     motor_array[rms_index] = motor_pos;
     if (rms_index == 5)
        delay(3000);
   }
     index++;
    // Strats a new ctcle, and reset the index
      if (index == 5) {
          index = 0;
      }
   delay(2000);
  //y = analogRead(4); // read A4 input pin
  //x = analogRead(3); // read A3 input pin
  //Serial.print("X = "); // print x adc value
  //Serial.println(x);
  //Serial.print("Y = "); // print y adc value
  //Serial.println(y);
   //delay(2000);
  if (rms_index==9){
       Serial.print("Motor position: ");
          for (int i = 0; i<10 ; i++){
          Serial.println(motor_array[i]);
       }
       
    }
  
  }
    
}

int* sensor_reading (double ){
  

}


/*
 * The square root of: (x1^2 + x2^2 + x3^2 ... xn^2) / n
 */
double squareAdd(double data_array[])
{
  double add = 0;
  for (int i=0; i < 5; i++) {
    Serial.println(data_array[i]);
    add += (data_array[i])*(data_array[i]);
  }
  return sqrt(add/5);
}

// determining stepper position values; assuming 17 steps correspond to 1
int motor_position (int n){
  if (n <= 5){
      Serial.print("clockwise step");
      myStepper.step(stepsPerRevolution);
      motor_pos++;
      Serial.println(motor_pos);
      delay(1500);  
   }
   else if ( n > 5 ){
      Serial.print("counterclockwise step");
      myStepper.step(-stepsPerRevolution);
      motor_pos--;
      Serial.println(motor_pos);
      delay(1500);  
   } 
   //delay (2000);
   return motor_pos;
}

void optimization(int motor_array[], double rms_array[]){
       
}

