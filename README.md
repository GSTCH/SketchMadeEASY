# Sketch made easy for Arduino

This libary is an abstraction of an Arduino sketch on logic level. Instead of programming in bits and bytes, the control logic is configured by combining the classes. For this create objects of inputs, actions and combine them with relations and conditions. There are an amount of example to see how easy this library is to use. 
The library supports the remote control FlySky FS-i6X (up to 14 channels). The same functions are also available by an App (connected with bluetooth). The App has been developed with "MIT AppInventor". 

## Getting started
Sketches are no longer programmed with this library, but can be configured by combining different classes. How does it work? Basic idea is how an Arduino works: It combines inputs with actuators through logic. A sketch with ***Sketch made Easy*** is created in three steps:
1). Definition of the inputs
2). Definition of the actuators (outputs)
3). Definition of logic: Through rules, input and actuator are set into relations.

There are many examples. The example directories contains a schema as well. Here the code of a toggling LED (the most common hello world example with Arduino). Open  "File:/Examples/SketchMadeEasy/Examples/04-ToggleingLed" into Arduino IDE to see full code.
```
  //((*** Initialize: Configure your sketch here....

  //** Create input:
  // Input changes value periodically and toggles between High and Low.
  Timer* timer = new Timer(TIMER_INTERVAL_MSEC, true);

  //** Create actuator. 
  // A DigitalOutput knows the value On and Off.
  DigitalOutput* led = new DigitalOutput(LED_PIN);

  //** Define logic with conditions and relations
  // Define relation when timer value changes to High
  CompareCondition* conditionLedOn = new CompareCondition(timer, OpEQ, Timer::High);
  Relation1to1* relationLedOn = new Relation1to1(conditionLedOn, led, FixValue::On());

  // Define relation when timer value changes to Low
  CompareCondition* conditionLedOff = new CompareCondition(timer, OpEQ, Timer::Low);
  Relation1to1* relationLedOff = new Relation1to1(conditionLedOff, led, FixValue::Off());
  // ***))
```
## Classes / Supported hardware
### Inputs
* Calculate
* ConditionInput
* DependentInput
* DigitalInput
* FixValue
* InverterValue
* JoystickAxis
* LoopSwitch
* MotorFlop
* Switch2Position
* Switch3Position
* Timer
* ToggleSwitch
* UltrasonicRangefinder
* VariableInput
### Actuators (Output)
* ActuatorCollection
* Buzzer
* DigitalOutput
* EncodeModeI2C
* EncoderMotorL298
* EncoderMotorL9110
* MotorI2C
* MotorL298
* MotorL9110
* MotorServo360I2C
* MotorServo360Pwm
* MotorServo360T1
* MotorServo360T2
* MotorStepperRotate
* MotorStepperRotateI2C
* ServoI2C
* ServoPwm
* ServoStepperPosition
* ServoStepperPositionI2C
* ServoT1
* ServoT2
* VariableOutput
### Conditions
* CompareCondition
* ElseCondition
* LogicCondition
### Relations
* CrawlerSteering
* Relation1to1

## Workboard
***Sketch made easy*** contains not only software. A construction kit of different modules makes it possible to put together an individual workboard. With the STL files, these can be produced using a 3D printer.  

## Documentation
See Wiki of this Repository.
