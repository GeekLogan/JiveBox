public class JiveBox {

	private static SoundController soundOut;

	public static void main(String[] args) {
		soundOut = new SoundController();
		System.out.println("Time Marker A!");
		pause(2000);
		System.out.println("Time Marker B!");
		for(int i = 0; true; i++) {
			for(int g = 0; g < soundOut.soundStack.size(); g++) {
				soundOut.soundStack.get(g).setActive(false);
			}
	        soundOut.soundStack.add(new SawtoothGen(80 + 10 * i));
			soundOut.soundStack.add(new SawtoothGen(80 + 10 * i + i));
			pause(2000);
			System.out.println("Time Marker C! (" + i * 10 + ")" );
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
