#include <iostream>
#include <string>
#include <algorithm>

class DetectorTarjetas {
private:
    static bool esDigito(char c) {
        return c >= '0' && c <= '9';
    }

    static int charAInt(char c) {
        return c - '0';
    }

    static bool validarLuhn(const std::string& numero) {
        int suma = 0;
        bool alternar = false;
        for (int i = numero.length() - 1; i >= 0; i--) {
            int n = charAInt(numero[i]);
            if (alternar) {
                n *= 2;
                if (n > 9) {
                    n = (n % 10) + 1;
                }
            }
            suma += n;
            alternar = !alternar;
        }
        return (suma % 10 == 0);
    }

public:
    static bool validarTarjeta(const std::string& numero) {
        // Eliminar espacios y guiones
        std::string numeroLimpio;
        std::copy_if(numero.begin(), numero.end(), std::back_inserter(numeroLimpio), esDigito);

        // Verificar longitud
        if (numeroLimpio.length() < 13 || numeroLimpio.length() > 19) {
            return false;
        }

        // Aplicar algoritmo de Luhn
        return validarLuhn(numeroLimpio);
    }
};

int main() {
    std::string numeroTarjeta;
    
    std::cout << "Por favor, ingrese el número de su tarjeta de crédito: ";
    std::getline(std::cin, numeroTarjeta);

    if (DetectorTarjetas::validarTarjeta(numeroTarjeta)) {
        std::cout << "La tarjeta es válida." << std::endl;
    } else {
        std::cout << "Error: La tarjeta no es válida." << std::endl;
    }

    return 0;
}