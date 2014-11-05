/**
 * CS 2110 Fall 2014 HW2
 * Part 1 - Coding with bases
 * @author Dan Sun
 * 
 * *** NOTE: The rules are different for each java file! ***
 *
 * You may not use any of the following:
 * - Any functions found in Java libraries (especially the Math library)
 *     - Example Math.pow, Integer.bitCount, String.valueOf, etc.
 *     - Basically, any function that does everything for you. The purpose of this
 *       homework is to learn how to do these operations yourself, and the Java API!
 *     - The only exception to this rule is String.charAt to get a character from a
 *       String, and you may use String.length to get the size of the string.
 *     - Any Java 7 feature / standard library function (we will be grading using Java 6)
 *     
 * - You my not implement any Java library functions as helpers to use in other functions.
 *     
 * - String concatenation with a number for more than one digit.
 *     - For example, "" + 123 is banned. "" + 6 is allowed, though.
 *     
 * - You may only use 2 conditionals in if-else clauses max per function.
 *     - This means you may have 2 separate conditions, making this okay:
 *     
 *     if(cond1) {
 *         code;
 *     } else {
 *         moreCode;
 *     }
 *     if(cond2) {
 *         code;
 *     } else {
 *         modeCode;
 *     }
 *     
 * - You may not use a switch statement.
 * - No nested for-loops! This is completely doable with one level of looping.
 * - Recursion is not allowed.
 * - You may not reuse any function to implement another function.
 */
public class HW2Bases
{
	/**
	 * strdtoi - Decimal String to int
	 *
	 * Convert a string containing ASCII characters (in decimal) to an int.
	 * You do not have to handle negative numbers. The Strings we will pass in will be
	 * valid decimal numbers, and able to fit in a 32-bit signed integer.
	 * 
	 * Example: strdtoi("123"); // => 123
	 */
	public static int strdtoi(String decimal)
	{
		int i = 0;
		int num = 0;
		while (i < decimal.length()) {
			num *= 10;
			num += decimal.charAt(i++) - '0'; //convert a string representation of a digit to a digit by minus '0'
		}	
		return num;
	}

	/**
	 * strbtoi - Binary String to int
	 *
	 * Convert a string containing ASCII characters (in binary) to an int.
	 * You do not have to handle negative numbers. The Strings we will pass in will be
	 * valid binary numbers, and able to fit in a 32-bit signed integer.
	 * 
	 * Example: strbtoi("111"); // => 7
	 */
	public static int strbtoi(String binary)
	{
		int i = 0;
		int num = 0;
		while (i < binary.length()) {
			num *= 2;
			num += binary.charAt(i++) - '0'; //convert a string representation of a binary to a binary by minus '0'
		}	
		return num;
	}

	/**
	 * strxtoi - Hexadecimal String to int
	 *
	 * Convert a string containing ASCII characters (in hex) to an int.
	 * You do not have to handle negative numbers. The Strings we will pass in will be
	 * valid hexadecimal numbers, and able to fit in a 32-bit signed integer.
	 * 
	 * Example: strxtoi("A6"); // => 166
	 */
	public static int strxtoi(String hex)
	{
		int i = 0;
		int num = 0;
		while (i < hex.length()) {
			num *= 16;
			// if a digit of the hex is between 0 to 9
			if (hex.charAt(i) >= '0' && hex.charAt(i) <= '9') {
				num += hex.charAt(i) - '0';//convert a string representation of a digit to a digit by minus '0'
			}
			// if a digit of the hex is larger than 9
			if (hex.charAt(i) == 'A') {
				num += 10;
			}
			if (hex.charAt(i) == 'B') {
				num += 11;
			}
			if (hex.charAt(i) == 'C') {
				num += 12;
			}
			if (hex.charAt(i) == 'D') {
				num += 13;
			}
			if (hex.charAt(i) == 'E') {
				num += 14;
			}
			if (hex.charAt(i) == 'F') {
				num += 15;
			}
			i++;
		}	
		return num;
	}

	/**
	 * itostrb - int to Binary String
	 *
	 * Convert a int into a String containing ASCII characters (in binary).
	 * You do not have to handle negative numbers.
	 * The String returned should contain the minimum number of characters necessary to
	 * represent the number that was passed in.
	 * 
	 * Example: itostrb(7); // => "111"
	 */
	public static String itostrb(int binary)
	{
		int num = binary;
		if (num == 0) {
			return "0";
		}
		String bin = "";
		while (num > 0) {
			int remainder = num % 2; // get the remainder
			char remChar = (char) (remainder + '0');
			bin = remChar + bin; // concatenate the remainders
			num = num / 2; // get the quotient
		}
		return bin;
	}

	/**
	 * itostrx - int to Hexadecimal String
	 *
	 * Convert a int into a String containing ASCII characters (in hexadecimal).
	 * You do not have to handle negative numbers.
	 * The String returned should contain the minimum number of characters necessary to
	 * represent the number that was passed in.
	 * 
	 * Example: itostrx(166); // => "A6"
	 */
	public static String itostrx(int hex)
	{
		int num = hex;
		if (num == 0) {
			return "0";
		}
		String hexadecimal = "";
		// define a hex table
		String[] hexTable = {"0", "1", "2", "3",
					"4", "5", "6", "7",
					"8", "9", "A", "B", 
					"C", "D", "E", "F"};
		while (num > 0) {
			int remainder = num % 16;
			String remStr = hexTable[remainder];
			hexadecimal = remStr + hexadecimal;
			num = num / 16;
		}
		return hexadecimal;
	}
}

