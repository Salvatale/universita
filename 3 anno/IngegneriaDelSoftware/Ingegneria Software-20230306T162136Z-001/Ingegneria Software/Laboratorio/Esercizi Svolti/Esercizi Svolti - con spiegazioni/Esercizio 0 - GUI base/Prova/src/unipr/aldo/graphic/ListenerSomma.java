package unipr.aldo.graphic;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ListenerSomma implements ActionListener {
	private GUI_prova gigi; //puntatore a GUI_prova (senza crearlo)

	ListenerSomma(GUI_prova g) {
		gigi = g;
	}
	
	@Override
	public void actionPerformed(ActionEvent e) {
			gigi.Somma(); //richiama la funzione della GUI_prova
	}
	
}