package esame1.swing;

import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.awt.Image;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.ResourceBundle;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

import esame1.database.DatabaseManager;
import esame1.modello.Utente;
import esame1.vista.Applicazione;

public class ApplicazioneSwing implements Applicazione {
	int conta = 0;
	@Override
	public void pannelloLogin() {
		try {
		
		// PRINCIPALE
		JPanel pan_principale = new JPanel();
		pan_principale.setLayout(new BorderLayout());
		
		// BASSO
		JPanel pan_basso = new JPanel();
		pan_principale.add(pan_basso,BorderLayout.SOUTH);
		
		// Bottone Ok
		JButton ok = new JButton();
		ok.setText("OK");
		pan_basso.add(ok,BorderLayout.WEST);
		ok.setEnabled(false);
		
		// Bottone Annulla
		JButton annulla = new JButton();
		annulla.setText("Annulla");
		pan_basso.add(annulla,BorderLayout.EAST);
		
		// CENTRO
		JPanel pan_centro = new JPanel();
		pan_centro.setLayout(new GridLayout(1, 2));
		pan_principale.add(pan_centro,BorderLayout.CENTER);
		
		// Logo
		ImageIcon logo = new ImageIcon("res/Logo.jpg");
		Image scaledImage = logo.getImage().getScaledInstance(130,130,Image.SCALE_DEFAULT);
		logo.setImage(scaledImage);
		JLabel img = new JLabel(logo);
		pan_centro.add(img, 0);
		
		//CENTRO - DESTRA
		JPanel pan_destra = new JPanel();
		pan_destra.setLayout(new GridLayout(5,1));
		pan_centro.add(pan_destra,1);
		
		//Campi di testo
		JLabel nomeLbl = new JLabel("Nome utente");
		JTextField nomeTxt = new JTextField();
		JLabel passwordLbl = new JLabel("Parola chiave");
		JTextField passwordTxt = new JTextField();
		
		pan_destra.add(nomeLbl,0);
		pan_destra.add(nomeTxt,1);
		pan_destra.add(passwordLbl,2);
		pan_destra.add(passwordTxt,3);
		
		// ComboBox
		String[] linguaLista = new String[] {"Italiano", "English", "Klingon"};
		JComboBox<String> linguaCombo = new JComboBox<String>(linguaLista); 
		pan_principale.add(linguaCombo,BorderLayout.NORTH);
		
		// FINESTRA
		JFrame finestra = new JFrame();
		finestra.setTitle("Entra nel sistema");
		finestra.setLocation(0, 0);
		finestra.setSize(400, 240);
		finestra.add(pan_principale,BorderLayout.NORTH);
		finestra.setVisible(true);
		
		
		// LISTENER
		// Ok  (valida)
		ok.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				valida(nomeTxt.getText(), passwordTxt.getText());
			}
		});
		
		// Annulla  (esci)
		annulla.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				esci();
			}
		});
		
		// Nome  (disattiva bottone Ok)
		nomeTxt.addKeyListener(new KeyListener() {
			@Override
			public void keyTyped(KeyEvent e) {
				//Vuoto
			}
			@Override
			public void keyReleased(KeyEvent e) {
				abilitaBottoneOk(ok, nomeTxt, passwordTxt);
			}
			@Override
			public void keyPressed(KeyEvent e) {
				//Vuoto
			}
		});
		
		// Password  (disattiva bottone Ok)
		passwordTxt.addKeyListener(new KeyListener() {
			@Override
			public void keyTyped(KeyEvent e) {
				//Vuoto
			}
			@Override
			public void keyReleased(KeyEvent e) {
				abilitaBottoneOk(ok, nomeTxt, passwordTxt);
			}
			@Override
			public void keyPressed(KeyEvent e) {
				//Vuoto
			}
		});
		
		// ComboBox  (cambio lingue)
		linguaCombo.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				JComboBox<String> combo = (JComboBox<String>) e.getSource();
		        String linguaScelta = (String) combo.getSelectedItem();
		        String lingua = "Lingua." + linguaScelta + ".";
		        
		        ResourceBundle resourceBundle = ResourceBundle.getBundle("configurazione");

		        annulla.setText(resourceBundle.getString(lingua + "annulla"));
				ok.setText(resourceBundle.getString(lingua + "ok"));
				nomeLbl.setText(resourceBundle.getString(lingua + "nome"));
				passwordLbl.setText(resourceBundle.getString(lingua + "password"));
				finestra.setTitle(resourceBundle.getString(lingua + "titolo"));
			}
		});
		
		// Finestra  (chiusura)
		finestra.addWindowListener(new WindowAdapter() {
			@Override
			public void windowClosing(WindowEvent e) {
				esci();
			}
		});
		
		
		} catch(Throwable throwable) {
			throwable.printStackTrace();
		}
	}

	@Override
	public boolean valida(String nome, String password) {
		System.out.println("valida");
		conta++;
		
		Utente utente = new Utente(nome, password);
		DatabaseManager databaseManager = new DatabaseManager();
				
		if(databaseManager.cercaUtente(utente)) {
			System.out.println("Utente trovato!");
			System.exit(0);
			return true;
		}
		else {
			System.out.println("Utente NON trovato!");
			if(conta<3) {
				return true;
			}
			else {
				System.exit(0);
				return true;
			}
		}
	}

	@Override
	public void esci() {
		System.out.println("esci");
		System.exit(0);
	}

	
	public void abilitaBottoneOk(JButton ok, JTextField nomeTxt, JTextField passwordTxt) {
		if(nomeTxt.getText().isEmpty() || passwordTxt.getText().isEmpty())
			ok.setEnabled(false);
		else
			ok.setEnabled(true);
	}
}