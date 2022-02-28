package com.company;

/**
 * construieste un obiect de tip tablou
 */

public class TablouBuilder implements Builder {
    private Tablou tablou;

    public TablouBuilder(){
        tablou = new Tablou();
    }


    @Override
    public void setId(int id) {
        ((Produs)tablou).setId(id);
    }

    @Override
    public void setName(String nume) {
        ((Produs)tablou).setNume(nume);
    }

    @Override
    public void setPretMinim(String pret) {
        double x = Double.parseDouble(pret);
        ((Produs)tablou).setPret_minim(x);
    }

    @Override
    public void setAn(String an) {
        int x = Integer.parseInt(an);
        ((Produs)tablou).setAn(x);
    }

    @Override
    public void setCaracteristica1(String c1) {
        tablou.setNume_pictor(c1);
    }

    @Override
    public void setCaracteristica2(String c2) {
        if(c2.equals("tempera"))
            tablou.setCuloare(Tablou.Culori.TEMPERA);
        if(c2.equals("acrilic"))
            tablou.setCuloare(Tablou.Culori.ACRILIC);
        if(c2.equals("ulei"))
            tablou.setCuloare(Tablou.Culori.ULEI);
    }

    public Tablou getTablou(){
        return tablou;
    }
}
