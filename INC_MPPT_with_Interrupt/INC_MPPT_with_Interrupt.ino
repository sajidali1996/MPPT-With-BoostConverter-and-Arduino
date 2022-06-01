
//For interrupt  we will be updating duty cycle every 1 second
#include <avr/io.h>
#include <avr/interrupt.h>
unsigned int reload = 0xF424; 
//interrupt sevice routine
ISR(TIMER1_COMPA_vect)
{
updateDutyCycle();
}

////



int D=50;

int dutyCycle=0;

float V_PV=0,I_PV=0,P_PV=0,P_PV_1=0,V_PV_1=0,I_PV_1=0,dV=0,dI=0,delta_D=1;

//________________________

void setup()
 {
   Serial.begin(9600);
   pinMode(5,OUTPUT);
   TCCR0B = TCCR0B & B11111000 | B00000001;    // set timer 0 divisor to     1 for PWM frequency of 62500.00 Hz pin 5


   ///interrupt setup
    cli();
    TCCR1A = 0;
    TCCR1B = 0; 
    OCR1A = reload;
    TCCR1B = (1<<WGM12) | (1<<CS12); 
    TIMSK1 = (1<<OCIE1A); 
    sei();
}
void loop(){
  
  V_PV=getVoltage();
  I_PV=getCurrent();

//___________________MPPT Algorithm INC___________________
//

dV=V_PV-V_PV_1;
//
if (dV==0){
    dV=1e-5;    //to avoid dividing by zero
}
dI=I_PV-I_PV_1;
//
if(dV==0){
            if(dI==0){
                      //return
                     }
             else{
                          if(dI>0){
                                   D=D+delta_D;//increase voltage;
                                  }
                          else{
                                    D=D-delta_D;//decrease voltage;
                               }
                  }
         } 
 else{
            if(I_PV+(dI/dV)*V_PV==0){
                                     //return 
                                    }
            else{
                      if(I_PV+(dI/dV)*V_PV>0){
                                               D=D-delta_D;//decrease voltage;
                                              }
                      else{
                                               D=D+delta_D;//increase voltage;
                          }
                  
                }
      }

//Recording historical values      
V_PV_1=V_PV;
I_PV_1=I_PV;

//______________________End of MPPT__________


//display variables
printVariables();
delay(1000);
   
}

////___________Custom Functions__________


void updateDutyCycle()
{

  dutyCycle=map(D,0,100,255,0);
  analogWrite(5,dutyCycle);
 // Serial.print("ISR ran successfully @ :");  //debug line
  //Serial.println(millis());                  //debug line

}

void printVariables(){
    Serial.print("V : ");
    Serial.print(V_PV);
    Serial.print(",");
    Serial.print("I : ");
    Serial.print(I_PV);
    Serial.print(",");
    Serial.print("P : ");
    Serial.print(P_PV);
    Serial.print(",");
    Serial.print("D : ");
    Serial.println(100-D);
  }

  
float getVoltage(){
  return  0.0346*analogRead(A1) + 0.0781;
  
   }


   
float getCurrent(){
  float in=analogRead(A2)-512;
  return (in/20);

}
