package esame2.modello;

public class Studente {
	int matricola;
	String cognome;
	String nome;
	
	public Studente(int matricola, String cognome, String nome) {
		this.matricola = matricola;
		this.cognome = cognome;
		this.nome = nome;
	}

	public int getMatricola() {
		return matricola;
	}

	public void setMatricola(int matricola) {
		this.matricola = matricola;
	}

	public String getCognome() {
		return cognome;
	}

	public void setCognome(String cognome) {
		this.cognome = cognome;
	}

	public String getNome() {
		return nome;
	}

	public void setNome(String nome) {
		this.nome = nome;
	}
	
	
}
