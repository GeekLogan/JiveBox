public interface SoundMachine {

    //MUST RETURN FROM -1 TO 1 DOUBLE
    public double genSound(double time);
    public boolean isActive();
    public void setActive(boolean in);

}
