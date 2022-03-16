int redPin = 13;  //select the pin for the red LED
int bluePin =12;  // select the pin for the blue LED
int greenPin =14; // select the pin for the green LED
int val = 0;      // an variable for cycling through the colors
                  //Rotory Encoder Variables:
int CLK = 2;      //
int DAT= 0;       // 
int SW = 4;       //
                  //.
int color = 1;    //Code that corresponds to the color on the color wheel you are currently on



void setup() {
  Serial.begin(115200);
  pinMode(redPin, OUTPUT_PULLDOWN);
  pinMode(bluePin, OUTPUT_PULLDOWN);
  pinMode(greenPin, OUTPUT_PULLDDOWN);

  pinMode(CLK,INPUT);
  pinMode(DAT,INPUT);
  pinMode(SW,INPUT);
  Serial.println("PROGRAM START");

  analogWrite(redPin,-1);
       analogWrite(bluePin,-1 );
       analogWrite(greenPin, -1);
  }
void loop() 
{
 // delay(100); 
   
  attachInterrupt(digitalPinToInterrupt(DAT), RoteStateChanged, RISING);

  
  
  switch(color) {
    case 1:
      changeColor(225, 0, 0); 
      
    break;  
    case 2:
      changeColor(150,75,0-20);
    break;  
    case 3:
      changeColor(75,150,-20);
    break;  
    case 4:
      changeColor(-20,225,-20);  
    break;  
    case 5:
      changeColor(-20,150,75);
    break;  
    case 6:
      changeColor(-20,75,150);  
    break; 
    case 7:
      changeColor(-20,-20,225);
    break; 
    case 8:
      changeColor(75,-20,150);
    break; 
    case 9: 
      changeColor(150,-20,75); 
    break; 

  }
     
  
   delay(100);
}
/*************************************
Function: RoteStateChanged() 
Input:  void
Output: void
-------------------------------------
Description: Rotation encoder ISR. 
*************************************/
ICACHE_RAM_ATTR void RoteStateChanged() //When CLK  FALLING READ DAT
{
 Serial.println("MOTION DETECTED!!!");
 if(color != 9)
 {
  color++; 
 }
 else { 
  color = 1; 
 }

 Serial.printf("Color: %d \n" , color); 

 
}


/*************************************
Function: cycle 
Input:  void
Output: void
-------------------------------------
Description: Cycles across RGB values at ~.5 Hz (the clock rate needs work)
*************************************/
//void cycle() { 
//    for(val=255; val>0; val--){
//       analogWrite(redPin, val);
//       analogWrite(bluePin, 255-val);
//       analogWrite(greenPin, 128-val);
//       delay(1); 
//  }
//for(val=0; val<255 ; val++) {
//     analogWrite(redPin, val);
//     analogWrite(bluePin, 255-val);
//     analogWrite(greenPin, 128-val);
//     delay(1);  
//   }
//
//}

/*************************************
Function: betterCycle 
Input:  void
Output: void
-------------------------------------
Description: Cycles across the color wheel at quantized steps.
*************************************/
void betterCycle() { 
  int red;
  int blue;
  int green;
  
//    for(red = 0; red < 225; red+45)
//      {
//        for(blue = 0 ; blue < 225 ; blue +45)
//        {
//          
//          for(green = 0 ; green < 225 ; green + 45 )
//          {
//            changeColor(red, green, blue); 
//            
//          }
//        }
//     }

    switch(color) {
    case 1:
      changeColor(225, 0, 0); 
      
    break;  
    case 2:
      changeColor(150,75,0);
    break;  
    case 3:
      changeColor(75,150,0);
    break;  
    case 4:
      changeColor(0,225,0);  
    break;  
    case 5:
      changeColor(0,150,75);
    break;  
    case 6:
      changeColor(0,75,150);  
    break; 
    case 7:
      changeColor(0,0,225);
    break; 
    case 8:
      changeColor(75,0,150);
    break; 
    case 9: 
      changeColor(150,0,75); 
    break; 
}
}

/*************************************
Function: changeColor 
Input:  int red   - color to be assigned to red pin
        int blue  - color to be assigned to blue pin
        int green - color to be assigned to green pin
Output: void
-------------------------------------
Description: Cycles across the color wheel at quantized steps.
*************************************/
void changeColor(int red, int blue, int green) 
{
       analogWrite(redPin, red);
       analogWrite(bluePin, blue);
       analogWrite(greenPin, green);
}
