const int interruptA = 0;       
const int interruptB = 1;       
int CLK = 2;     // PIN2
int DAT = 0;     // PIN3
int BUTTON = 4;  // PIN4
int LED1 = 5;    // PIN5
int LED2 = 16;    // PIN6
int COUNT = 0;

void setup() 
 {
  attachInterrupt(digitalPinToInterrupt(CLK), RoteStateChanged, RISING);
 // attachInterrupt(interruptB, buttonState, FALLING);
 
  pinMode(CLK, INPUT); 
  digitalWrite(2, HIGH);  // Pull High Resistance  
  pinMode(DAT, INPUT); 
  digitalWrite(0, HIGH);  // Pull High Resistance 
 
 

  pinMode(BUTTON, INPUT); 
  digitalWrite(4, HIGH);  // Pull High Resistance
  pinMode(LED1, OUTPUT); 
  pinMode(LED2, OUTPUT); 
   Serial.begin(115200);
 }


void loop() 
{
  if  (!(digitalRead(BUTTON))) 
    {
     COUNT = 0;  
     //Serial.println("STOP COUNT = 0");
     digitalWrite(LED1, LOW);
     digitalWrite(LED2, LOW);
     delay (2000);
    }
      Serial.println(COUNT); 
  
      RoteStateChanged();
      
}

//-------------------------------------------
void RoteStateChanged() //When CLK  FALLING READ DAT
{
 if  (digitalRead(DAT)  ) // When DAT = HIGH IS FORWARD
   {
    COUNT++;
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, LOW);
    delay(20);
   }
else                  // When DAT = LOW IS BackRote
   {
    COUNT--;
    digitalWrite(LED2, HIGH);
    digitalWrite(LED1, LOW);
    delay(20);
   }
}
