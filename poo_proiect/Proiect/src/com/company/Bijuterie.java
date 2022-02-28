package com.company;

import java.io.PrintWriter;

/**
 * subclasa a clasei produs
 * descrie o bijuterie
 */

public class Bijuterie extends Produs {
    private String material;
    private boolean piatra_pretioasa;

    public Bijuterie() {
    }

    @Override
    public void print(PrintWriter file) {
        file.write(super.getId() + " " + super.getAn() + " " + super.getPret_minim() + " " +
                super.getNume() + " " + material + " " + piatra_pretioasa + "\n");
    }

    public String getMaterial() {
        return material;
    }

    public boolean isPiatra_pretioasa() {
        return piatra_pretioasa;
    }

    public void setMaterial(String material) {
        this.material = material;
    }

    public void setPiatra_pretioasa(boolean piatra_pretioasa) {
        this.piatra_pretioasa = piatra_pretioasa;
    }
}
