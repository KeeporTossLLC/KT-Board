void setup() 
{

   Serial.begin(115200);
   
   Serial.println("Turning ON power to secondary 3.3v supply.");
   pinMode(6, OUTPUT);
   digitalWrite(6,HIGH);    
  
}




void loop()
{

  
}
