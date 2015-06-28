public class SineGen extends SoundMachine2 {

    public SineGen(int frequency) {
        super(frequency);
    }

    public double genSound(double time) {
        return Math.sin( time * freq * SoundController.TAU );
    }

}
