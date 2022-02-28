package com.company;

import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Scanner;

/**
 * detine liste cu produse,brokeri si licitatii
 */


public class CasaLicitatii implements  Runnable{
    private ListaProduse produse = new ListaProduse();
    private ArrayList<Client> clienti = new ArrayList<>();
    private ArrayList<Licitatie> licitatii = new ArrayList<>();
    private ArrayList<Broker> angajati = new ArrayList<>();
    private PrintWriter file;

    public void setFile(PrintWriter file) {
        this.file = file;
    }

    public PrintWriter getFile() {
        return file;
    }

    private static CasaLicitatii instance = new CasaLicitatii();

    public static CasaLicitatii getInstance(){
        return instance;
    }

    public CasaLicitatii() {
    }

    public ListaProduse getProduse() {
        return produse;
    }

    public ArrayList<Client> getClienti() {
        return clienti;
    }

    public ArrayList<Licitatie> getLicitatii() {
        return licitatii;
    }

    public ArrayList<Broker> getAngajati() {
        return angajati;
    }

    /**
     * preia de la fiecare broker care are clienti care liciteaza pentru produsul id_produs
     * suma licitata si afla maximul dintre toate sumele
     * @param id_produs id-ul produsul
     */

    public void calculeazaMaximLicitatie(int id_produs){

        ArrayList<Double> l_1;
        int c_i = -1;
        ArrayList<Double> l_2 = new ArrayList<>();
        for(int i = 0; i < licitatii.size(); i++){
            if(licitatii.get(i).getId_produs() == id_produs) {
                c_i = i; //salveaza indexul
                for(int j = 0; j < angajati.size(); j++){
                    l_1 = angajati.get(j).getSume(licitatii.get(i));
                    if(l_1 != null){
                        double max = Collections.max(l_1);
                        l_2.add(max);
                    }
                }
            }
        }

        licitatii.get(c_i).setMaxim(Collections.max(l_2));
        licitatii.get(c_i).incPasi();
    }

    /**
     * trece prin toate licitatiile si verifica daca au suficienti participanti pentru
     * a le porni
     * in caz contrar anunta numarul de participanti necesari pentru pornirea licitatiei
     */

    public void verificaLicittatii (){

        int index_produs = -1;
        boolean exista_licitatie = false;

        for(int i = 0; i < licitatii.size(); i++){
            exista_licitatie = true;
            boolean gata = false;
            if(licitatii.get(i).getParticipanti_curenti() == licitatii.get(i).getNr_participanti() &&
            !licitatii.get(i).isLicitatie_terminata()){
                //cauta produsul in lista de produse pt a anunta inceperea licitatiei
                for(int j = 0; j < produse.getList().size(); j++){
                    if(produse.getList().get(j).getId() == licitatii.get(i).getId_produs()){
                        index_produs = j;
                        break;
                    }
                }
                file.write("Incepe licitatie pentru produsul:\n");
                produse.getList().get(index_produs).print(file);
                for(int k = 0; k < licitatii.get(i).getNr_pasi_maxim(); k++){
                    licitatii.get(i).getBrokeri().get(licitatii.get(i).getBrokeri().size() - 1)
                            .pasLicitatie(licitatii.get(i));
                }
            }
            else if(!licitatii.get(i).isLicitatie_terminata()){
                int necesari = licitatii.get(i).getNr_participanti() - licitatii.get(i).getParticipanti_curenti();
                file.write("Mai sunt necesari:" + necesari + " participanti pentru a incepe licitatia produsului cu id-ul:"
                        + licitatii.get(i).getId_produs() + "\n");
            }
        }
        if(!exista_licitatie)
            file.write("Nu exista licitatii disponibile\n");
    }
    @Override

    /**
     * ruleaza programul si asteapta comenzi de alaturare licitatie sau listare produse
     */
    public void run() {
        List l = ReadFile.readFileInList("test1.txt");
        for (int i = 0; i < l.size(); i++) {

            String[] command = ((String) l.get(i)).split(" ", 0);
            switch (command[0]) {
                case "listproducts":
                    ListCommand x = new ListCommand(clienti.get(clienti.size() - 1), instance);
                    x.execute();
                    break;
                case "joinbid":
                    int id_client = Integer.parseInt(command[1]);
                    int id_produs = Integer.parseInt(command[2]);
                    double pret_maxim = Double.parseDouble(command[3]);
                    try {
                        Thread.sleep(100);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                    JoinBidCommand y = new JoinBidCommand(instance, id_produs, id_client, pret_maxim);
                    y.execute();
                    break;
                case "quit":
                    file.close();
                    System.exit(0);
                default:
                    file.write("Comanda nerecunoscuta\n");


            }
            if ((i + 1) % 4 == 0)
                verificaLicittatii();
        }
    }
}
