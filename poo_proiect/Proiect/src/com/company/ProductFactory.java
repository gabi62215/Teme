package com.company;

/**
 * creeaza produse in functie de tipul dorit
 */

public class ProductFactory {
    private String tip_produs;

    public ProductFactory(String tip_produs) {
        this.tip_produs = tip_produs;
    }

    public Produs getProdus(int id,String name,String pret_minim,String an,String c_1,String c_2){

        if(tip_produs.equals("tablou")) {
            TablouBuilder builder = new TablouBuilder();
            builder.setId(id);
            builder.setName(name);
            builder.setPretMinim(pret_minim);
            builder.setAn(an);
            builder.setCaracteristica1(c_1);
            builder.setCaracteristica2(c_2);
            return builder.getTablou();
        }

        if(tip_produs.equals("mobila")){
            MobilaBuilder builder = new MobilaBuilder();
            builder.setId(id);
            builder.setName(name);
            builder.setPretMinim(pret_minim);
            builder.setAn(an);
            builder.setCaracteristica1(c_1);
            builder.setCaracteristica2(c_2);
            return builder.getMobila();
        }

        if(tip_produs.equals("bijuterie")){
            BijuterieBuilder builder = new BijuterieBuilder();
            builder.setId(id);
            builder.setName(name);
            builder.setPretMinim(pret_minim);
            builder.setAn(an);
            builder.setCaracteristica1(c_1);
            builder.setCaracteristica2(c_2);
            return builder.getBijuterie();
        }

        return null;
    }


}
