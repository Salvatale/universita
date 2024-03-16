package esame3.web;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import esame3.sessione.Sessione;

@SuppressWarnings("serial")
public class LinguaSitoServlet extends HttpServlet {
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		try{
			HttpSession session = request.getSession();
			Sessione sessione = (Sessione)session.getAttribute("sessione");
			
			if(sessione==null) {
				sessione = new Sessione();
				session.setAttribute("sessione", sessione);
			}
			
			session.setAttribute("lingua_sito", request.getParameter("lingua"));
			
			request.getRequestDispatcher("sistema_gestione.jsp").forward(request, response);
		} catch(Throwable throwable) {
			request.getRequestDispatcher("error.html").forward(request, response);
		}
	}

	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		doGet(request, response);
	}

}
