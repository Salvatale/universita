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
<title>Dettagli Studente</title>
</head>
<body>
<% 
	Studente studente = (Studente)session.getAttribute("studente");

	session.removeAttribute("studente");
%>
<p>Matricola: <%=studente.getMatricola() %></p>
<p>Cognome: <%=studente.getCognome() %></p>
<p>Nome: <%=studente.getNome() %></p>
<p>Torna a <a href="lista_studenti">lista studenti</a></p>
</body>
</html>
