package com.company;

import java.io.PrintWriter;

/**
 * Clasa client cu campurile specifice si cateva adaugate in plus
 */

public abstract class Client {
    private int id;
    private String nume;
    private String adresa;
    private int nr_participari = 0;
    private int nr_licitatii_castigate = 0;
    private double pret_maxim;
    private double pret_licitat;
    private int id_produs;

    public int getId_produs() {
        return id_produs;
    }

    public void setId_produs(int id_produs) {
        this.id_produs = id_produs;
    }

    public Client(int id, String nume, String adresa) {
        this.id = id;
        this.nume = nume;
        this.adresa = adresa;

    }

    public void setId(int id) {
        this.id = id;
    }

    public double getPret_maxim() {
        return pret_maxim;
    }

    public Client(){

    }

    public double getPret_licitat() {
        return pret_licitat;
    }

    public void setPret_licitat(double pret_licitat) {
        this.pret_licitat = pret_licitat;
    }

    public int getId() {
        return id;
    }

    public String getNume() {
        return nume;
    }

    public String getAdresa() {
        return adresa;
    }

    public int getnr_participari() {
        return nr_participari;
    }

    public int getNr_licitatii_castigate() {
        return nr_licitatii_castigate;
    }

    /**
     * afiseaza toate produsele din casa de licitatii
     * @param e casa de licitatii
     */
    public void afiseazaProduse(CasaLicitatii e){
        for(int i = 0; i < e.getProduse().getList().size(); i++)
            e.getProduse().getList().get(i).print(e.getFile());
    }

    /**
     * se alatura unei licitatii exsitente sau creaza una nou daca licitatia pentru produs nu exista
     * asigneaza un broker random
     * @param e casa de licitatii
     * @param id_produs produsul dorit
     * @param id_client id clientului din casa de licitatii
     * @param pret_maxim pretul maxim pe care este dispus sa il plateasca clientul
     */

    public void alaturareLicitatie(CasaLicitatii e,int id_produs,int id_client,double pret_maxim){
        boolean exista_licitatie = false;
        int max = e.getAngajati().size() - 1;
        int min = 0;
        int random = (int) ((Math.random() * (max - min)) + min);
        for(int i = 0; i < e.getLicitatii().size(); i++){
            //verifica daca licitatia exista deja
            //daca licitatia exista adauga clientul respectiv la licitatie
            if(e.getLicitatii().get(i).getId_produs() == id_produs){
                e.getLicitatii().get(i).incParticipanti();
                e.getLicitatii().get(i).getBrokeri().add(e.getAngajati().get(random));
                e.getAngajati().get(random).getClienti().add(e.getClienti().get(id_client));
                e.getLicitatii().get(i).getClienti().add(e.getClienti().get(id_client));
                e.getClienti().get(id_client).setId_produs(id_produs);
                exista_licitatie = true;
                e.getFile().write("Brokerul " + random + " are " + e.getAngajati().get(random).getClienti().size() +
                        "\n");
            }
        }
        //daca licitatia nu exista creeaza una dupa care adauga clientul la licitatie
        if(!exista_licitatie){
            //cauta produsul pentru a extrage pretul minim
            int ci = -1;
            for(int i = 0; i < e.getProduse().getList().size(); i++){
                if(e.getProduse().getList().get(i).getId() == id_produs){
                    ci = i;
                    break;
                }
            }
            Licitatie x = new Licitatie(e.getLicitatii().size(),3,id_produs,3,
                    e.getProduse().getList().get(ci).getPret_minim());
            x.getBrokeri().add(e.getAngajati().get(random));
            e.getLicitatii().add(x);
            int i = e.getLicitatii().size() - 1;
            e.getLicitatii().get(i).incParticipanti();
            e.getAngajati().get(random).getClienti().add(e.getClienti().get(id_client));
            e.getLicitatii().get(i).getClienti().add(e.getClienti().get(id_client));
            e.getClienti().get(id_client).setId_produs(id_produs);
            e.getFile().write("Brokerul " + random + " are " + e.getAngajati().get(random).getClienti().size() +
                    "\n");
        }
        this.pret_maxim = pret_maxim;
        this.nr_participari++;
    }

    /**
     * liciteaza un pret random mai mare decat cel mai mare pret din pasul precedent
     * @param pret_minim_produs pretul maxim de la pasul precedent(deci minim pt client)
     * @return returneaza suma licitata
     */

    double liciteaza(double pret_minim_produs, PrintWriter file){
        int max = 50;
        int min = 1;
        int random = (int) ((Math.random() * (max - min)) + min);
        double suma = pret_minim_produs + random * 2.5;
        if(suma > pret_maxim) {
            file.write("Suma maxima depasita!Suma licitata automat\n");
            this.pret_maxim = 0;
            return 0;
        }
        this.pret_licitat = suma;
        return suma;
    }

    void incLicitatiiCastigate(){
        nr_licitatii_castigate++;
    }

    public abstract void print(PrintWriter file);
}
