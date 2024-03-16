/**
 * 
 */
package lib.adapter;

import lib.calc.*;

/**
 * @author gdestri
 *
 */
public class CalcolatriceAdapter {

	public static String somma(String p_oper1, String p_oper2) {
		double oper1 = ConvertitoreTipo.stringToDouble(p_oper1);
		double oper2 = ConvertitoreTipo.stringToDouble(p_oper2);
		
		double ris = Calcolatrice.somma(oper1, oper2);
		
		return ConvertitoreTipo.doubleToString(ris);
	}
	
	
	public static String sottrai(String p_oper1, String p_oper2) {
		double oper1 = ConvertitoreTipo.stringToDouble(p_oper1);
		double oper2 = ConvertitoreTipo.stringToDouble(p_oper2);
		
		double ris = Calcolatrice.sottrai(oper1, oper2);
		
		return ConvertitoreTipo.doubleToString(ris);
	}
	
	public static String moltiplica(String p_oper1, String p_oper2) {
		double oper1 = ConvertitoreTipo.stringToDouble(p_oper1);
		double oper2 = ConvertitoreTipo.stringToDouble(p_oper2);
		
		double ris = Calcolatrice.moltiplica(oper1, oper2);
		
		return ConvertitoreTipo.doubleToString(ris);
	}
	
	public static String dividi(String p_oper1, String p_oper2) {
		double oper1 = ConvertitoreTipo.stringToDouble(p_oper1);
		double oper2 = ConvertitoreTipo.stringToDouble(p_oper2);
		
		double ris = Calcolatrice.dividi(oper1, oper2);
		
		return ConvertitoreTipo.doubleToString(ris);
	}

} // end class
