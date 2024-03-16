package esame2.modello;

import java.util.List;

public interface Modello {
	public List<Studente> ricaricaStudenti();
	public boolean modificaStudente(Studente studente); 
}
