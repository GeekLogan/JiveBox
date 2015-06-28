public class FMGen extends SoundMachine2 {

    protected int freq2;

    public FMGen(int frequency1, int frequency2) {
        super(frequency1);
        this.freq2 = frequency2;
    }

    public double genSound(double time) {
        double seed1 = time * SoundController.TAU;
        double seed2 = seed1;
        seed1 *= this.freq;
        seed2 *= this.freq2;
        double out = Math.sin(seed1 + Math.sin(seed2));
        return out;
    }

}
