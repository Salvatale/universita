package esame3.database;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.ResourceBundle;

import esame3.modello.Modello;
import esame3.modello.Studente;

public class DatabaseManager implements Modello {
	public String url;

	public DatabaseManager() {
		try {
			ResourceBundle bundle = ResourceBundle.getBundle("configurazione");
			url = bundle.getString("database.url");
			String clazz = bundle.getString("database.class");
			Class.forName(clazz);
		} catch (Throwable throwable) {
			throwable.printStackTrace();
		}
	}

	@Override
	public List<Studente> ricaricaLista() {
		List<Studente> studenti = new ArrayList<Studente>();
		
		Connection connection = null;
		PreparedStatement statement = null;
		ResultSet resultSet = null;
		try {
			connection = connetti();
			statement = connection.prepareStatement("SELECT * FROM STUDENTE");
			resultSet = statement.executeQuery();
			
			while(resultSet.next()) {
				Studente studente = new Studente(Integer.parseInt(resultSet.getString("MATRICOLA")), resultSet.getString("COGNOME"), resultSet.getString("NOME"));
				studenti.add(studente);
			}
			
		} catch (Throwable throwable) {
			disconnetti(connection, statement, resultSet);
			throwable.printStackTrace();
		}
		
		disconnetti(connection, statement, resultSet);
		return studenti;
	}

	public Connection connetti() throws SQLException {
		return DriverManager.getConnection(url);
	}

	public void disconnetti(Connection connection, PreparedStatement statement, ResultSet resultSet) {
		try {
			connection.close();
		} catch (Throwable throwable) {
			// Vuoto
		}
		try {
			statement.close();
		} catch (Throwable throwable) {
			// Vuoto
		}
		try {
			resultSet.close();
		} catch (Throwable throwable) {
			// Vuoto
		}
	}

}
