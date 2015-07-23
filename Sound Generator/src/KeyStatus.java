public class KeyStatus {

	private boolean[] keys;
	private SoundController soundOut;

	public KeyStatus( SoundController sc ) {

		soundOut = sc;
		keys = new boolean[32];

	}

	public void processCommand(char cmd, char key) {
		byte id = keyId(key);

		if(JiveBox.DEBUG) {
			String cmd_name = "Error";
			if(cmd == 'u') cmd_name = "Released";
			if(cmd == 'd') cmd_name = "Pressed";
			System.out.println("Command -> " + cmd_name + " : " + key + " [" + id + ']');
		}

		if(id < 0 || id > 31) return; //bad id

		/* do stuff here */

	}

	//The following method maps the inter-program codes back to
	//DVR777 codes
	protected byte keyId(char in) {
		switch(in) {
			case 'a': return 26;
			case 'b': return 24;
			case 'c': return 28;
			case 'd': return 30;
			case 'e': return 18;
			case 'f': return 16;
			case 'g': return 20;
			case 'h': return 22;
			case 'i': return 25;
			case 'j': return 27;
			case 'k': return 29;
			case 'l': return 31;
			case 'm': return 17;
			case 'n': return 19;
			case 'o': return 21;
			case 'p': return 23;
			case 'q': return 10;
			case 'r': return 8;
			case 's': return 12;
			case 't': return 14;
			case 'u': return 2;
			case 'v': return 1;
			case 'w': return 9;
			case 'x': return 11;
			case 'y': return 13;
			case 'z': return 15;
			case '0': return 4;
			case '1': return 0;
			case '2': return 3;
			case '3': return 6;
			case '4': return 5;
			case '5': return 7;
		}
		return -1;
	}

}
