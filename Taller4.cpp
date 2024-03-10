#include "libs/TextFileHandler.h"
#include "libs/List.h"
#include "libs/BinaryFileHandler.h"
#include "libs/Product.h"

#include <iostream>
#include <string.h>
#include <stdlib.h> 

using namespace std;

ProductBinary productToBinary(Product product) {
    ProductBinary binary;
    strcpy(binary.BinaryName, product.storeName.c_str());
    strcpy(binary.BinaryURL, product.storeURL.c_str());
    strcpy(binary.BinaryProductName, product.productName.c_str());
    strcpy(binary.BinaryDatePromotionPeriod, product.datePromotionPeriod.c_str());
    binary.BinaryPrice = product.price;
    return binary;
}

void printMenu();

int main() {
    
    printMenu();

    int option = 0;
    List<Product> products;
    string textFileName = "productos.txt";
    string binaryFileName = "productos.bin";
    BinaryFileHandler<ProductBinary> binaryFileHandler(binaryFileName);

    do {
        cout << "Ingrese una opción: ";
        cin >> option;

       switch (option)
        {
            case 1:
                {
                cout << "Opción 1" << endl;
                TextFileHandler textFileHandler(textFileName);
                List<ProductBinary> binarios;
                ProductBinary Binary;
                List<string> lines = textFileHandler.readLines();
                for (int i = 0; i < lines.size; i++) {
                List<string> tokens = split(lines.get(i), ';');
                    strcpy(Binary.BinaryName, tokens.get(0).c_str());
                    strcpy(Binary.BinaryURL, tokens.get(1).c_str());
                    strcpy(Binary.BinaryProductName, tokens.get(2).c_str());
                    strcpy(Binary.BinaryDatePromotionPeriod, tokens.get(3).c_str());
                    Binary.BinaryPrice = stod(tokens.get(4));
                    binarios.add(Binary);
            }
                binaryFileHandler.writeBinaryFile(binarios);
                cout << "Archivo binario creado."<< endl;
                cout << endl;
            }
            break;

            case 2:
            {
                cout << endl;
            cout << "Opción 2" << endl;
            List<ProductBinary> binarios = binaryFileHandler.readBinaryFile();
            for (int i = 0; i < binarios.size; i++) {
                ProductBinary BinaryProduct = binarios.get(i);
                Product product;
                product.storeName = BinaryProduct.BinaryName;
                product.storeURL = BinaryProduct.BinaryURL;
                product.productName = BinaryProduct.BinaryProductName;
                product.datePromotionPeriod = BinaryProduct.BinaryDatePromotionPeriod;
                product.price = BinaryProduct.BinaryPrice;
                products.add(product);
            }
            for (int i = 0; i < products.size; i++) {
                Product product = products.get(i);
                cout << "Nombre de la tienda: " << product.storeName << endl;
                cout << "URL de la tienda: " << product.storeURL << endl;
                cout << "Nombre del producto: " << product.productName << endl;
                cout << "Tiempo de promoción: " << product.datePromotionPeriod << endl;
                cout << "Precio: " << product.price << endl;
                cout << endl;
                }
                cout << endl;
            }
            break;
            case 3:
            {
                cout << endl;
                cout << "Opción 3" << endl;
            Product product;
            cout << "Ingrese el nombre de la tienda: ";
            cin >> product.storeName;
            cout << "Ingrese la URL de la tienda: ";
            cin >> product.storeURL;
            cout << "Ingrese el nombre del producto: ";
            cin >> product.productName;
            cout << "Ingrese tiempo de promoción (DD/MM/AAAA): ";
            cin >> product.datePromotionPeriod;
            cout << "Ingrese el precio: ";
            cin >> product.price;

            ProductBinary binaryProduct = productToBinary(product);
            if (binaryFileHandler.appendElementToFile(binaryProduct)) {
                cout << "Producto agregado." << endl;
            }
            else {
                cout << "Error al agregar." << endl;
            }
            cout << endl;
            } 
            break;
                
            case 4:
            {
                cout << endl;
                cout << "Opción 4" << endl;
                int linea;
                cout << "Ingrese el producto que desea eliminar, guíese por la selección de menu dos: ";
                cin >> linea;
                if (binaryFileHandler.removeElementFromFile(linea)) {
                    cout << "Producto eliminado." << endl;
                }
                else {
                    cout << "No se logró eliminar." << endl;
                }
                cout << endl;
                } 
            break; 

            case 5: {
                cout << "Opción 5" << endl;
                string date, name;
                cout << "Ingrese la fecha de promoción (DD/MM/AAAA): ";
                cin >> date;
                cout << "Ingrese el nombre del producto: ";
                cin >> name;
                List<Product> mejoresProductos = Mejores(date, name);
                cout << "Los " << mejoresProductos.size << " productos más baratos son:" << endl;
                for (int i = 0; i < mejoresProductos.size; i++) {
                    Product product = mejoresProductos.get(i);
                    cout << "Nombre de la tienda: " << product.storeName << endl;
                    cout << "URL de la tienda: " << product.storeURL << endl;
                    cout << "Nombre del producto: " << product.productName << endl;
                    cout << "Tiempo de promoción: " << product.datePromotionPeriod << endl;
                    cout << "Precio: " << product.price << endl;
                    cout << endl;
                }
            }
            break;

            case 0:
                cout << "Saliendo..." << endl;
                break;

            default:
                cout << "Opción inválida" << endl;
                break;
        } 

    } while (option != 0);
    
    return 0;
}

void printMenu() {
    cout << "1. Leer productos desde un archivo de texto y crear un archivo binario" << endl;
    cout << "2. Mostrar productos del archivo binario" << endl;
    cout << "3. Agregar un producto al archivo binario" << endl;
    cout << "4. Borrar un producto del archivo binario" << endl;
    cout << "5. Buscar productos por nombre y fecha de vigencia" << endl;
    cout << "0. Salir" << endl;
}