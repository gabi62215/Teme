package com.company;


import org.apache.commons.csv.CSVFormat;

import org.apache.commons.csv.CSVRecord;

import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.Reader;

public class CSVReader {
    private String in_file;
    private String out_file;


    public CSVReader() {
    }

    void readCSV(Store store) throws IOException, DuplicateProductException {

        Reader in = new FileReader(in_file);
        Iterable<CSVRecord> records = CSVFormat.DEFAULT
                .withHeader("uniq_id", "product_name", "manufacturer", "price", "number_available_in_stock")
                .withFirstRecordAsHeader()
                .parse(in);


        for (CSVRecord csvRecord : records) {
            Manufacturer a = new Manufacturer(csvRecord.get("manufacturer"));
            String price_s = csvRecord.get("price");
            price_s = price_s.replaceAll(",", "");
            double price = Double.parseDouble(price_s.substring(1));
            String stock_s = csvRecord.get("number_available_in_stock");
            stock_s = stock_s.replaceAll("NEW", " ");
            int stock = Integer.parseInt(stock_s.substring(0, stock_s.length() - 2));
            ProductBuilder builder = new ProductBuilder();
            builder.setId(csvRecord.get("uniq_id"));
            builder.setName(csvRecord.get("product_name"));
            builder.setManufacturer(csvRecord.get("manufacturer"));
            builder.setPrice(price);
            builder.setQuantity(stock);
            Product x = builder.getProduct();
            store.addProduct(x);

            store.addManufacturer(a);
        }
        in.close();


    }

    void writeCSV(Store store) throws IOException {
        FileWriter myWritter = new FileWriter(out_file);
        for (int i = 0; i < store.getProducts().size(); i++) {
            myWritter.write(store.getProducts().get(i).getId() + ",");
            myWritter.write(store.getProducts().get(i).getName() + ",");
            myWritter.write(store.getProducts().get(i).getManufacturer().getName() + ",");
            myWritter.write(store.getCurrency().getSymbol() + store.getProducts().get(i).getPrice() + ",");
            myWritter.write(store.getProducts().get(i).getQuantity() + "\n");
        }
        myWritter.close();
    }

    public void setIn_file(String in_file) {
        this.in_file = in_file;
    }

    public void setOut_file(String out_file) {
        this.out_file = out_file;
    }
}
