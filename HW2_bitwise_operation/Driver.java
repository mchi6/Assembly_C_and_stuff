public class Driver {
	public static void main (String[] args) {
		String number = "32";
		String number2 = "111";
		String number3 = "A6";
		int number4 = 7;
		int number5 = 166;
		int num = HW2Bases.strdtoi(number);
		int num2 = HW2Bases.strbtoi(number2);
		int num3 = HW2Bases.strxtoi(number3);
		String num4 = HW2Bases.itostrb(number4);
		String num5 = HW2Bases.itostrx(number5);
		System.out.println("decimal:" + num);
		System.out.println("binary:" + num2);
		System.out.println("hexadecimal:" + num3);
		System.out.println("int:" + num4);
		System.out.println("int:" + num5);

		int newInt = HW2Operations.setByte(0xAAA5BBC6, 0x17, 1);
		System.out.printf("%X\n", newInt);
		newInt = HW2Operations.getNibble(0xFF254545, 7);
		System.out.printf("%1X\n", newInt);
		newInt = HW2Operations.pack(0x12, 0x34, 0x56, 0x78);
		System.out.printf("%1X\n", newInt);
		int answer = HW2Operations.abs(0x00001234, 13);
		System.out.printf("%1X\n", answer);
		System.out.println(HW2Operations.powerOf2(1));
	}
}