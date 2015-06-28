public class SawtoothGen extends SoundMachine2 {

    public SawtoothGen(int frequency) {
        super(frequency);
    }

    public double genSound(double time) {
        double out = time * this.freq;
        out -= Math.floor(0.5 + out);
        out *= 2;
        return out;
    }

}
