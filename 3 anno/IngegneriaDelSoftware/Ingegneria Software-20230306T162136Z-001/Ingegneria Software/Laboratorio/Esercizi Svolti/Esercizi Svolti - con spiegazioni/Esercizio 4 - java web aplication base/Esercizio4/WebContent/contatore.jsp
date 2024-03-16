<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
<title>Pagina Contatore</title>
</head>
<body>
Testo della pagina dinamica.
<br>
Il valore del parametro 1 e':
<%
	out.print(request.getParameter("par1"));
%>
<br>
Il valore del parametro 2 e':
<%
	out.print(request.getParameter("par2"));
%>
<br>
Il valore del contatore e':
<% 
	Integer contatore = (Integer)session.getAttribute("contatore_servlet.contatore");

	out.print(contatore);
%>
<br>
Il valore del session ID e': 
<% 
	out.print(session.getId());
%>

<%
	if(contatore > 5)
		session.invalidate();
%>
</body>
</html>
