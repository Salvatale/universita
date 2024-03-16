package unipr.aldo.graphic;
//Il LISTENER dà una funzione al bottone Esci
import java.awt.event.ActionEvent;  //fa qualcosa quando succede un certo evento
import java.awt.event.ActionListener;  //controlla se avviene un certo evento
public class ListenerEsci implements ActionListener { //bisogna implementare tutti i metodi perchè non c'è ereditarietà
	private GUI_prova Gigi;
	
	ListenerEsci(GUI_prova Gp){ //metodo costruttore
		Gigi = Gp;
	};
	
	@Override  //riscrivo completamente il metodo
	public void actionPerformed (ActionEvent arg0) {
		Gigi.Esci();
	}
}
