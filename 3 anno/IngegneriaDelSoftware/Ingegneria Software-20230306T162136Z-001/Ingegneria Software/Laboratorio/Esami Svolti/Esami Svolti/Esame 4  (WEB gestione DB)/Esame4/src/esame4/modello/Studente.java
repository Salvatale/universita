package esame4.modello;

public class Studente {
	public int matricola;
	public String nome;
	public String cognome;
	public String dataNascita;
	
	public Studente(int matricola, String nome, String cognome, String dataNascita) {
		this.matricola = matricola;
		this.nome = nome;
		this.cognome = cognome;
		this.dataNascita = dataNascita;
	}
	
	public int getMatricola() {
		return matricola;
	}
	public void setMatricola(int matricola) {
		this.matricola = matricola;
	}
	public String getNome() {
		return nome;
	}
	public void setNome(String nome) {
		this.nome = nome;
	}
	public String getCognome() {
		return cognome;
	}
	public void setCognome(String cognome) {
		this.cognome = cognome;
	}
	public String getDataNascita() {
		return dataNascita;
	}
	public void setDataNascita(String dataNascitaString) {
		this.dataNascita = dataNascitaString;
	}
	
	
}
