package com.company;

import java.io.PrintWriter;

/**
 * subclasa a clasei produs
 * descrie un tablou
 */

public class Tablou extends Produs {
    private String nume_pictor;
    public enum Culori{
        ULEI,TEMPERA,ACRILIC
    }
    private Culori culoare;

    public Tablou() {

    }

    public String getNume_pictor() {
        return nume_pictor;
    }

    public Culori getCuloare() {
        return culoare;
    }

    public void setNume_pictor(String nume_pictor) {
        this.nume_pictor = nume_pictor;
    }

    public void setCuloare(Culori culoare) {
        this.culoare = culoare;
    }

    public void print(PrintWriter file){
        if(culoare == Culori.ULEI)
            file.write(super.getId() + " " + super.getAn() + " " + super.getPret_minim() + " " +
                    super.getNume() + " " + nume_pictor + " " + "ulei" + "\n");
        if(culoare == Culori.ACRILIC)
            file.write(super.getId() + " " + super.getAn() + " " + super.getPret_minim() + " " +
                    super.getNume() + " " + nume_pictor + " " + "acrilic" + "\n");
        if(culoare == Culori.TEMPERA)
            file.write(super.getId() + " " + super.getAn() + " " + super.getPret_minim() + " " +
                    super.getNume() + " " + nume_pictor + " " + "tempera" + "\n");
    }
}
