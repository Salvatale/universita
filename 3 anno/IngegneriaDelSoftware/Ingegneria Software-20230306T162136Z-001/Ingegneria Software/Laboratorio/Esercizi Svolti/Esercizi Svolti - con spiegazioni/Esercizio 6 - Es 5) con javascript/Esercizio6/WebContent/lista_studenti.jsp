<%@ page import="it.unipr.informatica.esercizio6.Sessione"%>
<%@ page import="it.unipr.informatica.esercizio6.modello.Studente"%>
<%@ page import="java.util.List"%>
<%@ page import="it.unipr.informatica.esercizio6.database.DatabaseManager"%>
<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
<title>Lista degli Studenti</title>
<script type="text/javascript">
function rimuovi(matricola) {
	var sicuro = confirm("Sei sicuro di voler cancellare lo studente con matricola: " + matricola);

	if(sicuro == true)
		location.href = "rimuovi_studente?matricola="+matricola;
}
</script>
</head>
<body>
<% 
	List<Studente> studenti = (List<Studente>)session.getAttribute("lista_studenti");

	session.removeAttribute("lista_studenti");
	
	String messaggio = (String)session.getAttribute("messaggio");
	
	if(messaggio != null) {
		session.removeAttribute("messaggio");
%>
<p><%=messaggio %></p>
<% 		
	}
%>
<p><a href="aggiungi_studente.jsp">Aggiungi studente</a></p>
<table>
<tr><td></td><td></td><td></td><td>Matricola</td><td>Cognome</td><td>Nome</td></tr>
<% 
	for(Studente studente : studenti) {
%>
<tr>
<td><a href="dettagli_studente?matricola=<%=studente.getMatricola() %>">Dettagli</a></td>
<td><a href="modifica_studente?matricola=<%=studente.getMatricola() %>">Modifica</a></td>
<td><a href="javascript:rimuovi(<%=studente.getMatricola() %>)">Rimuovi</a></td>
<td><a href="dettagli_studente?matricola=<%=studente.getMatricola() %>"><%=studente.getMatricola() %></a></td>
<td><a href="dettagli_studente?matricola=<%=studente.getMatricola() %>"><%=studente.getCognome() %></a></td>
<td><a href="dettagli_studente?matricola=<%=studente.getMatricola() %>"><%=studente.getNome() %></a></td>
</tr>
<%
	}
%>
</table>
</body>
</html>
