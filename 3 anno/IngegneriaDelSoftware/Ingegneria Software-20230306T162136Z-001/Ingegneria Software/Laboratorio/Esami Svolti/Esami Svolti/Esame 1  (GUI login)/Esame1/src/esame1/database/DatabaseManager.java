package esame1.database;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ResourceBundle;

import esame1.modello.Modello;
import esame1.modello.Utente;

public class DatabaseManager implements Modello {

	protected String url;
	
	public DatabaseManager() {
		try {
			ResourceBundle resourceBundle = ResourceBundle.getBundle("configurazione");
			String clazz = resourceBundle.getString("database.class");
			url = resourceBundle.getString("database.url");
			Class.forName(clazz);
		
		} catch (Throwable throwable) {
			throwable.printStackTrace();
		}
	}
	
	@Override
	public boolean cercaUtente(Utente utente) {
		Connection connessione = null;
		PreparedStatement statement = null;
		ResultSet resultSet = null;
		
		try {
			connessione = connetti();
			statement = connessione.prepareStatement("SELECT * FROM UTENTI WHERE NOME='" + utente.getNome() + "' AND PAROLA_CHIAVE='" + utente.getPassword() + "'");
			resultSet = statement.executeQuery();
			
			if(resultSet.next())
				return true;
			return false;
			
		} catch(Throwable throwable) {
			throwable.printStackTrace();
			disconnetti(connessione, statement, resultSet);
		}
		
		return false;
	}
	
	public void disconnetti(Connection connection, PreparedStatement statement, ResultSet resultSet) {
		try {
			connection.close();
		} catch(Throwable throwable) {
			//Vuoto
		}
		
		try {
			statement.close();
		} catch(Throwable throwable) {
			//Vuoto
		}
		
		try {
			resultSet.close();
		} catch(Throwable throwable) {
			//Vuoto
		}
	}
	
	public Connection connetti() throws SQLException {
		return DriverManager.getConnection(url);
	}

}
