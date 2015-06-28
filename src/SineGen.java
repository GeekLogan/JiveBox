public class SineGen implements SoundMachine {

    private int freq;
    private boolean active;

    public SineGen(int frequency) {
        this.freq = frequency;
        this.active = true; 
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
