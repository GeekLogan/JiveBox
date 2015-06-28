public class SawtoothGen implements SoundMachine {

    private int freq;
    private boolean active;

    public SawtoothGen(int frequency) {
        this.freq = frequency;
        this.active = true;
    }

    public double genSound(double time) {
        /*
        double sawtooth_synth(double t, int wavefreq) {
            double out = t * wavefreq;
            out = (out - floor(0.5 + out));
            out = gain_filter_lossless(out, 2.0);
            return out;
        }
        return Math.sin( time * freq * SoundController.TAU );
        */
        double out = time * this.freq;
        out = (out - Math.floor(0.5 + out));
        out *= 2;
        return out;
    }

    public boolean isActive() {
        return active;
    }

    public void setActive(boolean in) {
        active = in;
    }

}
