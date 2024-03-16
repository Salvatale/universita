package esame4.sessione;

import esame4.database.DatabaseManager;

public class Sessione {
	protected DatabaseManager databaseManager;
	
	public Sessione() {
		databaseManager = new DatabaseManager();
	}

	public DatabaseManager getDatabaseManager() {
		return databaseManager;
	}
}
