# LaserHarph
This project was made for event called "Festival of Science and art in Poznan". This code was used to detect that user has played one of the laser strings.
Code was implemented for Arduino MEGA. 

The Laser Harph looked like this:
L1 ------------------- D1
L2 ------------------- D2
L3 ------------------- D3
...
LX ------------------- DX

Where L mean Laser and D means Fotodiod (Detector)
Those Detectors was connected via 3 multiplexers and values of those was next interpretated by software on Arduino.
To make thath happen program starts with calibration. The lights of lasers are turned off and the mesurment of the light is carried out.
With the new avrage level of light for each detector is set, the lasers are turned on again. 
So when user cross the laser beam there is a diffrance betwean activation level and avrage level. This diffrence is detected as activation.
When activation ocours software sends an string via Serial with information about which laser string was activated.
