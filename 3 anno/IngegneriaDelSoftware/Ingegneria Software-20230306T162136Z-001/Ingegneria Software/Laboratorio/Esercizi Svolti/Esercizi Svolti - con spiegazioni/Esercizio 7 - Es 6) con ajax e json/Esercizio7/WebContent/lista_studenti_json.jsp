<%@ page import="it.unipr.informatica.esercizio7.Sessione"%>
<%@ page import="it.unipr.informatica.esercizio7.modello.Studente"%>
<%@ page import="java.util.List"%>
<%@ page import="it.unipr.informatica.esercizio7.database.DatabaseManager"%>
<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
<title>Esercizio 7</title>
<script type="text/javascript">
function rimuovi(matricola) {
	var sicuro = confirm("Sei sicuro di voler cancellare lo studente con matricola: " + matricola);

	if(sicuro == true)
		location.href = "rimuovi_studente?matricola="+matricola;
}

function nuovo_stato_connessione() {
	if(richiesta.readyState != 4)
		return;
	
	if(richiesta.status != 200)
		return;
	
	var json = richiesta.responseText;

	eval("risultato = " + json);
		
	var indice = 0;

	while(risultato[indice] != null) {
		var studente = risultato[indice];
		
		var matricola = studente["matricola"];
		
		var cognome = studente["cognome"];
		
		var nome = studente["nome"];
		
		var riga = document.createElement("tr");
		
		var stringa = "<td><a href='dettagli_studente?matricola=" + matricola + "'>Dettagli</a></td>";
		
		stringa += "<td><a href='modifica_studente?matricola=" + matricola + "'>Modifica</a></td>";

		stringa += "<td><a href='javascript:rimuovi(" + matricola + ")'>Rimuovi</a></td>";

		stringa += "<td><a href='dettagli_studente?matricola=" + matricola + "'>" + matricola + "</a></td>";

		stringa += "<td><a href='dettagli_studente?matricola=" + matricola + "'>" + cognome + "</a></td>";
		
		stringa += "<td><a href='dettagli_studente?matricola=" + matricola + "'>" + nome + "</a></td>";

		riga.innerHTML = stringa;

		tabella.appendChild(riga);
		
		indice++;
	}
}

function caricaTabella() {
	tabella = document.getElementById("tabella");
	
	tabella.innerHTML = "";

	var riga = document.createElement("tr");
	
	riga.innerHTML = "<td></td><td></td><td></td><td class='intestazione'>Matricola</td><td class='intestazione'>Cognome</td><td class='intestazione'>Nome</td>";

	tabella.appendChild(riga);
	
	richiesta = null;
	
	if(window.XMLHttpRequest) 
		richiesta = new XMLHttpRequest();
	else
		richiesta = new ActiveXObject("Microsoft.XMLHTTP");

	richiesta.onreadystatechange = nuovo_stato_connessione;

	richiesta.open("GET", "lista_studenti_json", true);
	
	richiesta.send(null);	
}
</script>
<link href="stile.css" rel="stylesheet" />
</head>
<body>
<h1>Sistema di Gestione Studenti</h1>
<h2>Attività disponibili</h2>
<body onLoad="caricaTabella()">
<% 
	String messaggio = (String)session.getAttribute("messaggio");
	
	if(messaggio != null) {
		session.removeAttribute("messaggio");
%>
<p class="testo_rosso"><%=messaggio %></p>
<% 
	}
%>
<p><a href="aggiungi_studente.jsp">Aggiungi studente</a></p>
<p><a href="javascript:ricaricaTabella()">Ricarica tabella</a></p>
<table class="tabella" id="tabella">
</table>
</body>
</html>
