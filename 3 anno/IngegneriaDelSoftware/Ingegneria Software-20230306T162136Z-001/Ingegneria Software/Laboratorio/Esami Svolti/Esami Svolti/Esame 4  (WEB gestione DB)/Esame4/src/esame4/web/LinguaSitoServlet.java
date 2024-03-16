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
public class LinguaSitoServlet extends HttpServlet {
	
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		HttpSession session =  request.getSession();
		Sessione sessione = (Sessione)session.getAttribute("sessione");
		
		if(sessione==null) {
			 sessione = new Sessione();
			 session.setAttribute("sessione", sessione);
		}
		
		String lingua = request.getParameter("lingua");
		session.setAttribute("lingua_sito", lingua);
		
		DatabaseManager databaseManager = sessione.getDatabaseManager();
		List<Studente> studenti = databaseManager.ricaricaStudenti();
		session.setAttribute("lista_studenti", studenti);

		request.getRequestDispatcher("sistema.jsp").forward(request, response);
	}

	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		doGet(request, response);
	}

}
