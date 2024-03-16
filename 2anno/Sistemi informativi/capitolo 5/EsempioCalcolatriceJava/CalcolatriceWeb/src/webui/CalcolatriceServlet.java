package webui;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import lib.adapter.*;

/**
 * Servlet implementation class CalcolatriceServlet
 */
@WebServlet(description = "Servlet per la calcolatrice", urlPatterns = { "/CalcolatriceServlet" })
public class CalcolatriceServlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public CalcolatriceServlet() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		processRequest(request, response);
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		processRequest(request, response);
	}
	
	protected void processRequest(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// recupera i parametri in arrivo
		String operando1 = request.getParameter("txtOper1");
		String operando2 = request.getParameter("txtOper2");
		
		String comandoOperazione = request.getParameter("btnOperazione");
		
		// definisce la variabile per il risultato
		String risultato = "";
		
		if (comandoOperazione != null) {
			// controlla se i parametri sono diversi da null e nel caso elabora
			if ((operando1 != null) && (operando2 != null)) {
				switch (comandoOperazione) {
					case "+": {
						risultato = CalcolatriceAdapter.somma(operando1, operando2); 	
						break;
					}
					case "-": {
						risultato = CalcolatriceAdapter.sottrai(operando1, operando2); 	
						break;
					}
					case "*": {
						risultato = CalcolatriceAdapter.moltiplica(operando1, operando2); 	
						break;
					}
					case "/": {
						risultato = CalcolatriceAdapter.dividi(operando1, operando2); 	
						break;
					}

					default:
					break;
				} // end switch

			} // end if

		} // end if
		else {
			// i bottoni sono nulli
			operando1 = "";
			operando2 = "";
		}
		// String allarme = "<script>alert(\"pippo\");</script>";	
			
		// aggancia i parametri al canale verso la JSP
		request.setAttribute("operando1", operando1);
		request.setAttribute("operando2", operando2);
		request.setAttribute("risultato", risultato);
		
		// request.setAttribute("allarme", allarme);
		
		// manda il controllo alla JSP
		request.getRequestDispatcher("calcolatrice.jsp").forward(request,response);
		
		
	}
}
