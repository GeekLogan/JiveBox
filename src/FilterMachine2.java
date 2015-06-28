public abstract class FilterMachine2 implements FilterMachine {

    protected boolean active;

    public FilterMachine2(int frequency) {
        
    }

    public double processSound(double in) {
        return in;
    }

    public boolean isActive() {
        return active;
    }

    public void setActive(boolean in) {
        active = in;
    }

}
