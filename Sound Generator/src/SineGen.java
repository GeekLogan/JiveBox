public class SineGen extends SoundMachine2 {

    double startTime;

    public SineGen(double frequency) {
        super(frequency);
        startTime = 0;
    }

    public double genSound(double time) {
	if(startTime == 0) startTime = time;
        return Math.sin( (time - startTime) * freq * SoundController.TAU );
    }

}
