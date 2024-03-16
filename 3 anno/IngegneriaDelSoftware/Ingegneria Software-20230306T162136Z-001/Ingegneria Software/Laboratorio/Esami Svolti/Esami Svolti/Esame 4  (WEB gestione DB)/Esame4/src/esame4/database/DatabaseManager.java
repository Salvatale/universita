package esame4.database;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;
import java.util.ResourceBundle;

import esame4.modello.Modello;
import esame4.modello.Studente;

public class DatabaseManager implements Modello{
	protected String url;
	
	public DatabaseManager() {
		try {
			ResourceBundle resourceBundle = ResourceBundle.getBundle("configurazione");
			String clazz = resourceBundle.getString("database.class");
			url = resourceBundle.getString("database.url");
			Class.forName(clazz);
		} catch(Throwable throwable) {
			throwable.printStackTrace();
		}
	}
	
	@Override
	public List<Studente> ricaricaStudenti() {
		List<Studente> studenti = new ArrayList<Studente>();
		Connection connessione = null;
		PreparedStatement statement = null;
		ResultSet resultSet = null;
		
		try {
			connessione = connetti();
			statement = connessione.prepareStatement("SELECT * FROM STUDENTE");
			resultSet = statement.executeQuery();
			
			while(resultSet.next()) {
				Studente studente = new Studente(resultSet.getInt("MATRICOLA"), resultSet.getString("NOME"), resultSet.getString("COGNOME"), resultSet.getString("NASCITA"));
				studenti.add(studente);
			}
		} catch(Throwable throwable) {
			throwable.printStackTrace();
			disconnetti(statement, connessione, resultSet);
		}
		disconnetti(statement, connessione, resultSet);
		return studenti;
	}

	@Override
	public boolean modificaStudente(Studente studente) {
		Connection connessione = null;
		PreparedStatement statement = null;
		
		try {
			connessione = connetti();
			statement = connessione.prepareStatement("UPDATE STUDENTE SET COGNOME = ?, NOME = ?, NASCITA = ? WHERE MATRICOLA = ?");
			statement.setString(1, studente.getCognome());
			statement.setString(2, studente.getNome());
			statement.setString(3, studente.getDataNascita());
			statement.setInt(4, studente.getMatricola());
			statement.execute();
			
		} catch(Throwable throwable) {
			throwable.printStackTrace();
			disconnetti(statement, connessione, null);
			return false;
		}
		
		disconnetti(statement, connessione, null);
		return true;
	}
	
	@Override
	public boolean rimuoviStudente(int matricola) {
		Connection connessione = null;
		PreparedStatement statement = null;
		
		try {
			connessione = connetti();
			statement = connessione.prepareStatement("DELETE FROM STUDENTE WHERE MATRICOLA = ?");
			statement.setInt(1, matricola);
			statement.execute();
			
		} catch(Throwable throwable) {
			throwable.printStackTrace();
			disconnetti(statement, connessione, null);
			return false;
		}
		
		disconnetti(statement, connessione, null);
		return true;
	}

	@Override
	public Studente caricaDati(int matricola) {
		Connection connessione = null;
		PreparedStatement statement = null;
		ResultSet resultSet = null;
		Studente studente = null;
		
		try {
			connessione = connetti();
			statement = connessione.prepareStatement("SELECT * FROM STUDENTE WHERE MATRICOLA = ?");
			statement.setInt(1, matricola);
			resultSet = statement.executeQuery();
			
			if(resultSet.next()) {
				studente = new Studente(matricola, resultSet.getString("NOME"), resultSet.getString("COGNOME"), resultSet.getString("NASCITA"));
				disconnetti(statement, connessione, resultSet);
				return studente;
			}
			else {  // Se l'SQL non ha dato risultati:
				disconnetti(statement, connessione, resultSet);
				return null;
			}
		} catch(Throwable throwable) {
			throwable.printStackTrace();
			disconnetti(statement, connessione, resultSet);
			return null;
		}
	}

	@Override
	public boolean aggiungiStudente(Studente studente) {  //La "matricola" dello studente non viene considerata
		Connection connessione = null;
		PreparedStatement statement = null;
		ResultSet resultSet = null;
		
		try {
			connessione = connetti();
			statement = connessione.prepareStatement("INSERT INTO STUDENTE (COGNOME,NOME,NASCITA) VALUES (?,?,?)", statement.RETURN_GENERATED_KEYS);
			statement.setString(1, studente.getCognome());
			statement.setString(2, studente.getNome());
			statement.setString(3, studente.getDataNascita());
			statement.execute();
			
		} catch(Throwable throwable) {
			throwable.printStackTrace();
			disconnetti(statement, connessione, resultSet);
			return false;
		}
		
		disconnetti(statement, connessione, resultSet);
		return true;
	}
	
	public Connection connetti() throws SQLException {
		return DriverManager.getConnection(url);
	}
	
	public void disconnetti(Statement statement, Connection connection, ResultSet resultSet) {
		try{
			statement.close();
		} catch(Throwable throwable) {
			//Vuoto
		}
		try{
			connection.close();
		} catch(Throwable throwable) {
			//Vuoto
		}
		try{
			resultSet.close();
		} catch(Throwable throwable) {
			//Vuoto
		}
	}
	
}