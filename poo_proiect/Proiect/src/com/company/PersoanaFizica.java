package com.company;

import java.io.PrintWriter;

/**
 * subclasa a clasei Client
 * descrie o persoana fizica
 */

public class PersoanaFizica extends Client {
    private String data_nastere;

    public PersoanaFizica(int id, String nume, String adresa,  String data_nastere) {
        super(id, nume, adresa);
        this.data_nastere = data_nastere;
    }

    public String getData_nastere() {
        return data_nastere;
    }


    @Override
    public void print(PrintWriter file) {
        file.write(super.getNume() + " " +
                super.getAdresa()+ " " + data_nastere + "\n");
    }
}
