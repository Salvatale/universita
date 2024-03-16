<%@ page import="java.util.ArrayList"%>
<%@ page import="com.sun.org.apache.bcel.internal.generic.NEWARRAY"%>
<%@ page import="java.util.List" %>
<%@ page import="java.util.ResourceBundle" %>
<%@ page import="esame3.modello.Studente" %>
<%@ page import="esame3.database.DatabaseManager" %>
<%@ page import="esame3.sessione.Sessione" %>
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Sistema gestione</title>
</head>
<%
	// LINGUA
	ResourceBundle bundle = ResourceBundle.getBundle("configurazione");
	
	String lingua = (String)session.getAttribute("lingua_sito");
	if(lingua==null) {
		lingua = "Italiano";
		session.setAttribute("lingua_sito", lingua);
	}
	
	String conf = "Lingua." + lingua + ".";
	
	List<String> lista_lingue = new ArrayList();
	lista_lingue.add("Italiano");
	lista_lingue.add("English");
	lista_lingue.add("Klingon");
	// Aggiungo qui una nuova lingua
	
	int numero_lingue = lista_lingue.size();
	
	// STUDENTI
	List<Studente> studenti = (List<Studente>) session.getAttribute("lista_studenti");
	
	Integer indice = (Integer)session.getAttribute("indice");
	if(indice==null) {
		indice = 0;
		session.setAttribute("indice", indice);
	}
	
	int numero_studenti = studenti.size();
	
	Studente studente = studenti.get(indice);
%>
<body>
<h1><%= bundle.getString(conf + "Titolo") %></h1>

<form method="post" action="">
<p><%= bundle.getString(conf + "Matricola") %></p>
<p><input name="matricola" type="text" value="<%= studente.getMatricola() %>" readonly/></p>
<p><%= bundle.getString(conf + "Cognome") %></p>
<p><input name="cognome" type="text" value="<%= studente.getCognome() %>" readonly/></p>
<p><%= bundle.getString(conf + "Nome") %></p>
<p><input name="nome" type="text" value="<%= studente.getNome() %>" readonly/></p>
<br>
<p><%= bundle.getString(conf + "MsgStudenti") %> <%= indice+1 %> - <%= numero_studenti %></p>
<p>

<a href="cambia_studente?sposta=0"><input name="indietro" type="button" value="<%= bundle.getString(conf + "Indietro") %>"
<%
	if(indice==0) { %>
		disabled
<%	}
%>
																						/></a>
																						
<a href="cambia_studente?sposta=1"><input name="avanti" type="button" value="<%= bundle.getString(conf + "Avanti") %>"
<%
	if(indice==numero_studenti-1) { %>
		disabled
<%	}
%>
																						/></a>
<input type="submit" value="<%= bundle.getString(conf + "ScegliLingua") %>" onclick="form.action='lingua_sito'"/>

<select name="lingua">
<%
	// LINGUA
	for(int i=0; i<numero_lingue; i++) {
%>		
<%= lingua == lista_lingue.get(i) %>																
	<option value="<%= lista_lingue.get(i) %>"
<%		if(lingua.equals(lista_lingue.get(i))) {	%>	selected  <% } %>										
												><%= lista_lingue.get(i) %></option>
<%
	}
%>
</select>

</p>
</form>

</body>
</html>