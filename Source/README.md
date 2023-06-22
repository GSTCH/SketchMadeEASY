Arduino Easy 
This libary is an abstraction of an Arduino sketch on logic level. 
Instead of programming in bits and bytes, the control logic is configured by combining the classes.
The heard is the ControlManager class. An object is mandatory. 
Then create the object of the input, action, relation and condition classes.
Add a reference of each object to the control manager.
There are an amount of example to see how easy this library is to use
There's an "ArduinoEasy RemoteControl" on "MIT AppInventor". This app allows to control four elements over bluetooth.

This is the first published version, a higher beta.


Version 0.6.5.4
***************
First internal published version.

Version 0.7.1.0
***************
- Hidden all not necessary code from the user
  - ControlManager completly hidden
  - ID is now optional
- New classes
  - Servo
  - UltrasonicRangefinder
  - StepperPosition
  - StepperRotate
- New use cases
  - 
- New tests
  -
  