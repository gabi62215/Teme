package com.company;

import java.io.PrintWriter;

/**
 * subclasa a clasei Client
 * descrie o persoana juridica
 */

public class PersoanaJuridica extends Client {
    @Override
    public void print(PrintWriter file) {
        if(tip == Companie.SRL)
            file.write(super.getNume() + " " +
                    super.getAdresa() + " SRL " + captial_social + "\n");
        else
            file.write(super.getNume() + " " +
                    super.getAdresa() + " SA " + captial_social + "\n");
    }

    public enum Companie{
        SRL,SA
    }

    private Companie tip;
    private double captial_social;

    public PersoanaJuridica(int id, String nume, String adresa, Companie tip, double captial_social) {
        super(id, nume, adresa);
        this.tip = tip;
        this.captial_social = captial_social;
    }

    public Companie getTip() {
        return tip;
    }

    public double getCaptial_social() {
        return captial_social;
    }


}
