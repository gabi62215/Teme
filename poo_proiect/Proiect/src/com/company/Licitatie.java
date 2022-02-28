package com.company;

import java.util.ArrayList;

/**
 * detine informatiile legate de o licitatie
 */

public class Licitatie {
    private int id;
    private int nr_participanti;
    private int id_produs;
    private int nr_pasi_maxim;
    private int participanti_curenti = 0;
    private int pasi = 1;
    private ArrayList<Broker> brokeri = new ArrayList<>();
    private double maxim;
    private ArrayList<Client> clienti = new ArrayList<>();
    private boolean licitatie_terminata = false;

    public Licitatie(int id, int nr_participanti, int id_produs, int nr_pasi_maxim,double pret_minim_initial) {
        this.id = id;
        this.nr_participanti = nr_participanti;
        this.id_produs = id_produs;
        this.nr_pasi_maxim = nr_pasi_maxim;
        this.maxim = pret_minim_initial;
    }

    public boolean isLicitatie_terminata() {
        return licitatie_terminata;
    }

    public void setLicitatie_terminata(boolean licitatie_terminata) {
        this.licitatie_terminata = licitatie_terminata;
    }

    public ArrayList<Client> getClienti() {
        return clienti;
    }

    public Licitatie() {
    }

    public ArrayList<Broker> getBrokeri() {
        return brokeri;
    }

    public double getMaxim() {
        return maxim;
    }

    public void setMaxim(double maxim) {
        this.maxim = maxim;
    }

    public int getId() {
        return id;
    }

    public int getNr_participanti() {
        return nr_participanti;
    }

    public int getId_produs() {
        return id_produs;
    }

    public int getNr_pasi_maxim() {
        return nr_pasi_maxim;
    }

    public void incParticipanti(){
        participanti_curenti++;
    }

    public void incPasi(){
        pasi++;
    }

    public int getParticipanti_curenti() {
        return participanti_curenti;
    }

    public int getPasi() {
        return pasi;
    }
}
