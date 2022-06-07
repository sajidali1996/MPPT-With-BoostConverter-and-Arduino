/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: MPPT_INC0.h
 *
 * Code generated for Simulink model 'MPPT_INC0'.
 *
 * Model version                  : 1.18
 * Simulink Coder version         : 9.7 (R2022a) 13-Nov-2021
 * C/C++ source code generated on : Sat Jun  4 18:34:37 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. Traceability
 *    3. MISRA C:2012 guidelines
 *    4. Safety precaution
 * Validation result: Not run
 */

#ifndef RTW_HEADER_MPPT_INC0_h_
#define RTW_HEADER_MPPT_INC0_h_
#ifndef MPPT_INC0_COMMON_INCLUDES_
#define MPPT_INC0_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* MPPT_INC0_COMMON_INCLUDES_ */

#include <stddef.h>

/* Model Code Variants */
#include "MW_target_hardware_resources.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#define MPPT_INC0_M                    (rtM)

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T V_PV_1;                       /* '<S1>/MATLAB Function' */
  real_T I_PV_1;                       /* '<S1>/MATLAB Function' */
  real_T D;                            /* '<S1>/MATLAB Function' */
} DW;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T V_PV;                         /* '<Root>/V_PV' */
  real_T I_PV;                         /* '<Root>/I_PV' */
  real_T delta_D;                      /* '<Root>/delta_D' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T DutyCycle;                    /* '<Root>/DutyCycle' */
} ExtY;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;
};

/* Block signals and states (default storage) */
extern DW rtDW;

/* External inputs (root inport signals with default storage) */
extern ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY rtY;

/* Model entry point functions */
extern void MPPT_INC0_initialize(void);
extern void MPPT_INC0_step(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;
extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('Gen_EmbeddedCode_MPPT_with_INC/MPPT_INC')    - opens subsystem Gen_EmbeddedCode_MPPT_with_INC/MPPT_INC
 * hilite_system('Gen_EmbeddedCode_MPPT_with_INC/MPPT_INC/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Gen_EmbeddedCode_MPPT_with_INC'
 * '<S1>'   : 'Gen_EmbeddedCode_MPPT_with_INC/MPPT_INC'
 * '<S2>'   : 'Gen_EmbeddedCode_MPPT_with_INC/MPPT_INC/MATLAB Function'
 */

/*-
 * Requirements for '<Root>': MPPT_INC0
 */
#endif                                 /* RTW_HEADER_MPPT_INC0_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
