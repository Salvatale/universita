<%@page import="java.util.ArrayList"%>
<%@page import="esame4.modello.Studente"%>
<%@page import="esame4.database.DatabaseManager"%>
<%@page import="esame4.sessione.Sessione"%>
<%@page import="java.util.List"%>
<%@page import="java.util.ResourceBundle"%>
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Sistema</title>
</head>
<%
	// LINGUA
	ResourceBundle resourceBundle = ResourceBundle.getBundle("configurazione");
	
	String lingua = (String)session.getAttribute("lingua_sito");
	if(lingua==null)
		lingua = "Italiano";
	
	String ConfLing = "Lingua." + lingua + ".";
	
	List<String> listaLingue = new ArrayList();
	listaLingue.add("Italiano");
	listaLingue.add("English");
	listaLingue.add("Klingon");
	//listaLingue.add("altra nuova lingua da aggiungere");
	
	
	// TABELLA STUDENTI
	Studente datiStudente = (Studente)session.getAttribute("dati_studente");
	String dataNascita = "";
	
	if(datiStudente==null) {
		datiStudente = new Studente(0, "", "", "");
	}
	else {
		dataNascita = datiStudente.getDataNascita();
		dataNascita = dataNascita.substring(6, 8) + "-" + dataNascita.substring(4, 6) + "-" + dataNascita.substring(0, 4);
	}
	session.removeAttribute("dati_studente");
%>

<body>
<h2><%=resourceBundle.getString(ConfLing + "TitoloSito") %></h2>

<form method="post" action="">
<p><span id="matricolaS"><%=resourceBundle.getString(ConfLing + "LblMatricolaTxt") %></span></p>
<p><input type="text" name="matricola" id="matricola" value="<%= datiStudente.getMatricola() %>" readonly/></p>

<p><span id="cognomeS"><%=resourceBundle.getString(ConfLing + "LblCognomeTxt") %></span></p>
<p><input type="text" name="cognome" id="cognome" value="<%= datiStudente.getCognome() %>"/></p>

<p><span id="nomeS"><%=resourceBundle.getString(ConfLing + "LblNomeTxt") %></span></p>
<p><input type="text" name="nome" id="nome"value="<%= datiStudente.getNome() %>"/></p>

<p><span id="dataNascitaS"><%=resourceBundle.getString(ConfLing + "LblNascitaTxt") %></span></p>
<p><input type="text" name="dataNascita" id="dataNascita" value="<%= dataNascita %>"/></p>

<p>
<table border="1">
<tr>
<td>
	<input type="submit" value="<%=resourceBundle.getString(ConfLing + "BtnRimuovi") %>" onclick="form.action='rimuovi_studente'"/>
	<input type="submit" value="<%=resourceBundle.getString(ConfLing + "BtnModifica") %>" onclick="form.action='modifica_studente'"/>
	<input type="submit" value="<%=resourceBundle.getString(ConfLing + "BtnAggiungi") %>" onclick="form.action='aggiungi_studente'"/>
</td>
<td>
	<a href="lista_studenti"><input type="button" value="<%=resourceBundle.getString(ConfLing + "BtnAggiornaTabella") %>" /></a>
</td>
<td>
	<input type="submit" value="<%=resourceBundle.getString(ConfLing + "BtnApplicaLingua") %>" onclick="form.action='lingua_sito'"/>

	<select name="lingua">
<%
	// LINGUA	
	for(int i=0; i<listaLingue.size();i++) {
%>		<option value="<%= listaLingue.get(i)%>" 
<%
		if(listaLingue.get(i).equals(lingua)) {
%>			selected
<%
		}
%>
												><%= listaLingue.get(i)%></option>
<%
	}
%>
	</select>
</td>
</tr>
</table>
</p>
</form>
<%
	// MESSAGGIO (di errore)
	String msg = (String)session.getAttribute("messaggio");
	session.removeAttribute("messaggio");
	if(msg==null)
		msg="";
%>
<p><font size="2"><%=msg %></font></p>
<br>
<span id="studentiInscrittiS"><%=resourceBundle.getString(ConfLing + "LblStudentiInscritti") %></span>
<table id="tabellaStudenti" border="1">
<tr> 
	<td><%=resourceBundle.getString(ConfLing + "LblMatricolaT") %></td>
	<td><%=resourceBundle.getString(ConfLing + "LblCognomeT") %></td>
	<td><%=resourceBundle.getString(ConfLing + "LblNomeT") %></td>
</tr>
<%	
	// TABELLA STUDENTI
	List<Studente> studenti = (List<Studente>)session.getAttribute("lista_studenti");
	session.removeAttribute("lista_studenti");
	
	if(studenti!=null) {
		for(Studente studente : studenti) { 
%>   
<tr>
<td> <a href="carica_dati?matricola=<%=studente.getMatricola()%>"><%= studente.getMatricola() %></a> </td>
<td> <a href="carica_dati?matricola=<%=studente.getMatricola()%>"><%= studente.getCognome() %></a> </td>
<td> <a href="carica_dati?matricola=<%=studente.getMatricola()%>"><%= studente.getNome() %></a> </td>
</tr>
<%		
		}
	}
%>
</table>

</body>
</html>