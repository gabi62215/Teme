package com.company;

import java.io.PrintWriter;

/**
 * descire elementele de baza ale oricarui produs
 */

public abstract class Produs {
    private int id;
    private String nume;
    private double pret_vanzare;
    private double pret_minim;
    private int an;

    public Produs(int id, String nume, double pret_vanzare, double pret_minim, int an) {
        this.id = id;
        this.nume = nume;
        this.pret_vanzare = pret_vanzare;
        this.pret_minim = pret_minim;
        this.an = an;
    }

    public Produs() {
    }

    public int getId() {
        return id;
    }

    public String getNume() {
        return nume;
    }

    public double getPret_vanzare() {
        return pret_vanzare;
    }

    public double getPret_minim() {
        return pret_minim;
    }

    public int getAn() {
        return an;
    }

    public void setId(int id) {
        this.id = id;
    }

    public void setNume(String nume) {
        this.nume = nume;
    }

    public void setPret_vanzare(double pret_vanzare) {
        this.pret_vanzare = pret_vanzare;
    }

    public void setPret_minim(double pret_minim) {
        this.pret_minim = pret_minim;
    }

    public void setAn(int an) {
        this.an = an;
    }

    /**
     * functie de afisare diferita pentru ficare tip de obiect
     */
    public abstract void print(PrintWriter file);
}
