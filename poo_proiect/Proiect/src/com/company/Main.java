package com.company;

import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Main {

    public static void main(String[] args) {
        try {
            PrintWriter my_file = new PrintWriter("licitatie.out");
            CasaLicitatii x = CasaLicitatii.getInstance();
            x.setFile(my_file);
            x.getClienti().add(new PersoanaFizica(0,"Gabi","petofi sandor 8","13.06.2000"));
            x.getClienti().add(new PersoanaFizica(1,"Matei","valea ialomitei 13","29.05.2000"));
            x.getClienti().add(new PersoanaFizica(2,"Sara","calea victoriei 12","26.11.2001"));

            x.getClienti().add(new PersoanaJuridica(3,"Geaxi","magheru 15",
                    PersoanaJuridica.Companie.SRL,2000));
            x.getClienti().add(new PersoanaJuridica(4,"Geaxi","lascar catargiu 3",
                    PersoanaJuridica.Companie.SA,250));
            x.getClienti().add(new PersoanaJuridica(5,"Ciprian","clucerului 30",
                    PersoanaJuridica.Companie.SRL,550.57));

            x.getAngajati().add(new Broker(x));
            x.getAngajati().add(new Broker(x));
            x.getAngajati().add(new Broker(x));

            ExecutorService executor = Executors.newFixedThreadPool(2);
            executor.execute(new Administrator(x));
            executor.execute(x);
            executor.shutdown();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }


    }
}
