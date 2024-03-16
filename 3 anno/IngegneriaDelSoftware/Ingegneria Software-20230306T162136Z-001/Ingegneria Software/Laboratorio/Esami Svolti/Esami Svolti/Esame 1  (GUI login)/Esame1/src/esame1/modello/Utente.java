package esame1.modello;

public class Utente {
	String nome;
	String password;
	
	public Utente(String nome, String password) {
		this.nome = nome;
		this.password = password;
	}
	
	public String getNome() {
		return nome;
	}
	public void setNome(String nome) {
		this.nome = nome;
	}
	public String getPassword() {
		return password;
	}
	public void setPassword(String password) {
		this.password = password;
	}
}
