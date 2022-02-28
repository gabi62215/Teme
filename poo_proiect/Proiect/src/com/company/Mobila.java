package com.company;

import java.io.PrintWriter;

/**
 * subclasa a clasei Produs
 * descrie o piesa de mobila
 */

public class Mobila extends Produs {
    private String tip;
    private String material;

    public Mobila() {
    }

    @Override
    public void print(PrintWriter file) {
        file.write(super.getId() + " " + super.getAn() + " " + super.getPret_minim() + " " +
                super.getNume() + " " + tip + " " + material + "\n");
    }

    public void setTip(String tip) {
        this.tip = tip;
    }

    public void setMaterial(String material) {
        this.material = material;
    }

    public String getTip() {
        return tip;
    }

    public String getMaterial() {
        return material;
    }
}
