

int D=50;


int dutyCycle=0;

float V_PV=0,I_PV=0,P_PV=0,P_PV_1=0,V_PV_1=0,I_PV_1=0,dV=0,dI=0,delta_D=1;

//________________________

void setup()
 {
   Serial.begin(9600);
   pinMode(5,OUTPUT);
   TCCR0B = TCCR0B & B11111000 | B00000001;    // set timer 0 divisor to     1 for PWM frequency of 62500.00 Hz pin 5
   
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


//apply duty cycle
dutyCycle=map(D,0,100,255,0);
analogWrite(5,dutyCycle);//uncomment this for 62kHz


//display variables
printVariables();

   
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
