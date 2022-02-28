package com.company;

import java.io.FileWriter;
import java.io.IOException;
import java.util.List;

import static com.company.Discount.DiscountType.FIXED_DISCOUNT;
import static com.company.Discount.DiscountType.PERCENTAGE_DISCOUNT;

public class Main {

    public static void main(String[] args) throws IOException, CurrencyNotFoundException, DiscountNotFoundException, NegativePriceException, DuplicateProductException {
        Store store = Store.getInstance();
        List l = ReadFile.readFileInList("input.txt");
        CSVReader csv = new CSVReader();
        String[] command;
        String quotes = null;
        FileWriter myWritter = new FileWriter("output.txt");
        for (int i = 0; i < l.size(); i++) {
            //splits each line by space to get the command and parameters
            if (((String) l.get(i)).contains("\"")) {
                command = (((String) l.get(i)).substring(0, ((String) l.get(i)).indexOf("\"")).split(" ", 0));
                quotes = ((String) l.get(i)).substring(((String) l.get(i)).indexOf("\""), ((String) l.get(i)).length());
            } else
                command = ((String) l.get(i)).split(" ", 0);
            switch (command[0]) {
                case "listcurrencies":
                    store.listCurrencies(myWritter);
                    break;
                case "getstorecurrency":
                    myWritter.write(store.getCurrency().getName());
                    myWritter.write("\n");
                    break;
                case "addcurrency":
                    Currency x = new Currency(command[1], command[2], Double.parseDouble(command[3]));
                    store.getCurrencies().add(x);
                    break;
                case "loadcsv":
                    csv.setIn_file(command[1]);
                    csv.readCSV(store);
                    break;
                case "savecsv":
                    csv.setOut_file(command[1]);
                    csv.writeCSV(store);
                    break;
                case "setstorecurrency":
                    store.setCurrent_currency(command[1]);
                    break;
                case "updateparity":
                    double parity = Double.parseDouble(command[2]);
                    store.updateParity(command[1], parity);
                    break;
                case "listproducts":
                    store.listProducts(myWritter);
                    break;
                case "showproduct":
                    store.showProduct(command[1], myWritter);
                    break;
                case "listmanufacturers":
                    store.listManufacturers(myWritter);
                    break;
                case "listproductsbymanufacturarer":
                    store.listProductsByManufacturarer(command[1], myWritter);
                    break;
                case "listdiscounts":
                    store.listDiscounts(myWritter);
                    break;
                case "addiscount":
                    Discount discount;
                    if (command[1].equals("PERCENTAGE")) {
                        discount = new Discount(Double.parseDouble(command[2]), PERCENTAGE_DISCOUNT, quotes);
                    } else
                        discount = new Discount(Double.parseDouble(command[2]), FIXED_DISCOUNT, quotes);
                    store.getDiscounts().add(discount);
                    break;
                case "applydiscount":
                    if (command[1].equals("PERCENTAGE")) {
                        store.applyDiscount(PERCENTAGE_DISCOUNT, Double.parseDouble(command[2]));
                    } else
                        store.applyDiscount(FIXED_DISCOUNT, Double.parseDouble(command[2]));
                    break;
                case "calculatetotal":
                    store.calculateTotal(command, myWritter);
                    break;
                case "exit":
                    myWritter.close();
                    System.exit(0);
                    break;
                case "quit":
                    myWritter.close();
                    System.exit(0);
                    break;
            }

        }
    }
}
