package esame3.web;

import java.io.IOException;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import esame3.database.DatabaseManager;
import esame3.modello.Studente;
import esame3.sessione.Sessione;

@SuppressWarnings("serial")
public class CambiaStudenteServlet extends HttpServlet {
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		try{
			HttpSession session = request.getSession();
			Sessione sessione = (Sessione)session.getAttribute("sessione");
			
			if(sessione==null) {
				sessione = new Sessione();
				session.setAttribute("sessione", sessione);
			}
			
			DatabaseManager databaseManager = sessione.getDatabaseManager();
			List<Studente> studenti = databaseManager.ricaricaLista();
		
			int sposta = Integer.parseInt(request.getParameter("sposta"));
			if(sposta==0)
				sposta = -1;
			int indice = (int)session.getAttribute("indice");
			int numero_studenti = studenti.size();
			indice = indice + sposta;	
			session.setAttribute("lista_studenti", studenti);
		
			if(indice >= 0 && indice < numero_studenti) {
				session.setAttribute("indice", indice);
				request.getRequestDispatcher("sistema_gestione.jsp").forward(request, response);
			} else {
				session.removeAttribute("indice");
				request.getRequestDispatcher("not_found.html").forward(request, response);
			}
		} catch(Throwable throwable) {
			request.getRequestDispatcher("error.html").forward(request, response);
		}
	}

	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		doGet(request, response);
	}

}
