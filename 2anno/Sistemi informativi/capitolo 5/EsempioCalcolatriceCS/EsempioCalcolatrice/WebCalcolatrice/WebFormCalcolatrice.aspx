<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="WebFormCalcolatrice.aspx.cs" Inherits="WebCalcolatrice.WebFormCalcolatrice" %>

<!DOCTYPE html>
<%-- Commento --%>
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
    <title>Web Form Calcolatrice</title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
    
        <p> Primo operando:&nbsp;&nbsp;&nbsp;&nbsp;
            <asp:TextBox ID="txtOperando1" runat="server"></asp:TextBox>
        </p>

        <p> Secondo operando:&nbsp;&nbsp;&nbsp;&nbsp;
            <asp:TextBox ID="txtOperando2" runat="server"></asp:TextBox>
        </p>

        <p> 
            <asp:Button ID="btnSomma" runat="server" Font-Bold="True" Font-Size="Large" Height="30px" Text="+" Width="30px" OnClick="btnSomma_Click" />
&nbsp;&nbsp;&nbsp;
            <asp:Button ID="btnSottrai" runat="server" Font-Bold="True" Font-Size="Large" Height="30px" Text="-" Width="30px" OnClick="btnSottrai_Click" />
&nbsp;&nbsp;&nbsp;
            <asp:Button ID="btnMoltiplica" runat="server" Font-Bold="True" Font-Size="Large" Height="30px" Text="*" Width="30px" OnClick="btnMoltiplica_Click" />
&nbsp;&nbsp;&nbsp;
            <asp:Button ID="btnDividi" runat="server" Font-Bold="True" Font-Size="Large" Height="30px" Text="/" Width="30px" OnClick="btnDividi_Click" />
        </p>

        <p> Risultato:&nbsp;&nbsp;&nbsp;&nbsp; <asp:TextBox ID="txtRisultato" runat="server"></asp:TextBox>
        </p>
    
    </div>
    </form>
</body>
</html>
