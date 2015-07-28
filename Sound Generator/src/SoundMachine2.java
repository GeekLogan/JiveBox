public abstract class SoundMachine2 implements SoundMachine {

    protected double freq;
    protected boolean active;

    public SoundMachine2(double frequency) {
        this.freq = frequency;
        this.active = true;
    }

    public double genSound() {
        return 0;
    }

    public boolean isActive() {
        return active;
    }

    public void setActive(boolean in) {
        this.active = in;
    }

    public void setFrequency(double frequency) {
        this.freq = frequency;
    }

}
