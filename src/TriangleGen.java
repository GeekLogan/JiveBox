public class TriangleGen extends SoundMachine2 {

    private SawtoothGen seed;

    public TriangleGen(int frequency) {
        super(frequency);
        seed = new SawtoothGen( frequency );
    }

    public double genSound(double time) {
        double out = seed.genSound(time);
        if(out < 0) out *= -1;
        out *= 2;
        out -= 1;
        return out;
    }

}
