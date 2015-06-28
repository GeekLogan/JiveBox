import javax.sound.sampled.*;
import java.lang.Thread;
import java.util.*;

public class SoundController extends Thread {

    public static final int MAX_SCALE = 32767;
    public static final int MIN_SCALE = -1 * MAX_SCALE;
    public static final int ZERO = 0;
    public static final int sampleRate = 44100;
    public static final double PI = Math.PI;
    public static final double TAU = 2 * PI;
    public static final int sectioning = 2;
    public static final int BLOCK_SIZE = sampleRate / sectioning;
    public static final double BLOCK_TIME_SIZE = 1000 / sectioning;

    private AudioFormat format;
    private SourceDataLine dataLine;
    private short[] bufferIn;
    private byte[] bufferOut;

    public ArrayList<SoundMachine> soundStack;
    public KeyStatus keys;

    public SoundController() {
        // sample rate, bit rate, channels, signed, bigEndian
        format = new AudioFormat( (float) sampleRate, 8 * 2, 1, true, false);
        bufferIn = new short[BLOCK_SIZE];
        bufferOut = new byte[BLOCK_SIZE * 2];
        soundStack = new ArrayList<SoundMachine>();

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
                System.err.println("Startup Timing Failed...");
            }
        } catch( LineUnavailableException e ) {
            System.err.println("Failed to Start Data Stream!");
            e.printStackTrace();
            System.exit(3);
        }

        keys = new KeyStatus();
        this.start();
    }

    public KeyStatus getKeys() {
        return keys;
    }

    public void run() {
        System.out.println("Starting Sound Thread...");
        while(true) {
            for(int i = 0; i < sampleRate; i++) {
                int index = i % BLOCK_SIZE;
                double soundBlock = 0;

                if(soundStack.size() > 0) {
                    int count = 0;
                    double time = i;
                    time /= sampleRate * 1.0;
                    try{
                        for(SoundMachine a : soundStack) {
                            try {
                                if(a.isActive()) {
                                    soundBlock += a.genSound(time);
                                    count++;
                                }
                            } catch(NullPointerException e) {
                                
                            }
                        }
                    } catch(ConcurrentModificationException e) {
                        System.err.println("Concurrent Error...");
                    }
                    soundBlock /= count;
                    soundBlock *= MAX_SCALE;
                    soundBlock *= 0.985; //anti-clip filter
                }

                bufferIn[index] = (short) soundBlock;

                if(index == 0) {
                    syncBuffer();
                    flushBuffer();
                }
            }
        }
    }

    private void syncBuffer() {
        for(int i = 0; i < bufferIn.length; i++) {
            int index = i * 2;
            bufferOut[index] = (byte)(bufferIn[i] & 0xff);
            index++;
            bufferOut[index] = (byte)((bufferIn[i] >> 8) & 0xff);
        }
    }

    private void flushBuffer() {
        dataLine.write(bufferOut, 0, bufferOut.length);
    }

    public void close() {
        try{
            dataLine.drain();
            dataLine.stop();
        } catch( Exception e ) {
            System.err.println("Failed to Close Audio Device");
        }
    }
}
