package esame2.database;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.ResourceBundle;

import esame2.modello.Modello;
import esame2.modello.Studente;

public class DatabaseManager implements Modello {
	String url;

	public DatabaseManager() {
		try {
			ResourceBundle bundle = ResourceBundle.getBundle("configurazione");
			String clazz = bundle.getString("database.class");
			url = bundle.getString("database.url");
			Class.forName(clazz);
		} catch (Throwable throwable) {
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
			connessione = connetti(url);
			statement = connessione.prepareStatement("SELECT * FROM STUDENTE");
			resultSet = statement.executeQuery();

			while (resultSet.next()) {
				int matricola = Integer.parseInt(resultSet.getString("MATRICOLA"));
				String cognome = resultSet.getString("COGNOME");
				String nome = resultSet.getString("NOME");
				Studente studente = new Studente(matricola, cognome, nome);
				studenti.add(studente);
			}
		} catch (Throwable throwable) {
			throwable.printStackTrace();
			disconnetti(connessione, statement, resultSet);
		}

		disconnetti(connessione, statement, resultSet);
		return studenti;
	}

	@Override
	public boolean modificaStudente(Studente studente) {
		Connection connessione = null;
		PreparedStatement statement = null;
		ResultSet resultSet = null;
		
		try {
			connessione = connetti(url);
			statement = connessione.prepareStatement("UPDATE STUDENTE SET COGNOME=?,NOME=? WHERE MATRICOLA=?");
			statement.setString(1, studente.getCognome());
			statement.setString(2, studente.getNome());
			statement.setString(3, Integer.toString(studente.getMatricola()));
			
			int i = statement.executeUpdate();
			
			if(i==1) {
				disconnetti(connessione, statement, resultSet);
				return true;
			} else {
				disconnetti(connessione, statement, resultSet);
				return false;
			}
			
		} catch(Throwable throwable) {
			throwable.printStackTrace();
			disconnetti(connessione, statement, resultSet);
			return false;
		}
	}

	public Connection connetti(String url) throws SQLException {
		return DriverManager.getConnection(url);
	}

	public void disconnetti(Connection connessione, PreparedStatement statement, ResultSet resultSet) {
		try {
			connessione.close();
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
