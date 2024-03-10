#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include "TextFileHandler.h"
#include "List.h"
#include "BinaryFileHandler.h"

using namespace std;

struct Product {
  string storeName;
  string storeURL;
  string productName;
  string datePromotionPeriod; //Format dd/mm/yyyy
  double price;
};

//structure to store the product in a binary file
struct ProductBinary {
  char BinaryName[50];
  char BinaryURL[100];
  char BinaryProductName[100];
  char BinaryDatePromotionPeriod[50];
  double BinaryPrice;
};

bool dateIsGreaterOrEqual(string date1,string date2) {
    List<string> separador1 = split(date1, '/');
    int firstYear = stoi(separador1.get(3));
    List<string> separador2 = split(date2, '/');
    int secondYear = stoi(separador2.get(3));
    if(firstYear > secondYear){
      return false;
    }
    return true; 
}

List<Product> getProductsFromLines(List<string> line, char delimiter){
  Product product;
  TextFileHandler textFileHandler("productos.txt");
    List<Product> productos;
    List<string> lines = textFileHandler.readLines();
    for (int i = 0; i < lines.size; i++) {
    List<string> tokens = split(lines.get(i), ';');
    product.storeName, tokens.get(0);
    product.storeURL, tokens.get(1);
    product.productName, tokens.get(2);
    product.datePromotionPeriod, tokens.get(3);
    product.price = stod(tokens.get(4));
    productos.add(product);
  }
  return productos;
}

List<Product> searchProducts(string date, string name) {

    List<Product> products;
    TextFileHandler textFileHandler("productos.txt");
    List<string> lines = textFileHandler.readLines();
    List<Product> LinesProducts = getProductsFromLines(lines, ';');
    for(int i = 0; i < LinesProducts.size; i++){
      bool taskDid = dateIsGreaterOrEqual(LinesProducts.get(i).datePromotionPeriod, date);
      if(taskDid && LinesProducts.get(i).productName == name){
        products.add(LinesProducts.get(i));
      }
    }
    return products;
}

List<Product> Mejores(string date, string name) {
  List<Product> productos = searchProducts(date, name);
    for (int i = 0; i < productos.size - 1; i++) {
      for (int j = i + 1; j < productos.size; j++) {
        if (productos.get(i).price > productos.get(j).price) {
          Product producto = productos.get(i);
          productos.set(i, productos.get(j));
          productos.set(j, producto);
        }
      }
    }

    TextFileHandler fileHandler("Mejores.txt");
    List<string> lines;
    for (int i = 0; i < 5 && i < productos.size; i++) {
        Product product = productos.get(i);
        string line = product.storeName + "," + product.storeURL + "," + product.productName + "," + product.datePromotionPeriod + "," + to_string(product.price);
        lines.add(line);
    }
    fileHandler.writeLines(lines);
    return productos;
}

#endif /* PRODUCT_H */