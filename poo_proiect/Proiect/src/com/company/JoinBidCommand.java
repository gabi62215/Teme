package com.company;

/**
 * executa comanda joinbid care adauga un client la o licitatie
 */

public class JoinBidCommand implements Command {
    CasaLicitatii casaLicitatii;
    int id_produs;
    int id_client;
    double pret_maxim;

    public JoinBidCommand(CasaLicitatii casaLicitatii, int id_produs, int id_client, double pret_maxim) {
        this.casaLicitatii = casaLicitatii;
        this.id_produs = id_produs;
        this.id_client = id_client;
        this.pret_maxim = pret_maxim;
    }


    @Override
    public void execute() {
        casaLicitatii.getClienti().get(id_client).alaturareLicitatie(casaLicitatii,id_produs,id_client,pret_maxim);
    }
}
