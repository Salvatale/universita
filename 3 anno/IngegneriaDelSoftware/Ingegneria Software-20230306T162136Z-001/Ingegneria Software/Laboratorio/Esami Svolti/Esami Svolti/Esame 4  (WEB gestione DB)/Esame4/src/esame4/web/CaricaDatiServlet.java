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
public class CaricaDatiServlet extends HttpServlet {
	
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		try {
			HttpSession session = request.getSession();
			Sessione sessione = (Sessione)session.getAttribute("sessione");
			
			if(sessione==null){
				sessione = new Sessione();
				session.setAttribute("sessione", sessione);
			}
			
			DatabaseManager databaseManager = sessione.getDatabaseManager();
			int matricola = Integer.parseInt(request.getParameter("matricola"));
			Studente studente = databaseManager.caricaDati(matricola);
			String messaggio = null;
			if(studente==null)
				messaggio = "ERRORE: Lo studente non non è iscritto!";
			
			List<Studente> studenti = databaseManager.ricaricaStudenti();
			
			session.setAttribute("lista_studenti", studenti);
			session.setAttribute("messaggio", messaggio);
			session.setAttribute("dati_studente", studente);
			request.getRequestDispatcher("sistema.jsp").forward(request, response);
		} catch(Throwable throwable) {
			request.getRequestDispatcher("errore.html").forward(request, response);
		}
	}

	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		doGet(request, response);
	}

}
