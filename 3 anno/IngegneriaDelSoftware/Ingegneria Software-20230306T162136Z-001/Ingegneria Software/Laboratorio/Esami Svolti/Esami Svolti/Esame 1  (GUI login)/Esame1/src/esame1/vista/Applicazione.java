package esame1.vista;

public interface Applicazione {
	
    public void pannelloLogin();
    
    public boolean valida(
    		String nome,
    		String password
    	);
    
    public void esci();
}
