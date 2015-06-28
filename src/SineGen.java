public class SineGen implements SoundMachine {

    private int freq = 400;
    private boolean active = true;

    public SineGen(int frequency) {
        this.freq = frequency;
    }

    public double genSound(double time) {
        return Math.sin( time * freq * SoundController.TAU );
    }

    public boolean isActive() {
        return active;
    }

    public void setActive(boolean in) {
        active = in;
    }

}
