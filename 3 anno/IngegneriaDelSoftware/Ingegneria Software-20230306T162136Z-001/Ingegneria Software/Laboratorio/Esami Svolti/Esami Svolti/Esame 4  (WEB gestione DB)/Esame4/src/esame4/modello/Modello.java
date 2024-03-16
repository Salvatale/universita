package esame4.modello;

import java.util.List;

public interface Modello {
	public List<Studente> ricaricaStudenti();
	public boolean modificaStudente(Studente studente);
	public boolean aggiungiStudente(Studente studente);
	public boolean rimuoviStudente(int matricola);
	public Studente caricaDati(int matricola);
}
