<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<jsp:useBean id="operando1" scope="request" class="java.lang.String"></jsp:useBean>
<jsp:useBean id="operando2" scope="request" class="java.lang.String"></jsp:useBean>
<jsp:useBean id="risultato" scope="request" class="java.lang.String"></jsp:useBean>

<jsp:useBean id="allarme" scope="request" class="java.lang.String"></jsp:useBean>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
<title>Insert title here</title>
</head>
<body>
	<h1>Calcolatrice Web</h1>
	<form name="miaForm" action="CalcolatriceServlet" method="get">
		
		Primo operando: &nbsp; &nbsp; &nbsp; <input type="text" name="txtOper1" value="<%=operando1 %>">
		<br>
		
		Secondo operando: &nbsp; &nbsp; <input type="text" name="txtOper2" value="<%=operando2 %>">
		<br>
		<br>
		
		<input type="submit" name="btnOperazione" value="+">
		&nbsp;&nbsp;&nbsp;
		<input type="submit" name="btnOperazione" value="-">
		&nbsp;&nbsp;&nbsp;
		<input type="submit" name="btnOperazione" value="*">
		&nbsp;&nbsp;&nbsp;
		<input type="submit" name="btnOperazione" value="/">
		<br>
		<hr>
		<br>
		Risultato: &nbsp; &nbsp; 
		<input type="text" name="txtRisultato" value="<%=risultato %>">
	</form>
		<br>
		<%=allarme %>
</body>
</html>