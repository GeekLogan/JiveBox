public class VolumeCielFilter extends FilterMachine2 {

    private double lim;

    public VolumeCielFilter(double limit) {
        this.lim = limit;
    }

    public double processSound(double in) {
        if(in > this.lim) in = this.lim;
        return in;
    }

}
