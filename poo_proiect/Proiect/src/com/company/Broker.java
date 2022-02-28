package com.company;

import java.util.ArrayList;

/**
 * Clasa Broker cu campurile sale care face posibila comunicare intre casa si client
 */
public class Broker {
    private ArrayList<Client> clienti = new ArrayList<>();
    private CasaLicitatii casaLicitatii;

    public Broker(CasaLicitatii x) {
        casaLicitatii = x;
    }

    public Broker() {
    }

    public ArrayList<Client> getClienti() {
        return clienti;
    }

    /**
     * cere sumele de la fiecare client care este inscris la licitatia licitatie
     * @param licitatie licitatia curenta
     * @return returneaza o lista cu fiecare suma licitata de fiecare client
     */

    public ArrayList<Double> getSume(Licitatie licitatie) {
//brokeri au clienti de la toate licitatiile
        ArrayList<Double> l = new ArrayList<>();
        double comision = 1;
        for (int i = 0; i < clienti.size(); i++) {
            if(clienti.get(i).getId_produs() == licitatie.getId_produs()) {
                double suma = clienti.get(i).liciteaza(licitatie.getMaxim(),casaLicitatii.getFile());

                if (clienti.get(i) instanceof PersoanaFizica && clienti.get(i).getnr_participari() < 5){
                    comision = suma * 0.2;
                }

                if (clienti.get(i) instanceof PersoanaFizica && clienti.get(i).getnr_participari() >= 5){
                    comision = suma * 0.15;
                }
                if (clienti.get(i) instanceof PersoanaJuridica && clienti.get(i).getnr_participari() < 25){
                    comision = suma * 0.25;
                }
                if (clienti.get(i) instanceof PersoanaJuridica && clienti.get(i).getnr_participari() >= 25){
                    comision = suma * 0.10;
                }
                casaLicitatii.getFile().write("Client " + clienti.get(i).getId());

                casaLicitatii.getFile().write(" liciteaza:" + suma + "\n");
                casaLicitatii.getFile().write("Comision perceput:" + comision + "\n");
                l.add(suma);

            }

        }

        if(l.size() == 0)
            return null;
        return l;
    }

    /**
     * verifica daca s-a indeplinit pretul minim pentru vanzare produsului
     * daca s-a indeplinit,in cazul in care 2 clienti au licitat aceeasi suma il alege pe cel
     * cu mai multe licitatii castigate
     * sterge produsul vandut din lista de produse si arhiveaza o licitatie
     * @param x licitatia curenta
     */

    public void anuntaCastigator(Licitatie x) {
        int id_maxim = -1;
        int index_produs = -1;
        double maxim = -1;

        //decide castigatorul

        for (int i = 0; i < x.getClienti().size(); i++) {
            if (x.getClienti().get(i).getPret_licitat() > maxim){
                maxim = x.getClienti().get(i).getPret_licitat();
                id_maxim = x.getClienti().get(i).getId();
            }
            if(x.getClienti().get(i).getPret_licitat() == maxim){
                if(casaLicitatii.getClienti().get(id_maxim).getNr_licitatii_castigate() < x.getClienti().get(i).
                        getNr_licitatii_castigate())
                    id_maxim = x.getClienti().get(i).getId();
            }

        }

        //cauta produsul in lista de produse ale casei

        for(int i = 0; i < casaLicitatii.getProduse().getList().size(); i++){
            if(casaLicitatii.getProduse().getList().get(i).getId() == x.getId_produs()) {
                index_produs = i;
                break;
            }
        }

        //anunta castigatorul si sterge produsul

        if(x.getMaxim() >= casaLicitatii.getProduse().getList().get(index_produs).getPret_minim()) {

            casaLicitatii.getFile().write("Licitatia castigata cu suma " + casaLicitatii.getClienti().get(id_maxim).getPret_licitat()
                    + " de ");
            casaLicitatii.getClienti().get(id_maxim).print(casaLicitatii.getFile());
            casaLicitatii.getClienti().get(id_maxim).incLicitatiiCastigate();
            casaLicitatii.getProduse().stergeDupaId(x.getId_produs());
        }
        else {
            casaLicitatii.getFile().write("Nu a fost licitat pretul minim");
        }
        //arhiveaza licitatia
        for(int i = 0; i < casaLicitatii.getLicitatii().size(); i++){
            if(casaLicitatii.getLicitatii().get(i).getId() == x.getId()){
                casaLicitatii.getLicitatii().get(i).setLicitatie_terminata(true);
                break;
            }
        }

        //sterge clienti care participau la licitatia castigata din lista de clienti
        //a fiecarui broker
        for(int i = 0; i < casaLicitatii.getAngajati().size(); i++){
            for(int j = 0; j < casaLicitatii.getAngajati().get(i).getClienti().size(); j++)
                if(casaLicitatii.getAngajati().get(i).getClienti().get(j).getId_produs() == x.getId_produs()){
                    casaLicitatii.getAngajati().get(i).getClienti().remove(j);
                }
        }

    }

    /**
     * reprezinta un pas al licitatiei
     * verifica daca s-a ajung la nuamrul maxim de pasi pentru a opri licitatia,iar in caz contrar
     * comunica pretul maxim licitat si cere noile sume de la fiecare client
     * @param licitatie licitatia curenta
     */

    public void pasLicitatie(Licitatie licitatie) {

        casaLicitatii.getFile().write("Pasul:" + licitatie.getPasi() + "\n");
        casaLicitatii.getFile().write("Nr maxim pasi:" + licitatie.getNr_pasi_maxim() + "\n");

        if (licitatie.getNr_pasi_maxim() == licitatie.getPasi()) {
            anuntaCastigator(licitatie);
        } else {
            casaLicitatii.getFile().write("Cea mai mare suma licitata:" + licitatie.getMaxim() + " pentru produsul " +
                    "cu id-ul:" + licitatie.getId_produs() + "\n");
            casaLicitatii.calculeazaMaximLicitatie(licitatie.getId_produs());
        }
    }


}
