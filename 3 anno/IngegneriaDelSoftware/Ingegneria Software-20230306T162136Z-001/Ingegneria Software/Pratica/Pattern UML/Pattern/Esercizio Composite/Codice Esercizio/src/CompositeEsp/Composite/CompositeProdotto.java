package CompositeEsp.Composite;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import CompositeEsp.Numero.NumeroIntero;

public class CompositeProdotto implements Espressione{
	public List<Espressione> children = new ArrayList<Espressione>();

	public CompositeProdotto() {}

	public void add(Espressione Esp) {
		children.add(Esp);
	}

	public NumeroIntero operation() {
		// Ipotizzo che la lista abbia sempre almeno due Espressioni
		// (non gestisco i casi limite di lista vuota o con un solo elemento)
		Iterator<Espressione> i = children.iterator();
		NumeroIntero NumInt = ((Espressione) i.next()).operation(); // Primo elemento della lista
		
		while (i.hasNext())
			NumInt = NumInt.prodotto(((Espressione) i.next()).operation());
		return NumInt;
	}
}
