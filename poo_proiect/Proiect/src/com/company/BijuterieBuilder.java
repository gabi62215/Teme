package com.company;

/**
 * construieste o bijuterie
 */

public class BijuterieBuilder implements Builder {
    private Bijuterie bijuterie;

    public BijuterieBuilder() {
        bijuterie = new Bijuterie();
    }


    @Override
    public void setId(int id) {
        ((Produs)bijuterie).setId(id);
    }

    @Override
    public void setName(String nume) {
        ((Produs)bijuterie).setNume(nume);
    }

    @Override
    public void setPretMinim(String pret) {
        double x = Double.parseDouble(pret);
        ((Produs)bijuterie).setPret_minim(x);
    }

    @Override
    public void setAn(String an) {
        int x = Integer.parseInt(an);
        ((Produs)bijuterie).setAn(x);
    }

    @Override
    public void setCaracteristica1(String c1) {
        bijuterie.setMaterial(c1);
    }

    @Override
    public void setCaracteristica2(String c2) {
        boolean x = Boolean.parseBoolean(c2);
        bijuterie.setPiatra_pretioasa(x);
    }

    public Bijuterie getBijuterie() {
        return bijuterie;
    }
}
