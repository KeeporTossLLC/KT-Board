 
void setup()
{

    Serial.begin(115200);
    delay(1000);
    
    // turn on power
    Serial.println("Turning on power...");
    pinMode(6, OUTPUT);
    digitalWrite(6,HIGH);
    
      
    pinMode(5, OUTPUT); // MOTOR 1
    pinMode(2, OUTPUT); // MOTOR 2
    delay(5000);
    
}

void loop() 
{

    // FORWARD
    Serial.println("Turning motor FORWARD... 1 sec.");
    digitalWrite(5,HIGH);
    digitalWrite(2,LOW);
    delay(1000);

    // BRAKE
    Serial.println("brake for 5 sec...");
    digitalWrite(5,HIGH);
    digitalWrite(2,HIGH);    
    delay(5000);

    // REVERSE
    Serial.println("Turning motor REVERSE... 1 sec.");
    digitalWrite(5,LOW);
    digitalWrite(2,HIGH);    
    delay(1000);
    
    // BRAKE
    Serial.println("brake for 5 sec...");
    digitalWrite(5,HIGH);
    digitalWrite(2,HIGH);  
    delay(5000);
  
}
