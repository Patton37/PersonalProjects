int sensorPin = 0;
int indicator = 13;
int LED =13;
int state;


void setup()
{
  delay(1000);
  pinMode(LED, OUTPUT); 
  pinMode(sensorPin,INPUT);
  pinMode(indicator,OUTPUT);
    Serial.begin(115200);
    delay(1000);
  Serial.printf("Program Start:\n");
}

void loop()
{

     state = digitalRead(sensorPin); 
  
 
  
  if (state == HIGH) {
    toggle();
    delay(1000);
  }
  state = digitalRead(sensorPin); 
 
}

/*************************************
Function: toggle() 
Input:  void
Output: void
-------------------------------------
Description: A sample function that toggles an LED on and off rapidly . 
*************************************/
void toggle()
{
  
  
  for(int i = 0; i <2 ; i++)
  {
    if (state == HIGH ){
        state = LOW;
        digitalWrite(LED,LOW);
      }else{
        state = HIGH;  
        digitalWrite(LED,HIGH);
    }
      
      
    Serial.println("TOGGLED");
    delay(200); 
   
    
  }
}
