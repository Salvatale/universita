package CompositeEsp.Client;

import CompositeEsp.Composite.CompositeProdotto;
import CompositeEsp.Composite.CompositeSomma;
import CompositeEsp.Composite.Leaf;
import CompositeEsp.Numero.NumeroIntero;
import CompositeEsp.Numero.NumeroInteroImpl;

public class Client {

	public static void main(String[] args) {
		// Ipotizzo di dover fare la seguete espressione: 1 + 2 * 3 * 4 +5 * 6
		
		// Variabili che rappresentano i numeri dell'equazione:
		NumeroIntero N1 = new NumeroInteroImpl(1);
		NumeroIntero N2 = new NumeroInteroImpl(2);
		NumeroIntero N3 = new NumeroInteroImpl(3);
		NumeroIntero N4 = new NumeroInteroImpl(4);
		NumeroIntero N5 = new NumeroInteroImpl(5);
		NumeroIntero N6 = new NumeroInteroImpl(6);
		
		// (2 * 3 * 4)
		CompositeProdotto P1 = new CompositeProdotto();
		P1.add( new Leaf( N2 ) );
		P1.add( new Leaf( N3 ) );
		P1.add( new Leaf( N4 ) );
		
		// (5 * 6)
		CompositeProdotto P2 = new CompositeProdotto();
		P2.add( new Leaf( N5 ) );
		P2.add( new Leaf( N6 ) );
		
		// ( 1 + (2 * 3 * 4) + (5 * 6) )
		CompositeSomma S = new CompositeSomma();
		S.add( new Leaf( N1 ) );
		S.add( P1 );
		S.add( P2 );
		
		// Risultato
		NumeroIntero risultato = S.operation();
		System.out.println(risultato.getValore());  // 55
	}

}
