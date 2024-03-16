package esame3.sessione;

import esame3.database.DatabaseManager;

public class Sessione {
	public DatabaseManager databaseManager;
	
	public Sessione() {
		databaseManager = new DatabaseManager();
	}

	public DatabaseManager getDatabaseManager() {
		return databaseManager;
	}
}
