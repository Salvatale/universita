/**
 * 
 */
package lib.adapter;

/**
 * @author gdestri
 *
 */
public class ConvertitoreTipo {
	/**
	 * Converte da double a String
	 * @param p_valore
	 * @return String valore convertito
	 */
	public static String doubleToString(double p_valore) {
		return Double.toString(p_valore);
	} // end method
	
	/**
	 * Converte da String a double
	 * @param p_valore
	 * @return double valore convertito in double
	 */
	public static double stringToDouble(String p_valore) {
		double ris = 0.0;
		if (p_valore == null) {
			return ris;
		}
		
		try {
			ris = Double.parseDouble(p_valore);
		} 
		catch (NumberFormatException nfe) {
			// TODO: handle exception
		}
		catch (Exception e) {
			// TODO: handle exception
		}
		return ris;
		
	} // end method
} // end class
