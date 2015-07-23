# JiveBox

###1. Project Goals
JiveBox seeks to build a modular Java-based synthesizer that can be used for music production.

###2. License
All code is licensed under the GNU General Public License,
which is attached in the source code folder.  

###3. Build Target
The program is written using Sun Java 7 SE, and will not run correctly under OpenJDK.

The RaspberryPi DVR777 interface is written using the following libraries on the C99 code standard:

1. WiringPi

2. Linux UInput (the code assumes uinput device at /dev/uinput)

###4. Example running command
``
./JiveBoard #must be run in background or another terminal
``

``
java JiveBox #runs actual program
``

###5. Control Interface
