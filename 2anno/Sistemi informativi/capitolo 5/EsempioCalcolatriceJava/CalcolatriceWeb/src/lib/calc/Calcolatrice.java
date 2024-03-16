/**
 * 
 */
package lib.calc;

/**
 * @author gdestri
 *
 */
public class Calcolatrice {
	public static double somma(double p_oper1, double p_oper2) {
		return p_oper1 + p_oper2;
	}
	
	public static double sottrai(double p_oper1, double p_oper2) {
		return p_oper1 - p_oper2;
	}
	
	public static double moltiplica(double p_oper1, double p_oper2) {
		return p_oper1 * p_oper2;
	}
	
	public static double dividi(double p_oper1, double p_oper2) {
		if (p_oper2 == 0.0) {
			return Double.POSITIVE_INFINITY;
		}
		else {
			return p_oper1 / p_oper2;
		}
	}
}
