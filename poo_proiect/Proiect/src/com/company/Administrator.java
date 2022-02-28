package com.company;

import java.util.List;

/**
 * adauga produse in casa de licitatii pana cand lista ajunge la 10
 * odata ce ajunge la 10 se opreste si asteapta lichidarea unor produse
 * pentru a mai adauga
 */

public class Administrator implements Runnable {
    CasaLicitatii x;
    public Administrator(CasaLicitatii x) {
        this.x = x;
    }

    /**
     * citeste din fisierul de obiecte produse.txt odata la 5 secunde
     * si parseaza fiecare obiect
     */
    @Override
    public void run() {
        List l = ReadFile.readFileInList("produse.txt");

        for(int i = 0; i < l.size(); i++){
            Produs e = null;
            String[] command = ((String) l.get(i)).split(" ", 0);
            if(command[0].equals("tablou")){

                e = new ProductFactory("tablou").getProdus(i,command[0],command[1],command[2],
                        command[3],command[4]);
            }
            if(command[0].equals("mobila")){

                e = new ProductFactory("mobila").getProdus(i,command[0],command[1],command[2],
                        command[3],command[4]);
            }
            if(command[0].equals("bijuterie")){

                e = new ProductFactory("bijuterie").getProdus(i,command[0],command[1],command[2],
                        command[3],command[4]);
            }

            x.getProduse().adauga(e);

        }
    }
}
