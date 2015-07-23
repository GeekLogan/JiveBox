all:
	make main
	make synth
	make filter

main:
	javac -d ../bin JiveBox.java
	javac -d ../bin SoundController.java
	javac -d ../bin KeyStatus.java

synth:
	javac -d ../bin SoundMachine.java
	javac -d ../bin SoundMachine2.java
	javac -d ../bin SineGen.java
	javac -d ../bin SawtoothGen.java
	javac -d ../bin TriangleGen.java
	javac -d ../bin FMGen.java

filter:
	javac -d ../bin FilterMachine.java
	javac -d ../bin FilterMachine2.java
	javac -d ../bin VolumeCielFilter.java
	javac -d ../bin VolumeFloorFilter.java