#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>

int main() {
    // Ouvrir le fichier JSON
    std::ifstream file("file.json", std::ifstream::binary);
    if (!file.is_open()) {
        std::cerr << "Erreur : impossible d'ouvrir le fichier JSON." << std::endl;
        return 1;
    }

    // Créer un objet Json::Value pour stocker les données JSON
    Json::Value jsonData;
    Json::CharReaderBuilder readerBuilder;
    std::string errs;

    // Lire et parser le fichier JSON
    if (!Json::parseFromStream(readerBuilder, file, &jsonData, &errs)) {
        std::cerr << "Erreur lors du parsing du JSON : " << errs << std::endl;
        return 1;
    }

    // Accéder aux valeurs du fichier JSON
    std::string name = jsonData["name"].asString();
    int age = jsonData["age"].asInt();
    bool isEmployed = jsonData["isEmployed"].asBool();

    std::cout << "Nom: " << name << std::endl;
    std::cout << "Âge: " << age << std::endl;
    std::cout << "Emploi: " << (isEmployed ? "Oui" : "Non") << std::endl;

    // Accéder aux éléments du tableau "languages"
    const Json::Value languages = jsonData["languages"];
    std::cout << "Langues:" << std::endl;
    for (const auto& language : languages) {
        std::cout << " - " << language.asString() << std::endl;
    }

    return 0;
}


