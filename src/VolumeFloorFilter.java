public class VolumeFloorFilter extends FilterMachine2 {

    private double lim;
    
    public VolumeFloorFilter(double limit) {
        this.lim = limit;
    }

    public double processSound(double in) {
        if(in < this.lim) in = this.lim;
        return in;
    }

}
