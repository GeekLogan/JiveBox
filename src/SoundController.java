import javax.sound.sampled.*;
import java.lang.Thread;
import java.util.*;

public class SoundController extends Thread {

    /*
        Numeric constants
    */
    public static final int MAX_SCALE = 32767;
    public static final int MIN_SCALE = -1 * MAX_SCALE;
    public static final int ZERO = 0;
    public static final int sampleRate = 44100;
    public static final double PI = Math.PI;
    public static final double TAU = 2 * PI;
    public static final int sectioning = 2;
    public static final int BLOCK_SIZE = sampleRate / sectioning;
    public static final double BLOCK_TIME_SIZE = 1000 / sectioning;

    /*
        Variables for sound use
    */
    private AudioFormat format;
    private SourceDataLine dataLine;
    private short[] bufferIn;
    private byte[] bufferOut;

    /*
        Interface variables
    */
    public ArrayList<SoundMachine> soundStack;
    public KeyStatus keys;
    private boolean stop, isStopped;

    /*
        Default Constructor
    */
    public SoundController() {
        // sample rate, bit rate, channels, signed, bigEndian
        format = new AudioFormat( (float) sampleRate, 8 * 2, 1, true, false);
        bufferIn = new short[BLOCK_SIZE];
        bufferOut = new byte[BLOCK_SIZE * 2];
        soundStack = new ArrayList<SoundMachine>();

        stop = false;
        isStopped = false;

        DataLine.Info info = new DataLine.Info(SourceDataLine.class, format);
        if (!AudioSystem.isLineSupported(info)) {
            System.err.println("Line matching " + info + " is not supported.");
        }

        try {
            dataLine = (SourceDataLine) AudioSystem.getLine(info);
        } catch( LineUnavailableException e ) {
            System.err.println("Failed to Get Sound Stream!");
            e.printStackTrace();
            System.exit(2);
        }

        try{
            dataLine.open(format);
            dataLine.start();
            try{
                Thread.sleep(50);
            } catch (Exception e) {
                System.err.println("Startup Timing Failed... (Will Continue Without)");
            }
        } catch( LineUnavailableException e ) {
            System.err.println("Failed to Start Data Stream!");
            e.printStackTrace();
            System.exit(3);
        }

        keys = new KeyStatus();
        this.start();
    }

    /*
        Getter method for key status.
    */
    public KeyStatus getKeys() {
        return keys;
    }

    /*
        Sound runner loop.
    */
    public void run() {
        System.out.println("Starting Sound Thread...");
        double time = 0;
        double timed = 1.0 / sampleRate;
        while(!stop) { //cylcles indefinately
            for(int i = 0; i < sampleRate && !stop; i++) { //cylces per second
                time += timed; //time ticks on
                int index = i % BLOCK_SIZE;
                double soundBlock = 0; //the value for time unit

                if(soundStack.size() > 0) {
                    int count = 0; //count of number of concurrent tracks
                    try{
                        for(SoundMachine a : soundStack) {
                            try {
                                if(a.isActive()) {
                                    soundBlock += a.genSound(time);
                                    count++;
                                }
                            } catch(NullPointerException e) {
                                //Sideeffect of ConcurrentModificationException
                                throw new ConcurrentModificationException();
                            }
                        }
                    } catch(ConcurrentModificationException e) {
                        System.err.println("Concurrent Error... (Noncritical)");
                    }
                    soundBlock /= count; //scale the block down to the [-1,1] range
                    soundBlock *= MAX_SCALE; //scale up to the data range
                }

                bufferIn[index] = (short) soundBlock; //downsample to short

                if(index == 0) {
                    syncBuffer(); //transfer in buffer => out buffer
                    flushBuffer(); //clear out buffer to sound card
                }
            }
        }
        isStopped = true;
    }

    /*
        Copies the in buffer -> out buffer.
        This includes short -> byte downsample.
    */
    private void syncBuffer() {
        for(int i = 0; i < bufferIn.length; i++) {
            int index = i * 2;
            bufferOut[index] = (byte)(bufferIn[i] & 0xff);
            index++;
            bufferOut[index] = (byte)((bufferIn[i] >> 8) & 0xff);
        }
    }

    /*
        Copies out buffer -> sound buffer.
    */
    private void flushBuffer() {
        dataLine.write(bufferOut, 0, bufferOut.length);
    }

    /*
        Safely stop the sound thread
    */
    private void stop_clean() {
        this.stop = true;
        while(!this.isStopped);
    }

    /*
        (NOT CURRENTLY USED)
        Closes the sound device properly.
    */
    public void close() {
        this.stop_clean();
        try{
            dataLine.drain();
            dataLine.stop();
        } catch( Exception e ) {
            System.err.println("Failed to Close Audio Device");
        }
    }
}
