package CompositeEsp.Composite;

import CompositeEsp.Numero.NumeroIntero;

public class Leaf implements Espressione {
	public NumeroIntero NumInt;

	public Leaf(NumeroIntero n) {
		NumInt = n;
	}

	public NumeroIntero operation() {
		return NumInt;
	}
}
