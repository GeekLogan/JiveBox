public class DoubleSineGen implements SoundMachine {

    private int freq = 400;
    private int off = 1;
    private boolean active = true;

    public DoubleSineGen(int frequency, int offset) {
        this.freq = frequency;
        this.off = offset;
    }

    public double genSound(double time) {
        double tmp = Math.sin( time * freq * SoundController.TAU );
        tmp += Math.sin( time * (freq + off) * SoundController.TAU );
        tmp /= 2;
        return tmp;
    }

    public boolean isActive() {
        return active;
    }

    public void setActive(boolean in) {
        active = in;
    }

}
