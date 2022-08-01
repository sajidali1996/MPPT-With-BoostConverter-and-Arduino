#include "MPPT_INC0.h"     //Header file generated from Simulink Model
#include "rtwtypes.h"      //Header file generated from Simulink Model
#include <avr/io.h>
#include <avr/interrupt.h>
unsigned int reload = 0x186A;//(10Hz)//0x7A12(5Hz);//0xF424(1Hz);

int dutyCycle;
DW rtDW;
/* External inputs (root inport signals with default storage) */
ExtU rtU;      //input to inc mppt algorithm fucntion

/* External outputs (root outports fed by signals with default storage) */
ExtY rtY;      // output from inc mppt algorithm fucntion
static RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;
volatile int IsrOverrun = 0;
static boolean_T OverrunFlag = 0;

//__________interrupt service routine to update duty cycle______________
ISR(TIMER1_COMPA_vect)
{
updateDutyCycle();
}
//_________________________End of ISR_______________


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  TCCR0B = TCCR0B & B11111000 | B00000001;    // set timer 0 divisor to     1 for PWM frequency of 62500.00 Hz pin 5
  ///interrupt setup
    cli();
    TCCR1A = 0;
    TCCR1B = 0; 
    OCR1A = reload;
    TCCR1B = (1<<WGM12) | (1<<CS12); 
    TIMSK1 = (1<<OCIE1A); 
    sei();
    //initialize variables within a function
    MPPT_INC0_initialize();
    
}

void loop() {

////_____________________ snippet added for debugging purpose remove this later___________
//
//  
//  while (Serial.available()){      //This snippet of code takes input from serial input and stores in in_int
//   int in_int=4;  //line added for debugging purpose, remove this later
//     String in_str=Serial.readString();
//    Serial.print("Received : ");
//    Serial.println(in_str);
//     in_int=in_str.toInt();
//    if (in_int>=90){
//      in_int=90;}
//      else if(in_int<=0){
//        in_int=0;
//        }
//    }
//
//
//
////___________End of debugging code______________



  
  // Read PV voltage and PV current at input
rtU.V_PV=getVoltage();   
rtU.I_PV=getCurrent();  

printdebugParameters();

//analogWrite(5,127);
delay(1000);

}

//___________CUSTOM FUNCTIONS_________________


/* Model step function */
void MPPT_INC0_step(void)
{
  real_T dI;
  real_T dV;

  /* Outputs for Atomic SubSystem: '<Root>/MPPT_INC' */
  /* MATLAB Function: '<S1>/MATLAB Function' incorporates:
   *  Inport: '<Root>/I_PV'
   *  Inport: '<Root>/V_PV'
   *  Inport: '<Root>/delta_D'
   */
  dV = rtU.V_PV - rtDW.V_PV_1;
  if (dV == 0.0) {
    dV = 0;//1.0E-5;
  }

  dI = rtU.I_PV - rtDW.I_PV_1;
  if (dV == 0.0) {
    if (!(dI == 0.0)) {
      if (dI > 0.0) {
        rtDW.D += rtU.delta_D;
      } else {
        rtDW.D -= rtU.delta_D;
      }
    }
  } else {
    dV = ((dI / dV) * rtU.V_PV) + rtU.I_PV;
    if (!(dV == 0.0)) {
      if (dV > 0.0) {
        rtDW.D -= rtU.delta_D;
      } else {
        rtDW.D += rtU.delta_D;
      }
    }
  }

  rtDW.V_PV_1 = rtU.V_PV;
  rtDW.I_PV_1 = rtU.I_PV;

  /* Saturate: '<S1>/Saturation' incorporates:
   *  MATLAB Function: '<S1>/MATLAB Function'
   */
  if (rtDW.D > 0.9) {
    /* Outport: '<Root>/DutyCycle' */
    rtY.DutyCycle = 0.9;
  } else if (rtDW.D < 0.1) {
    /* Outport: '<Root>/DutyCycle' */
    rtY.DutyCycle = 0.1;
  } else {
    /* Outport: '<Root>/DutyCycle' */
    rtY.DutyCycle = rtDW.D;
  }

  /* End of Saturate: '<S1>/Saturation' */
  /* End of Outputs for SubSystem: '<Root>/MPPT_INC' */
}

//___________________________***______________________________________
/* Model initialize function */
void MPPT_INC0_initialize(void)
{
  /* SystemInitialize for Atomic SubSystem: '<Root>/MPPT_INC' */
  /* SystemInitialize for MATLAB Function: '<S1>/MATLAB Function' */
  rtDW.D = 0.5;          
  rtU.delta_D=0.005;    //step change in every MPPT algorithm execution 
                         // the step change in 0.005 results in change in pulse width by 0.5% 
   dutyCycle=127;
  /* End of SystemInitialize for SubSystem: '<Root>/MPPT_INC' */
}
//_________________________***______________________________________
float getVoltage(){
  return  0.0346*analogRead(A1) + 0.0781;
   }
//_________________________***____________________________________
float getCurrent(){
float in=analogRead(A2)-512;
return (in/20);
}
//________________________***________________________________________
void updateDutyCycle()
{
 MPPT_INC0_step();     //This is the line that calls the MPPT function
  dutyCycle=255*rtY.DutyCycle;//map(rtY.DutyCycle,0,1.0,0,255);
  analogWrite(5,dutyCycle);
  //Serial.print("ISR ran successfully @ :");  //debug line
  //Serial.println(dutyCycle);                  //debug line
}
//______________________***________________________________________
void printdebugParameters(){
  Serial.print("V : ");
  Serial.print(rtU.V_PV);
  Serial.print("  , ");
  Serial.print("I : ");
  Serial.print(rtU.I_PV);
  Serial.print("  , ");
  Serial.print("P : ");
  Serial.print(rtU.V_PV*rtU.I_PV);
  Serial.print("  , ");
  Serial.print("D : ");
  Serial.println(rtY.DutyCycle);  
  
  }
//______________________***____________  
