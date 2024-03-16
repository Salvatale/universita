package esame4.web;

import java.io.IOException;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import esame4.database.DatabaseManager;
import esame4.modello.Studente;
import esame4.sessione.Sessione;

@SuppressWarnings("serial")
public class ModificaStudenteServlet extends HttpServlet {
	
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		try {
			HttpSession session =  request.getSession();
			Sessione sessione = (Sessione)session.getAttribute("sessione");
			
			if(sessione==null) {
				 sessione = new Sessione();
				 session.setAttribute("sessione", sessione);
			}

			int matricola = Integer.parseInt(request.getParameter("matricola"));
			String cognome = request.getParameter("cognome");
			String nome = request.getParameter("nome");		

			String dataNascita = request.getParameter("dataNascita");
			dataNascita = dataNascita.replaceAll("-", "");
		
			DatabaseManager databaseManager = sessione.getDatabaseManager();
			String messaggio = null;

			if(cognome.isEmpty() || nome.isEmpty() || dataNascita.length()!=8) {
				messaggio = "ERRORE: Dati modificati non correttamente!";
			}
			else {
				dataNascita = dataNascita.substring(4, 8) + dataNascita.substring(2, 4) + dataNascita.substring(0,2);
				Studente studente = new Studente(matricola, nome, cognome, dataNascita);			
				if(databaseManager.modificaStudente(studente))
					messaggio = "Studente modificato correttamente.";
				else
					messaggio = "ERRORE: Non è stato possibile aggiungere lo studente!";
			}
			
			List<Studente> studenti = databaseManager.ricaricaStudenti();
			session.setAttribute("lista_studenti", studenti);
			session.setAttribute("messaggio", messaggio);

			request.getRequestDispatcher("sistema.jsp").forward(request, response);

		} catch(Throwable throwable) {
			request.getRequestDispatcher("errore.html").forward(request, response);
		}
	}

	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		doGet(request, response);
	}

}
