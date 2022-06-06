
#include "MPPT_INC0.h"
#include "rtwtypes.h"
DW rtDW;

/* External inputs (root inport signals with default storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
ExtY rtY;
static RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;
volatile int IsrOverrun = 0;
static boolean_T OverrunFlag = 0;

int in_int=4;  //line added for debugging purpose, remove this later
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
MPPT_INC0_initialize();

}

void loop() {

//_____________________ snippet added for debugging purpose remove this later___________

  
  while (Serial.available()){

     String in_str=Serial.readString();
    Serial.print("Received : ");
    Serial.println(in_str);
     in_int=in_str.toInt();
    if (in_int>=90){
      in_int=90;}
      else if(in_int<=0){
        in_int=0;
        }
    }



//___________End of debugging code______________



  
  // put your main code here, to run repeatedly:
rtU.V_PV=12;   // replace this with the getVoltage() fucntion
rtU.I_PV=in_int;  // replace this with the getCurrent() function



MPPT_INC0_step();     //This is the line that calls the MPPT function
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
delay(1000);

}




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

/* Model initialize function */
void MPPT_INC0_initialize(void)
{
  /* SystemInitialize for Atomic SubSystem: '<Root>/MPPT_INC' */
  /* SystemInitialize for MATLAB Function: '<S1>/MATLAB Function' */
  rtDW.D = 0.5;
  rtU.delta_D=0.005;
  /* End of SystemInitialize for SubSystem: '<Root>/MPPT_INC' */
}
