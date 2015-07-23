import java.util.ArrayList;
import java.io.*;

public class JiveBox {

	public static final boolean DEBUG = true;

	private static SoundController soundOut;
	private static KeyStatus keys;

	public static void main(String[] args) {

		soundOut = new SoundController();
		keys = new KeyStatus( soundOut );

		pause(500);

		/*
		System.out.println("Time Marker A!");
		pause(2000);
		System.out.println("Time Marker B!");
		for(int i = 0; true; i++) {
			for(int g = 0; g < soundOut.soundStack.size(); g++) {
				soundOut.soundStack.get(g).setActive(false);
			}
	        //soundOut.soundStack.add(new FMGen(80 + 10 * i, 100 + 10 * i));
			soundOut.soundStack.add(new FMGen(40, 90));
			//soundOut.soundStack.add(new FMGen(80 + 10 * i + i));
			pause(2000);
			System.out.println("Time Marker C! (" + i * 10 + ")" );
		}
		*/
		BufferedReader br = new BufferedReader( new InputStreamReader(System.in) );

		while(true) {

			try {
				char cmd = br.readLine().charAt(0);
				char key = br.readLine().charAt(0);
				keys.processCommand(cmd, key);
			} catch (IOException e ) {
				e.printStackTrace();
			}

		}
	}

	public static void pause(int time) {
		try{
			Thread.sleep(time);
		} catch (Exception e) {
			//Do nothing
		}
	}
}
