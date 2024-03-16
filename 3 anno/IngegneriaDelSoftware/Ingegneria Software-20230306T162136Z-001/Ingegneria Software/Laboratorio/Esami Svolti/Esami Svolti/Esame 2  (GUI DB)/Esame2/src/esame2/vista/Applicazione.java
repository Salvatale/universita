package esame2.vista;

public interface Applicazione {
	public void pannelloStudenti();

	public boolean salva(int matricola, String cognome, String nome);
	
	public void esci();
}