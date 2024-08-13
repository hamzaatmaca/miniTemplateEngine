#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <sstream>

std::string readFile(const std::filesystem::path& path) {
    if (!std::filesystem::exists(path)) {
        std::cerr << "Dosya mevcut değil: " << path << std::endl;
        return "";
    }
    std::ifstream file(path);
    std::stringstream buffer;
    if (file.is_open()) {
        buffer << file.rdbuf();
        file.close();
    } else {
        std::cerr << "Dosya açılamadı: " << path << std::endl;
    }
    return buffer.str();
}

int main() {
    std::filesystem::path current_path = std::filesystem::current_path();  
    std::cout << "Mevcut Çalışma Dizin: " << current_path << std::endl;

    std::filesystem::path index_path = current_path / "view" / "index.html";
    std::filesystem::path navbar_path = current_path / "view"/ "partials" / "navbar.html";
    std::filesystem::path footer_path = current_path / "view"/ "partials" / "footer.html";
    std::filesystem::path content_path = current_path / "view"/ "pages" / "home.html";

    std::cout << "Index Path: " << index_path << std::endl;
    std::cout << "Navbar Path: " << navbar_path << std::endl;
    std::cout << "Footer Path: " << footer_path << std::endl;
    std::cout << "Content Path: " << content_path << std::endl;

    std::string index_template = readFile(index_path);
    std::string navbar = readFile(navbar_path);
    std::string footer = readFile(footer_path);
    std::string content = readFile(content_path);

    if (index_template.empty() || navbar.empty() || footer.empty() || content.empty()) {
        std::cerr << "Bir veya daha fazla dosya okunamadı." << std::endl;
        return 1;
    }

    std::string result = index_template;
    std::string::size_type pos;

    // Yer tutucuları değiştir
    pos = result.find("{{ _NAVBAR }}");
    if (pos != std::string::npos) {
        result.replace(pos, 13, navbar);
    }

    pos = result.find("{{ _CONTENT }}");
    if (pos != std::string::npos) {
        result.replace(pos, 14, content);
    }

    pos = result.find("{{ _FOOTER }}");
    if (pos != std::string::npos) {
        result.replace(pos, 13, footer);
    }

    // Sonuç dosyasını yaz
    std::ofstream output_file(current_path / "view" / "combined.html");
    if (output_file.is_open()) {
        output_file << result;
        output_file.close();
    } else {
        std::cerr << "Sonuç dosyası açılamadı." << std::endl;
    }

    return 0;
}
