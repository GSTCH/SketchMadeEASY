# Sketch made EASY for Arduino

This libary is an abstraction of an Arduino sketch on logic level. Instead of programming in bits and bytes, the control logic is configured by combining the classes. For this create objects of inputs, actions and combine them with relations and conditions. There are an amount of example to see how easy this library is to use.<BR>
The library supports the remote control FlySky FS-i6X (up to 10 channels). The same functions are also available by an App (connected with bluetooth). The App has been developed with "MIT AppInventor". <BR>

## Introduction Video
Click on the image to play the video<BR>
[<img src="https://github.com/GSTCH/SketchMadeEASY/blob/main/Resource/Images/GettingStarted/SketchMadeEasy_Introduction_Thumbnail.jpg" width="50%">](https://youtu.be/A_DhKYVhOv8 "Click to play video") 

## Getting started
Sketches are no longer programmed with this library, but can be configured by combining different classes. How does it work? Basic idea is how an Arduino works: It combines inputs with actuators through logic. A sketch with ***Sketch made EASY*** is created in three steps:<BR>
<ol>
<li>Definition of the inputs</li>
<li>Definition of the actuators (outputs)</li>
<li>Definition of logic: </li>
  <ul>
    <li>Define at which value of an input something should happen (condition)</li>
    <li>Create a relation if the condition is true and specify the value of the actuator</li>    
  </ul>
</ol><BR>
There are many examples. The example directories contains a schema as well. Here the code of a toggling LED (the most common hello world example with Arduino). Open  "File:/Examples/SketchMadeEasy/Examples/04-ToggleingLed" into Arduino IDE to see full code.<BR>

```
  //((*** Initialize: Configure your sketch here....

  //** Create input:
  // Input changes value periodically and toggles between High and Low.
  Input* timer = new Timer(TIMER_INTERVAL_MSEC, true);

  //** Create actuator. 
  // A DigitalOutput knows the value On and Off.
  Actuator* led = new DigitalOutput(LED_PIN);

  //** Define logic with conditions and relations
  // Define relation when timer value changes to High
  Condition* conditionLedOn = new CompareCondition(timer, OpEQ, Timer::High);
  Relation* relationLedOn = new Relation1to1(conditionLedOn, led, FixValue::On());

  // Define relation when timer value changes to Low
  Condition* conditionLedOff = new CompareCondition(timer, OpEQ, Timer::Low);
  Relation* relationLedOff = new Relation1to1(conditionLedOff, led, FixValue::Off());
  // ***))
```

## Supported hardware (Classes)
|Inputs|Actuators|Logic|
| ------------- | ------------- |------------- |
|[Calculate](https://github.com/GSTCH/SketchMadeEASY/wiki/Class-Calculate)|[ActuatorCollection](https://github.com/GSTCH/SketchMadeEASY/wiki/Class-ActuatorCollection)|**Conditions**|
|[ConditionInput](https://github.com/GSTCH/SketchMadeEASY/wiki/Class-ConditionInput)|[Buzzer](https://github.com/GSTCH/SketchMadeEASY/wiki/Class-Buzzer)|[CompareCondition](https://github.com/GSTCH/SketchMadeEASY/wiki/Class-CompareCondition)|
|[DependentInput](https://github.com/GSTCH/SketchMadeEASY/wiki/Class-DependentInput)|[DigitalOutput](https://github.com/GSTCH/SketchMadeEASY/wiki/Class-DigitalOutput)|[ElseCondition](https://github.com/GSTCH/SketchMadeEASY/wiki/Class-ElseCondition)|
|[DigitalInput](https://github.com/GSTCH/SketchMadeEASY/wiki/Class-DigitalInput)|[EncodeModeI2C](https://github.com/GSTCH/SketchMadeEASY/wiki/Class-EncoderMotorI2C)|[LogicCondition](https://github.com/GSTCH/SketchMadeEASY/wiki/Class-LogicCondition)|
|[FixValue](https://github.com/GSTCH/SketchMadeEASY/wiki/Class-FixValue)|[EncoderMotorL298](https://github.com/GSTCH/SketchMadeEASY/wiki/Class-EncoderMotorL298)||
|[Inverter](https://github.com/GSTCH/SketchMadeEASY/wiki/Class-Inverter)|[EncoderMotorL9110](https://github.com/GSTCH/SketchMadeEASY/wiki/Class-EncoderMotorL9110)|**Relations**|
|[IteratorValue](https://github.com/GSTCH/SketchMadeEASY/wiki/Class-IteratorValue)|[MotorI2C](https://github.com/GSTCH/SketchMadeEASY/wiki/Class-MotorI2C)|[CrawlerSteering](https://github.com/GSTCH/SketchMadeEASY/wiki/Class-CrawlerSteering)|
|[JoystickAxis](https://github.com/GSTCH/SketchMadeEASY/wiki/Class-JoystickAxis)|[MotorL298](https://github.com/GSTCH/SketchMadeEASY/wiki/Class-MotorL298)|[Relation1to1](https://github.com/GSTCH/SketchMadeEASY/wiki/Class-Relation1to1)|
|[LoopSwitch](https://github.com/GSTCH/SketchMadeEASY/wiki/Class-LoopSwitch)|[MotorL9110](https://github.com/GSTCH/SketchMadeEASY/wiki/Class-MotorL9110)||
|[MonoFlop](https://github.com/GSTCH/SketchMadeEASY/wiki/Class-MonoFlop)|[MotorServo360I2C](https://github.com/GSTCH/SketchMadeEASY/wiki/Class-Servo360I2C)|**RemoteControls**|
|[Switch2Position](https://github.com/GSTCH/SketchMadeEASY/wiki/Class-Switch2Position)|[MotorServo360Pwm](https://github.com/GSTCH/SketchMadeEASY/wiki/Class-Servo360PWM)|[AppInventor](https://github.com/GSTCH/SketchMadeEASY/wiki/Class-AppInventor)|
|[Switch3Position](https://github.com/GSTCH/SketchMadeEASY/wiki/Class-Switch3Position)|[MotorServo360T1](https://github.com/GSTCH/SketchMadeEASY/wiki/Class-Servo360T1)|[FlySky](https://github.com/GSTCH/SketchMadeEASY/wiki/Class-FylSky)|
|[Timer](https://github.com/GSTCH/SketchMadeEASY/wiki/Class-Timer)|[MotorServo360T2](https://github.com/GSTCH/SketchMadeEASY/wiki/Class-Servo360T2)||
|[ToggleSwitch](https://github.com/GSTCH/SketchMadeEASY/wiki/Class-ToggleSwitch)|[MotorStepperRotate](https://github.com/GSTCH/SketchMadeEASY/wiki/Class-MotorStepperRotate)||
|[UltrasonicRangefinder](https://github.com/GSTCH/SketchMadeEASY/wiki/Class-UltrasonicRangefinder)|[MotorStepperRotateI2C](https://github.com/GSTCH/SketchMadeEASY/wiki/Class-MotorStepperRotateI2C)||
|[VariableInput](https://github.com/GSTCH/SketchMadeEASY/wiki/Class-VariableInput)|[ServoI2C](https://github.com/GSTCH/SketchMadeEASY/wiki/Class-ServoI2C)||
||[ServoPwm](https://github.com/GSTCH/SketchMadeEASY/wiki/Class-ServoPWM)||
||[ServoStepperPosition](https://github.com/GSTCH/SketchMadeEASY/wiki/Class-ServoStepperPosition)||
||[ServoStepperPositionI2C](https://github.com/GSTCH/SketchMadeEASY/wiki/Class-ServoStepperPositionI2C)||
||[ServoT1](https://github.com/GSTCH/SketchMadeEASY/wiki/Class-ServoT1)||
||[ServoT2](https://github.com/GSTCH/SketchMadeEASY/wiki/Class-ServoT2)||
||[VariableOutput](https://github.com/GSTCH/SketchMadeEASY/wiki/Class-VariableOutput)||


## Workboard
***Sketch made EASY*** contains not only software. A construction kit of different modules makes it possible to put together an individual workboard. With the STL files, these can be produced using a 3D printer.<BR>
<img src="https://github.com/GSTCH/SketchMadeEASY/blob/main/Resource/Images/Workboard/Uno+Breadboard.JPG" width="50%" height="50%" align="center">Workboard with Arduino Uno and Breadboard
<img src="https://github.com/GSTCH/SketchMadeEASY/blob/main/Resource/Images/Workboard/Testboard.JPG" width="60%" height="60%" align="center">My test board<BR>


## Documentation
See [Wiki](https://github.com/GSTCH/SketchMadeEASY/wiki) of this Repository
