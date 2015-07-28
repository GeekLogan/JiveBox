public class TuningFork {

    public static final double DEFAULT_CENTER_A = 440;
    public static final double A_STEP = Math.pow(2.0, 1.0 / 12.0);
    private double centerA; //value of A4

    public TuningFork() {
        this( DEFAULT_CENTER_A );
    }

    public TuningFork( double centerA ) {
        this.centerA = centerA;
    }

    public String toString() {
        return "Tuning Fork (Frequency: " + centerA + ")";
    }

    public double calculateSteps(int steps) {
        return centerA * Math.pow(A_STEP, (double) steps);
    }

    public static void main(String[] args) {
        //For testing only
        TuningFork test = new TuningFork();
        System.out.println(test.toString());

        int scale = 10;
        for(int i = -1 * scale; i <= scale; i++ ) {
            System.out.print(i);
            System.out.print(" -> ");
            System.out.println(test.calculateSteps(i));
        }

    }

}
