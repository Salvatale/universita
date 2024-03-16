<%@ page import="it.unipr.informatica.esercizio7.modello.Studente"%>
<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
<title>Modifica Studente</title>
</head>
<body>
<% 
	Studente studente = (Studente)session.getAttribute("studente");
%>
<form action="aggiorna_studente" method="post">
<p>Matricola: <input name="matricola" type="text" value="<%=studente.getMatricola() %>" readonly="readonly" /></p>
<p>Cognome: <input name="cognome" type="text" value="<%=studente.getCognome() %>" /></p>
<p>Nome: <input name="nome" type="text" value="<%=studente.getNome() %>" /></p>
<p><input type="submit" value="Modifica Studente" /></p>
</form>
</body>
</html>
