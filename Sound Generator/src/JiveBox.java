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
