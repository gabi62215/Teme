package com.company;

/**
 * executa comanda listproducts care listeaza toate produsele din casa de licitatii
 */

public class ListCommand implements Command {
    Client client;
    CasaLicitatii casaLicitatii;

    public ListCommand(Client client,CasaLicitatii casaLicitatii) {
        this.client = client;
        this.casaLicitatii = casaLicitatii;
    }


    @Override
    public void execute() {
        client.afiseazaProduse(casaLicitatii);
    }
}
