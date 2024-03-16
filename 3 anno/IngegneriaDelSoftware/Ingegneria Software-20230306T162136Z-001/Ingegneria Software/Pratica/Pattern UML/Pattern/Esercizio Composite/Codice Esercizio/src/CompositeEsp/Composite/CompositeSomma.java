package CompositeEsp.Composite;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import CompositeEsp.Numero.NumeroIntero;

public class CompositeSomma implements Espressione {
	private List<Espressione> children = new ArrayList<Espressione>();

	public CompositeSomma() {}
	
	public void add(Espressione Esp) {
		children.add(Esp);
	}

	public NumeroIntero operation() {
		Iterator<Espressione> i = children.iterator();
		NumeroIntero NumInt = ((Espressione) i.next()).operation();
		
		while (i.hasNext())
			NumInt = NumInt.somma(((Espressione) i.next()).operation());
		return NumInt;
	}
}