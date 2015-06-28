public interface FilterMachine {

    //MUST RETURN FROM -1 TO 1 DOUBLE
    public double processSound(double in);
    public boolean isActive();
    public void setActive(boolean in);

}
