package com.company;

/**
 * construieste un obiect de tip mobila
 */

public class MobilaBuilder implements Builder {
    private Mobila mobila;

    public MobilaBuilder() {
        mobila = new Mobila();
    }

    public void setId(int id) {
        ((Produs)mobila).setId(id);
    }

    public void setName(String nume) {
        ((Produs)mobila).setNume(nume);
    }

    public void setPretMinim(String pret) {
        double x = Double.parseDouble(pret);
        ((Produs)mobila).setPret_minim(x);
    }

    public void setAn(String an) {
        int x = Integer.parseInt(an);
        ((Produs)mobila).setAn(x);
    }

    public void setCaracteristica1(String c1) {
        mobila.setTip(c1);
    }

    public void setCaracteristica2(String c2) {
        mobila.setMaterial(c2);
    }

    public Mobila getMobila(){
        return mobila;
    }
}
