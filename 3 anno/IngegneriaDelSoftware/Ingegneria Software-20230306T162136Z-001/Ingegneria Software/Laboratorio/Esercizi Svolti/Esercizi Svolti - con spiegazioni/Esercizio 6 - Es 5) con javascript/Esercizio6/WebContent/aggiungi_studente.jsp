<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
<title>Aggiungi Studente</title>
<script type="text/javascript">
function trim(s) {
	return s.replace(/^\s+|\s+$/gm, "");
}

function verificaCampo() {
	var submit = document.getElementById("submit");
	
	var nodo = document.getElementById("cognome");
	
	var testo = nodo.value;

	var errore = document.getElementById("errore_cognome");
	
	var ok = true;

	if(trim(testo) == "") {
		errore.innerHTML = "Il cognome non può essere vuoto";
		
		submit.disabled = "disabled";
		
		ok = false;
	} else
		errore.innerHTML = "";
	
	nodo = document.getElementById("nome");
	
	testo = nodo.value;

	errore = document.getElementById("errore_nome");

	if(trim(testo) == "") {
		errore.innerHTML = "Il nome non può essere vuoto";

		submit.disabled = "disabled";
		
		ok = false;
	} else
		errore.innerHTML = "";

	if(ok)
		submit.removeAttribute("disabled");
}
</script>
</head>
<body>
<form action="inserisci_studente" method="post">
<p>Cognome: <input id="cognome" name="cognome" type="text" value="" onchange="verificaCampo()" /> <span id="errore_cognome"></span></p>
<p>Nome: <input id="nome" name="nome" type="text" value="" onchange="verificaCampo()" />  <span id="errore_nome"></span></p>
<p><input id="submit" type="submit" value="Aggiungi Studente" disabled="disabled" /></p>
</form>
</body>
</html>
